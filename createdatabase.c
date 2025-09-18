
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "inverted.h"


static int normalize_token(const char *in, char *out, size_t out_size)
{
    int start = 0;
    int end = (int)strlen(in) - 1;

    // Skip non-alphanumeric chars at start
    while (start <= end && !isalnum((unsigned char)in[start])) 
        start++;
    // Skip non-alphanumeric chars at end
    while (end >= start && !isalnum((unsigned char)in[end])) 
        end--;

    if (start > end) 
    return 0; 

    size_t k = 0;
    // Copy and convert to lowercase
    for (int i = start; i <= end && k + 1 < out_size; ++i) 
    {
        out[k++] = (char)tolower((unsigned char)in[i]);
    }
    out[k] = '\0'; 
    return (k > 0); 
}

//build the inverted index database
void create_database(SList *file_list, MainNode *hashtable[])
{
    // Initialize all hash table to NULL
    for (int i = 0; i < SIZE; ++i) 
    hashtable[i] = NULL;

    
    for (SList *f = file_list; f != NULL; f = f->link) 
    {
        FILE *fp = fopen(f->filename, "r"); 
        if (!fp) 
        {
            fprintf(stderr, "Warning: cannot open '%s'. Skipping.\n", f->filename);
            continue; 
        }

        char raw[WORD_SIZE];
        while (fscanf(fp, "%99s", raw) == 1) 
        {
            char token[WORD_SIZE];
        
            if (!normalize_token(raw, token, sizeof(token))) 
            continue;

            // Compute hash index: a-z = 0-25, others = SIZE-1
            int index;
            if (isalpha((unsigned char)token[0]))
                index = token[0] - 'a';
            else
                index = SIZE - 1;

            // Search for main node
            MainNode *m = hashtable[index];
            MainNode *found = NULL;
            while (m) {
                if (strcmp(m->word, token) == 0) 
                { 
                    found = m; 
                    break; 
                }
                m = m->link;
            }

            if (!found) 
            {
                // Create new main node 
                MainNode *newm = (MainNode*)malloc(sizeof(MainNode));

                if (!newm) 
                {
                     fprintf(stderr,"malloc failed\n"); 
                     fclose(fp); 
                     return; 
                }

                strncpy(newm->word, token, sizeof(newm->word)-1);
                newm->word[sizeof(newm->word)-1] = '\0';
                newm->file_count = 1;
                newm->sub_link = NULL;

                // Create subnode
                SubNode *s = (SubNode*)malloc(sizeof(SubNode));

                if (!s) 
                {
                     fprintf(stderr,"malloc failed\n"); 
                     fclose(fp); 
                     return; 
                }

                strncpy(s->filename, f->filename, sizeof(s->filename)-1);
                s->filename[sizeof(s->filename)-1] = '\0';
                s->word_count = 1;
                s->link = NULL;

                // Link subnode to main node
                newm->sub_link = s;

                // Insert new main node 
                newm->link = hashtable[index];
                hashtable[index] = newm;
            } 
            else 
            {
                // search subnode
                SubNode *sn = found->sub_link;
                SubNode *sfound = NULL;
                while (sn) {
                    if (strcmp(sn->filename, f->filename) == 0) 
                    { 
                        sfound = sn; 
                        break; 
                    }
                    sn = sn->link;
                }

                if (!sfound) 
                {
                    // Create new subnode 
                    SubNode *s = (SubNode*)malloc(sizeof(SubNode));

                    if (!s) 
                    { 
                        fprintf(stderr,"malloc failed\n"); 
                        fclose(fp); 
                        return; 
                    }

                    strncpy(s->filename, f->filename, sizeof(s->filename)-1);
                    s->filename[sizeof(s->filename)-1] = '\0';
                    s->word_count = 1;

                    // Insert subnode
                    s->link = found->sub_link;
                    found->sub_link = s;
                    found->file_count++; 
                } 
                else 
                {
                    sfound->word_count++;
                }
            }
        } 

        fclose(fp); 
    }
}
