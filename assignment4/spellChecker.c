#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Double linked list with front and back sentinels
struct HashList {
	
	struct HashLink* frontSentinel;
	int size;
};

struct HashList* hashListCreate() {
	struct HashList* list = malloc(sizeof(struct HashList));
	initHashList(list);
	return list;
}

static void initHashList(struct HashList* list) {

	struct HashLink* frontSen = (struct HashLink*)malloc(sizeof(struct HashLink));
	assert(frontSen != 0);

	frontSen->next = NULL;

	list->frontSentinel = frontSen;
	list->size = 0;
}


void hashListInsert(struct HashList* list, HashLink* link) {
	struct HashLink* newLink = (struct HashLink*)malloc(sizeof(struct HashLink));
	assert(newLink != 0);
    strcpy(newLink->key, link->key);
    newLink->value = link->value;
    newLink->next = NULL;

    HashLink* itr;

    itr = list->frontSentinel;
    while (itr->next != NULL) {
        if (itr->next->value > newLink->value) {
            break;
        } else {
            itr = itr->next;   
        }
    }
    newLink->next = itr->next;
    itr->next = newLink;
    list->size ++;

    if (list->size > 5) {
        while (itr->next->next != NULL) {
            itr = itr->next;
        }
        struct HashLink* holder = itr->next;
        itr->next = NULL;
        free(holder->key);
        free(holder);
    }
}

void hashListDestroy(struct HashList* list) {
    assert(list != NULL);

    struct HashLink* itr = list->frontSentinel;
    struct HashLink* holder;
    while (itr != NULL) {
        holder = itr;
        itr = itr->next;
        hashLinkDelete(holder);
    }
    free(list);
}

void hashListPrint(struct HashList* list) {
    assert( list != NULL);

    struct HashLink* itr = list->frontSentinel->next;
    while (itr != NULL) {
        printf("%s\n", itr->key);
        itr = itr->next;
    }
}

typedef enum {
    INSERTION,
    DELETION,
    SUBSTITUTION,
    NONE
} edit_type;
 
struct edit {
    unsigned int score;
    edit_type type;
    char arg1;
    char arg2;
    unsigned int pos;
    struct edit *prev;
};
typedef struct edit edit;
 
static int min3(int a, int b, int c) {
    if (a < b && a < c) {
        return a;
    }
    if (b < a && b < c) {
        return b;
    }
    return c;
}
 
static unsigned int levenshtein_matrix_calculate(edit **mat, const char *str1, size_t len1, const char *str2, size_t len2) {
    unsigned int i, j;
    for (j = 1; j <= len2; j++) {
        for (i = 1; i <= len1; i++) {
            unsigned int substitution_cost;
            unsigned int del = 0, ins = 0, subst = 0;
            unsigned int best;
            if (str1[i - 1] == str2[j - 1]) {
                substitution_cost = 0;
            }
            else {
                substitution_cost = 1;
            }
            del = mat[i - 1][j].score + 1; /* deletion */
            ins = mat[i][j - 1].score + 1; /* insertion */
            subst = mat[i - 1][j - 1].score + substitution_cost; /* substitution */
            best = min3(del, ins, subst);
            mat[i][j].score = best;                  
            mat[i][j].arg1 = str1[i - 1];
            mat[i][j].arg2 = str2[j - 1];
            mat[i][j].pos = i - 1;
            if (best == del) {
                mat[i][j].type = DELETION;
                mat[i][j].prev = &mat[i - 1][j];
            }
            else if (best == ins) {
                mat[i][j].type = INSERTION;
                mat[i][j].prev = &mat[i][j - 1];
            }
            else {
                if (substitution_cost > 0) {
                    mat[i][j].type = SUBSTITUTION;
                }
                else {
                    mat[i][j].type = NONE;
                }
                mat[i][j].prev = &mat[i - 1][j - 1];
            }
        }
    }
    return mat[len1][len2].score;
}
 
static edit **levenshtein_matrix_create(const char *str1, size_t len1, const char *str2, size_t len2) {
    unsigned int i, j;
    edit **mat = malloc((len1 + 1) * sizeof(edit *));
    if (mat == NULL) {
        return NULL;
    }
    for (i = 0; i <= len1; i++) {
        mat[i] = malloc((len2 + 1) * sizeof(edit));
        if (mat[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(mat[j]);
            }
            free(mat);
            return NULL;
        }
    }
    for (i = 0; i <= len1; i++) {
        mat[i][0].score = i;
        mat[i][0].prev = NULL;
        mat[i][0].arg1 = 0;
        mat[i][0].arg2 = 0;
    }
 
    for (j = 0; j <= len2; j++) {
        mat[0][j].score = j;
        mat[0][j].prev = NULL;
        mat[0][j].arg1 = 0;
        mat[0][j].arg2 = 0;
    }
    return mat; 
}
 
unsigned int levenshtein_distance(const char *str1, const char *str2, edit **script) {
    const size_t len1 = strlen(str1), len2 = strlen(str2);
    unsigned int i, distance;
    edit **mat, *head;
 
    /* If either string is empty, the distance is the other string's length */
    if (len1 == 0) {
        return len2;
    }
    if (len2 == 0) {
        return len1;
    }
    /* Initialise the matrix */
    mat = levenshtein_matrix_create(str1, len1, str2, len2);
    if (!mat) {
        *script = NULL;
        return 0;
    }
    /* Main algorithm */
    distance = levenshtein_matrix_calculate(mat, str1, len1, str2, len2);
    /* Read back the edit script */
    *script = malloc(distance * sizeof(edit));
    if (*script) {
        i = distance - 1;
        for (head = &mat[len1][len2];
                head->prev != NULL;
                head = head->prev) {
            if (head->type != NONE) {
                memcpy(*script + i, head, sizeof(edit));
                i--;
            }
        }
    }
    else {
        distance = 0;
    }
    /* Clean up */
    for (i = 0; i <= len1; i++) {
        free(mat[i]);
    }
    free(mat);
 
    return distance;
}

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file) {
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            if (c >= 'A' && c <= 'Z') {
                c += 32;
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map) {
    assert(file != NULL);
    assert(map != NULL);

    char* word = nextWord(file);
    int* occurence;
    
    while (word != NULL) {
        occurence = hashMapGet(map, word);
        if (occurence != NULL) {
            ++*occurence;
        } else {
            hashMapPut(map, word, 1);
        }

        free(word);
        word = nextWord(file);
    }
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        struct HashList* suggestions = hashListCreate();
        int found = 0;
        
        // Implement the spell checker code here..
        for (int i = 0; i < map->capacity; i++) {
            if (map->table[i] != NULL) {
                HashLink* itr = map->table[i];
                while (itr != NULL) {
                    if (strcmp(inputBuffer, itr->key) == 0) {
                        printf("The inputted word %s is spelled correctly\n", inputBuffer);
                        found = 1;
                        break;
                    } else {
                        edit* script;
                        itr->value = levenshtein_distance(inputBuffer, itr->key, &script);
                        hashListInsert(suggestions, itr);
                        free(script);
                    }
                    itr = itr->next;
                }

                if (!found) {
                    printf("The inputted word %s is spelled incorrectly\n", inputBuffer);
                    printf("Did you mean:\n");
                    hashListPrint(suggestions);
                }
            }
        }
        hashListDestroy(suggestions);
        
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
    }
    
    hashMapDelete(map);
    return 0;
}