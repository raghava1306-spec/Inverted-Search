
#include <stdio.h>
#include "inverted.h"

void display_database(MainNode *hashtable[])
{
    //table header 
    printf("%-10s%-15s%-15s%-20s%-15s\n", "[index]", "[word]", "[filecount]", "[filename]", "[wordcount]");

    //hash table
    for (int i = 0; i < SIZE; i++)
    {
        
        MainNode *main = hashtable[i];
        while (main != NULL)
        {
            
            SubNode *sub = main->sub_link;
            int first = 1; // Flag 

            // Traverse all sub nodes
            while (sub != NULL)
            {
                if (first)
                {
                    // Print main node details for the first sub node
                    printf("%-10d%-15s%-15d%-20s%-15d\n",i, main->word, main->file_count, sub->filename, sub->word_count);
                    first = 0; 
                }
                else
                {
                    // Print sub node 
                    printf("%-44s%-25s%-20d\n", "", sub->filename, sub->word_count);
                }
                sub = sub->link; // next sub node
            }

            main = main->link; // next main node 
        }
    }
}
