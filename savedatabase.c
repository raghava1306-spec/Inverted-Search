
#include "inverted.h"

void save_database(MainNode *hashtable[])
{
    FILE *fp;
    char backup_filename[100];

    
    int empty = 1;
    for (int i = 0; i < SIZE; i++)
    {
        if (hashtable[i] != NULL) 
        {
            empty = 0;
            break; 
        }
    }

    
    if (empty)
    {
        printf("Database is empty. Nothing to save.\n");
        return;
    }

    
    printf("Enter the backup filename: ");
    scanf("%s", backup_filename);

    
    fp = fopen(backup_filename, "w");
    if (fp == NULL) 
    {
        perror("Error opening backup file");
        return;
    }

    
    for (int i = 0; i < SIZE; i++)
    {
        MainNode *mtemp = hashtable[i]; 
        while (mtemp != NULL) 
        {
            // Save index, word, and file count to backup file
            fprintf(fp, "#%d;%s;%d;", i, mtemp->word, mtemp->file_count);

            SubNode *stemp = mtemp->sub_link;
            while (stemp != NULL)
            {
                fprintf(fp, "%s;%d;", stemp->filename, stemp->word_count);
                stemp = stemp->link; 
            }

            fprintf(fp, "#\n");
            mtemp = mtemp->link; 
        }
    }

    fclose(fp);
    printf("Database saved successfully in %s\n", backup_filename);
    
}
