#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trie{
    int flag;
    struct trie *children[26];

} trie;

void insert(struct trie **ppTrie, char *word);
int numberOfOccurances(struct trie *pTrie, char *word);
struct trie *deallocateTrie(struct trie *pTrie);
trie *generateNode(void);




void insert(struct trie **ppTrie, char *word){
    //Base Case
    
    if(*ppTrie == NULL){
        return;
    }

    trie *temp = *ppTrie;

    

    int length = strlen(word);
    for (int i = 0; i < length; i++){
        int index = word[i] - 'a';
        if (temp->children[index] == NULL){
            
            temp->children[index] = generateNode();
        }
        temp = temp->children[index];
        
    }
    temp->flag++;
}
int numberOfOccurances(struct trie *pTrie, char *word){
    //Check if head is null, return 0 if it is
    if (pTrie == NULL) {
            return 0;
    }
        //initialize temp trie to traverse dictionanry
        trie *temp = pTrie;
        //determine length of the word and use a for loop to find word
        int length = strlen(word);
        for (int i = 0; i < length; i++){
            int index = word[i] - 'a';
            if (temp->children[index] == NULL){
                return 0;
            }
         temp = temp->children[index];
     }
     //once word is found return the flag, flag should be incremented +1 for every occurance of the word
     //so all we need to do is return the flag
     return temp->flag;  


}

struct trie *deallocateTrie(struct trie *pTrie){
    //Base Case to stop recursive call
    if (pTrie == NULL) {
        return NULL;
    }
    //for all 26 of the children, call the function recursively, stop if the node is NULL
    for (int i = 0; i < 26; i++) {
        trie *temp = deallocateTrie(pTrie->children[i]);
        pTrie->children[i] = NULL;
    }
    free(pTrie);
    return NULL;
}

trie *generateNode(void)
{
    int i;

    trie *newNode = malloc(sizeof(trie));

    newNode->flag = 0;
    for (i = 0; i < 26; i++)
        newNode->children[i] = NULL;

        return newNode;
}


int main(void)
{
      //read the number of the words in the dictionary
      // parse line  by line, and insert each word to the trie data structure
      //Initialize the trie, TA HINT (USE CALLOC)
      char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};



    // trie *myTrie = malloc(sizeof(trie));
    // myTrie->flag = 0;
    // for (int j = 0; j < 26; j++){
    //     myTrie->children[j] = NULL;
    // }

    trie *myTrie = generateNode();
    

      //for each work in pWords, add it to the trie
    for (int i = 0; i < 5; i++){
        
        insert(&myTrie, pWords[i]);
    }

    for (int i=0;i<5;i++){
          printf("\t%s : %d\n",pWords[i], numberOfOccurances(myTrie, pWords[i]));
    }


    myTrie = deallocateTrie(myTrie);
    if (myTrie != NULL)
       printf("There is an error in this program\n");
    return 0;
}