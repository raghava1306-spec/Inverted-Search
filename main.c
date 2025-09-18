/*name-shridevi
date-15/08/2025
program for inverted search*/

#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include "inverted.h"   

int main(int argc, char *argv[]) 
{
    // Check if at least one file name is passed as a command-line argument
    if (argc < 2) 
    {
        printf("Usage: %s file1.txt file2.txt ...\n", argv[0]);
        return 1;
    }

    SList *file_list = NULL; // Head pointer for file linked list

    // Process each command-line argument (file name)
    for (int i = 1; i < argc; i++) 
    {
        char *filename = argv[i]; // Current file name

        // Validate file extension (.txt)
        char *dot = strrchr(filename, '.'); 
        if (!dot || strcmp(dot, ".txt") != 0) 
        {
            printf("Skipping: Not a .txt file -> %s\n", filename);
            continue;
        }

        // Check if file exists
        FILE *fp = fopen(filename, "r");
        if (!fp) 
        {
            printf("Skipping: File does not exist -> %s\n", filename);
            continue;
        }

        // Check if file is empty
        fseek(fp, 0, SEEK_END); // Move to end of file
        long size = ftell(fp); // Get file size
        fclose(fp);
        if (size == 0) 
        {
            printf("Skipping: File is empty -> %s\n", filename);
            continue;
        }

        // Check for duplicate file in linked list
        int duplicate = 0;
        SList *temp = file_list;
        while (temp) 
        {
            if (strcmp(temp->filename, filename) == 0) 
            {
                duplicate = 1;
                break;
            }
            temp = temp->link;
        }
        if (duplicate) 
        {
            printf("Skipping: Duplicate file -> %s\n", filename);
            continue;
        }

        // Create new file node
        SList *new = malloc(sizeof(SList));
        strcpy(new->filename, filename); // Copy filename
        new->link = NULL; // End of list

        // Insert node into linked list
        if (!file_list) 
        {
            file_list = new; // First node
        } 
        else 
        {
            SList *last = file_list;
            while (last->link) last = last->link; // Traverse to last node
            last->link = new; // Append new node
        }
    }

    // Exit if no valid files found
    if (!file_list) 
    {
        printf("No valid files to process. Exiting.\n");
        return 1;
    }

    // Initialize hash table to NULL
    MainNode *hashtable[SIZE] = { NULL };

    int db_created = 0; // Flag for create database
    int db_updated = 0; // Flag for update database

    int choice;
    while (1) 
    {
        // Menu display
        printf("\n----- Inverted Search Menu -----\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Database\n");
        printf("4. Save Database\n");
        printf("5. Update Database\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        // Input validation
        if (scanf("%d", &choice) != 1) 
        {
            printf("Invalid input. Please enter a number between 1 and 6.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        // Menu choices
        switch (choice) 
        {
            case 1: // Create Database
                if (db_created) 
                {
                    printf("Database already created.\n");
                }
                else if (db_updated) 
                {
                    printf("Database already updated from backup. Cannot create now.\n");
                }
                else 
                {
                    create_database(file_list, hashtable); // Build DB from files
                    db_created = 1; // Mark created
                    printf("Database created successfully.\n");
                }
                break;

            case 2: // Display Database
                display_database(hashtable);
                break;

            case 3: // Search Database
                search_database(hashtable);
                break;

            case 4: // Save Database to backup file
                save_database(hashtable);
                break;

            case 5: // Update Database from backup
                if (db_created) 
                {
                    printf("Database already created. Cannot update now.\n");
                }
                else if (db_updated) 
                {
                    printf("Database already updated. You cannot update again.\n");
                }
                else 
                {
                    update_database(hashtable); // Load DB from backup file
                    db_updated = 1; // Mark updated
                }
                break;

            case 6: // Exit program
                printf("Exiting...\n");
                return 0;

            default: // Invalid choice
                printf("Invalid choice. Please enter 1-6.\n");
        }
    }
}
