#ifndef INVERTED_H
#define INVERTED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 27 
#define WORD_SIZE 100
#define TABLE_SIZE 50


typedef struct SubNode 
{
    char filename[100];
    int word_count;
    struct SubNode *link;
} SubNode;

typedef struct MainNode 
{
    char word[50];
    int file_count;
    SubNode *sub_link;
    struct MainNode *link;
} MainNode;

typedef struct SList 
{
    char filename[100];
    struct SList *link;
} SList;


void create_database(SList *file_list, MainNode *hashtable[]);
int get_index(char *word);
void to_lowercase(const char *src, char *dest);


void display_database(MainNode *hashtable[]);


void search_database(MainNode *hashtable[]);


void save_database(MainNode *hashtable[]);


void update_database(MainNode *hashtable[]);

#endif
