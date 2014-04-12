/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 *
 * By Jerry Johnson  
 ***************************************************************************/
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"


/* Node Maker */
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}node;
    
/* make hash table */
struct node hash_table[SIZE];

int key(const char* );
char dline[46];
char *dword;
int dwordcount = 0;
char c;
int dindex = 0;
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO

    /* prep word for case insensitivity */
    char test[46];
    for (int i =0; i < 45; i++)
    {
        test[i] = tolower(word[i]);
    }
    
    /* run word through hash_key to find bucket */
    dindex = key(test);
    
    /* check nodes in bucket for word with strcmp until true or NULL */
    int compare;
    
    node *cursor = &hash_table[dindex];

    while (cursor != NULL)
    {
        compare = strcmp(test, cursor->word);
        if (compare == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    /* declare a file pointer */
    FILE *dfp = NULL;
    
    /* open an existing file for reading */
    dfp = fopen(dictionary, "r");
    
    /* Check DICTIONARY file */
    if (dfp != NULL)
    {
        /* scan in words to hashtable */
        while (!feof(dfp))
        {

            /* get the next word from file */
            node* new_node = malloc(sizeof(node));
            fscanf(dfp, "%s", new_node->word);
            
            /* Hash function*/
            /* add up all the chars and modulo by x to get a key*/
            dindex = key(new_node->word);
        
            /* place new node in hash table */
            if (hash_table[dindex].next == NULL)
            {
                hash_table[dindex] = *new_node;
            }
            else
            {
                new_node->next = &hash_table[dindex];
                hash_table[dindex] = *new_node;
            }
            dwordcount++;

        }
            fclose(dfp);
            return true; 
    }     
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    //
    if (load)
    {
        return dwordcount;
    }
    return 0;
}
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    //
    node* temp = malloc(sizeof(node));
    
    for(int i = SIZE; i > 0; i--)
    { 
        while(hash_table[i].next != NULL)
        {
            temp = &hash_table[i];
            hash_table[i] = *hash_table[i].next;
            free(temp);
        }
           
    }
    return true;
}



int key(const char* word)
{
    int n = (((int)word[0]) + ((int)word[1]) + ((int)word[2]) + ((int)word[3])
            + ((int)word[4]) + ((int)word[5]) + ((int)word[6]) + ((int)word[7])
            + ((int)word[8]) + ((int)word[9]) + ((int)word[10])); 

     dindex = n % (SIZE); //dindex = n & (SIZE - 1); to speed things up a bit
     return n;
}
