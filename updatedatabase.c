
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inverted.h"

void update_database(MainNode *hashtable[])
{
    char filename[50]; 
    FILE *fp; 

    printf("Enter the backup file name: ");  
    scanf("%s", filename);  

    fp = fopen(filename, "r");  
    if (fp == NULL)  
    {
        printf("Error: Unable to open file %s\n", filename);
        return;  
    }

    char line[1000]; 
    if (fgets(line, sizeof(line), fp) == NULL || line[0] != '#')
    {
        printf("Error: Invalid backup file format.\n");
        fclose(fp);  
        return;
    }

    
    for (int i = 0; i < 27; i++)
    {
        hashtable[i] = NULL;
    }


    while (fgets(line, sizeof(line), fp))
    {
        int index; 
        char word[50]; 
        int file_count; 

        
        if (sscanf(line, "%d %s %d", &index, word, &file_count) != 3)
            continue;  

        
        MainNode *mnew = malloc(sizeof(MainNode));
        strcpy(mnew->word, word);
        mnew->file_count = file_count;
        mnew->sub_link = NULL;

        
        mnew->link = hashtable[index];
        hashtable[index] = mnew;

        char fname[50];  
        int word_count;  
        
        for (int i = 0; i < file_count; i++)
        {
            fscanf(fp, "%s %d", fname, &word_count);

            
            SubNode *snew = malloc(sizeof(SubNode));
            strcpy(snew->filename, fname);  // Store file name
            snew->word_count = word_count;

            snew->link = mnew->sub_link;
            mnew->sub_link = snew;
        }
    }

    fclose(fp);  
    printf("Database updated from backup file successfully.\n");  
}
