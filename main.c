#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
struct TrieNode {
    struct TrieNode* children[26];
    int count; // Count of occurrences of the word
};

// Function to create a new Trie node
struct TrieNode* createNode() {
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    newNode->count = 0;
    for (int i = 0; i < 26; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Function to insert a word into the Trie
void insert(struct TrieNode* root, char* word) {
    struct TrieNode* curr = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            curr->children[index] = createNode();
        }
        curr = curr->children[index];
    }
    // Mark the end of the word and increase its count
    curr->count++;
}

// Function to read a dictionary file and store words into an array
int readDictionary(char* filename, char** pInWords) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int numWords = 0;
    char word[100]; // Assuming maximum word length is 100 characters
    while (fscanf(file, "%s", word) != EOF) {
        pInWords[numWords] = strdup(word);
        numWords++;
    }
    fclose(file);
    return numWords;
}

int main(void) {
    char* inWords[256];
    // Read the number of words in the dictionary and store them in inWords
    int numWords = readDictionary("dictionary-1.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }

    // Create a Trie and insert words from inWords array
    struct TrieNode* pTrie = createNode();
    for (int i = 0; i < numWords; i++) {
        insert(pTrie, inWords[i]);
    }

    // Test some words
    char* pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        struct TrieNode* curr = pTrie;
        char* word = pWords[i];
        for (int j = 0; word[j] != '\0'; j++) {
            int index = word[j] - 'a';
            if (curr->children[index] == NULL) {
                printf("\t%s : %d\n", word, 0);
                break;
            }
            curr = curr->children[index];
            if (word[j + 1] == '\0') {
                printf("\t%s : %d\n", word, curr->count);
            }
        }
    }

    // Deallocate memory used by the Trie
    for (int i = 0; i < numWords; i++) {
        free(inWords[i]);
    }
    free(pTrie);

    return 0;
}