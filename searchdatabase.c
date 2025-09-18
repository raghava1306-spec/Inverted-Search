
#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <ctype.h>      
#include "inverted.h"   


static int normalize_token(const char *in, char *out, size_t out_size)
{
    int start = 0; 
    int end = (int)strlen(in) - 1; 
// Skip non-alphanumeric 
    while (end >= start && !isalnum((unsigned char)in[end])) end--; 

    if (start > end) return 0; 

    size_t k = 0; // Output index
    for (int i = start; i <= end && k + 1 < out_size; ++i) 
    {
        out[k++] = (char)tolower((unsigned char)in[i]); 
    }

    out[k] = '\0'; 
    return (k > 0); 
}

/* Function to search for a word in the hashtable */
void search_database(MainNode *hashtable[])
{
    char raw[WORD_SIZE]; // Buffer to store user input
    printf("Enter the word to search: ");
    if (scanf("%99s", raw) != 1) 
    {        
        printf("Input error.\n");
        return;
    }

    char token[WORD_SIZE]; // Buffer for cleaned word
    if (!normalize_token(raw, token, sizeof(token))) 
    {   
        printf("Invalid search token.\n");
        return;
    }

    int index; // Hash index for the word
    if (isalpha((unsigned char)token[0]))                
        index = token[0] - 'a'; // Map 'a'-'z' to 0-25
    else
        index = SIZE - 1;// Non-alphabet words go to last index

    if (index < 0 || index >= SIZE) 
    {
        printf("Invalid index.\n");
        return;
    }

    MainNode *cur = hashtable[index]; 
    if (!cur) 
    {                                        
        printf("The word '%s' is not found in any file.\n", raw);
        return;
    }

    while (cur) {         
        if (strcmp(cur->word, token) == 0) 
        {             
            printf("the word %s is present %d file(s)\n", raw, cur->file_count);
            SubNode *s = cur->sub_link; 
            while (s) {                       
                printf("in file %s for %d times\n", s->filename, s->word_count);
                s = s->link; 
            }
            return; 
        }
        cur = cur->link; 
    }

    printf("The word '%s' is not found in any file.\n", raw); 
}
