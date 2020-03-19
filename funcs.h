#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

#ifndef LIBRAFUNCS_H
#define LIBRAFUNCS_H

typedef struct book_node book;

book* removeElems (book* first, int minPages, FILE* inp);
book* removeIdElems (book* first, int id, FILE* Filee);
void readList (FILE* fp, book** first);
void readKeybList (book** first, FILE* inp);
void printList (book* first);
int isEmptyFile (FILE* openedfile);
int checkIntInput ();
void authorSearch (book* first);
void editElem (book* first, int id, FILE* inp);
void resetFile (FILE* output, book* first); //rewrites the whole list to books.txt file
void printElem (book* print);
void toFile (FILE* output, book* elem);
void insertNode (book** first, book* new_book);
void printIdElem (book* first, int elid);
int compare (book* one, book* two, char mode);



#endif