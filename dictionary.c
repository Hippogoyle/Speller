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
//#define LENGTH 45
#define DSIZE 26 

/* Node Maker */
typedef struct node
{
    char word[46];
    struct node *next;
}node;
    
/* make hash table */
node *hash_table[DSIZE];



int key(const char*);
char dline[LENGTH + 1];

double dwordcount = 0;

int dindex = 0;
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    
    int len = strlen(word);
    char test[len + 1];
    int i;
    for( i = 0; i < len; i++)
    {
        test[i] = tolower(word[i]);    
    }
   // i++;
    test[i] = '\0';
    // run word through hash_key to find bucket
    dindex = key(test);
    
    // check nodes in bucket for word with strcmp until true or NULL
    int compare;
    
    node *cursor = hash_table[dindex];

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
    /* declare a file pointer open an existing file for reading*/
    FILE *dfp = fopen(dictionary, "r");

    /* Check DICTIONARY file */
    if (dfp != NULL)
    {
        /* scan in words to hashtable */
        int c;
        while (!feof(dfp))
        {
            node *new_node = malloc(sizeof(node));
            int i = 0;
            while ((c = fgetc(dfp))!= '\n')
            { 
                if(c <= 0)
                {
                    break;    
                }
                new_node->word[i] = c;
                i++;
            }
            new_node->word[i] = '\0';
  
            /* Hash function*/
            dindex = key(new_node->word);
        
            /* place new node in hash table */
            new_node->next = hash_table[dindex];
            hash_table[dindex] = new_node;

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
        return dwordcount;
}
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
   
    for(int i = 0; i <= DSIZE; i++)
    { 
        node *cursor = hash_table[i];
        
        while(cursor != NULL)
        {
        node *temp = cursor;
        cursor = cursor->next;
        free(temp);

        }   
    }
  
    return true;
}



int key(const char* word)
{
/*    int n = (((int)word[0]<<2) + ((int)word[1]<<1) + ((int)word[2]<<2) + ((int)word[3]) + ((int)word[3])*/
/*            + ((int)word[4]) + ((int)word[5])+ ((int)word[4]) + ((int)word[5]) + ((int)word[6]) + ((int)word[7])*/
/*            + ((int)word[8]) + ((int)word[9]<<3) + ((int)word[10])); */
    int n = (int)word[0] -'a';
     dindex = n % (DSIZE); //dindex = n & (DSIZE - 1); to speed things up a bit
     return dindex;
}
