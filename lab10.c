#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    struct Trie* children[26];
    int count;
};

// Helper function to create a new Trie node
struct Trie* createNode()
{
    struct Trie* newNode = (struct Trie*)malloc(sizeof(struct Trie));
    newNode -> count = 0;

    for (int i = 0; i < 26; i++){
        newNode -> children[i] = NULL;
    }
    return newNode;
}

// Inserts the word into the trie structure
void insert(struct Trie* pTrie, char* word)
{
    struct Trie* curr = pTrie;

    for (int i = 0; word[i] != '\0'; i++){
        int index = word[i] - 'a';

        if (curr -> children[index] == NULL){
            curr -> children[index] = createNode();
        }
        curr = curr->children[index];
    }

    curr -> count++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct Trie* pTrie, char* word)
{
    struct Trie* curr = pTrie;
    for (int i = 0; word[i] != '\0'; i++){
        int index = word[i] - ('a');

        if (curr -> children[index] == NULL){
            return 0;
        }
        curr = curr->children[index];
    }

    return curr->count;
}

// Deallocates the trie structure
void deallocateTrie(struct Trie* pTrie)
{
    if (pTrie == NULL)
        return;

    for (int i = 0; i < 26; i++){
        if (pTrie->children[i] != NULL){
            deallocateTrie(pTrie->children[i]);
        }
    }

    free(pTrie);
}

// Initializes a trie structure
struct Trie* createTrie()
{
    return createNode();
}

// This function will return the number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char* filename, char** pInWords)
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Open Error: %s\n", filename);
        exit(1);
    }

    int numWords;
    fscanf(fp, "%d", &numWords);
    for (int i = 0; i < numWords; ++i){
        pInWords[i] = (char*)malloc(100 * sizeof(char));
        fscanf(fp, "%s", pInWords[i]);
    }

    fclose(fp);

    return numWords;
}

int main(void)
{
    char* inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i){
        printf("%s\n", inWords[i]);
    }

    struct Trie* pTrie = createTrie();
    for (int i = 0; i < numWords; i++){
        insert(pTrie, inWords[i]);
    }

    // Parse line by line, and insert each word into the trie data structure
    char* pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++){
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    deallocateTrie(pTrie);
    return 0;
}
