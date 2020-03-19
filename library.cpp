#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include "funcs.h"
#define MAXNAMELEN 100
#define MAXSTRLEN 100
#define MAXINTLEN 6

FILE* input;	 //main file with books database


//------------------------------------------------------------------------------
//-------------------Main function----------------------------------------------
//------------------------------------------------------------------------------
int main ()
{
	book* firstBook = NULL;
	input = fopen ("books.txt", "r");

	readList (input, &firstBook);

	fclose (input);

	printList (firstBook);

	char choose;
	int count;
	int remid;
	while (true)
	{
		printf ("Add elems - enter 'a'.\nRemove elems - enter 'd'.\n");
		printf ("Search by author - enter 's'\nPrint all - enter 'p'\n");
		printf ("Edit elem - enter 'e'\nExit - 'x'\n");
		scanf ("%c", &choose);

		switch (choose)
		{
		case 'a': {
			printf ("How many elements do you want to add?\n");
			count = checkIntInput ();
			for (int i = 0; i < count; i++)
			{
				getchar ();
				readKeybList (&firstBook, input);
			}
			getchar ();
			printList (firstBook);
			break;
		}
		case 'd': {
			printList (firstBook);
			printf ("Enter deleting id: ");
			remid = checkIntInput ();
			removeIdElems (firstBook, remid, input); getchar (); break;
			printList (firstBook);
		case 's': {
			printf ("Enter Author name: ");
			authorSearch (firstBook); 
			getchar ();
			break;
		}
		case 'p': {
			printList (firstBook);
			getchar ();
			break;
		}
		case 'e': {
			printf ("Enter editing id: ");
			int idd = checkIntInput ();
			editElem (firstBook, idd, input);
			break;
		}
		default: return 0;
			break;
		}
		}
	}
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
