#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include "funcs.h"

typedef struct book_node
{
	int id;
	char author[100];
	char name[100];
	int published;
	int pages;
	int price;

	struct book_node* next;
}book;


//Checks if user inputs INTEGER
//If not, asks to input again
//EXAMPLE: int a = checkInput();
int checkIntInput ()
{
	char tmp[100];
	int check = 0;
	int result;
	while (true)
	{
		scanf ("%s", &tmp);
		for (int i = 0; i < strlen (tmp); i++)
		{
			if (!isdigit (tmp[i]))
				check = 1;
		}
		if (check == 0) break;

		check = 0;
		printf ("Enter valid number:");
	}
	result = atoi (tmp);
	return result;
}


//Asks for string, then displays all elements based on author field
void authorSearch (book* first)
{
	book* curr = first;
	int counter = 1;

	char searched[50];
	scanf ("%s", &searched);

	while (curr)
	{
		if (strstr ((curr->author), searched) != NULL)
		{
			printElem (curr);
		}
		curr = curr->next;
	}
	return;
}


//Edits one particular element, defined by id in func arguments
//Asks which field to edit; than reads data and puts in that field
void editElem (book* first, int id, FILE* inp)
{
	book* curr = first;

	for (int i = 1; i < id; i++)
	{
		curr = curr->next;

		if (!curr)
		{
			printf ("No such elem!\n");
			return;
		}
	}
	printElem (curr);
	printf("You want to edit:\n1 - Author\n2 - book name\n3 - Publishment year\n");
	printf ("4 - pages count\n5 - price\n6 - cancel\n");
	char buffer[100];
	int choice = checkIntInput();
	
	if (choice == 6) return;
	getchar ();
	printf ("Enter new value: ");
	switch (choice)
	{
	case 1: {
		fgets (buffer, 100, stdin);
		strtok (buffer, "\n");
		strcpy (curr->author, buffer);
		break;
	}
	case 2: {
		fgets (buffer, 100, stdin);
		strtok (buffer, "\n");
		strcpy (curr->name, buffer);
		break;
	}
	case 3: {
		curr->published = checkIntInput ();
		getchar ();
		break;
	}
	case 4: {
		curr->pages = checkIntInput ();
		getchar ();
		break;
	}
	case 5: {
		curr->price = checkIntInput ();
		getchar ();
		break;
	}
	default:
		break;
	}
	resetFile (inp, first);
}


//checks if file is empty
int isEmptyFile (FILE* openedfile)
{
	return getc (openedfile) == EOF ? 1 : 0;
}

//rewrites the whole list to file
void resetFile (FILE* output, book* first) 
{
	output = fopen ("books.txt", "w");
	book* curr = first;

	while (curr)
	{
		if (!isEmptyFile (output))
			fprintf (output, "\n%s\t%s\t%d\t%d\t%d", curr->author, curr->name, curr->published, curr->pages, curr->price);
		else
			fprintf (output, "%s\t%s\t%d\t%d\t%d", curr->author, curr->name, curr->published, curr->pages, curr->price);

		curr = curr->next;
	}

	fclose (output);
}


//writes an element into output
void toFile (FILE* output, book* elem)
{
	output = fopen ("books.txt", "a+");

	if (!isEmptyFile (output))
		fprintf (output, "\n%s\t%s\t%d\t%d\t%d", elem->author, elem->name, elem->published, elem->pages, elem->price);
	else
		fprintf (output, "%s\t%s\t%d\t%d\t%d", elem->author, elem->name, elem->published, elem->pages, elem->price);

	fclose (output);
}




//returns negative value, if one < two, 0 if equal, positive if one > two
//comparing modes:
//a - authors, n - book names, y - publishment year, p - pages count
int compare (book* one, book* two, char mode)
{
	switch (mode)
	{
	case 'a':return strcmp (one->author, two->author); break;
	case 'n':return strcmp (one->name, two->name); break;
	case 'y':return (one->published) - (two->published); break;
	case 'p':return (one->pages) - (two->pages); break;

	default: return -300; break;
	}

}


//Inserts a node into list, autimaticaly sorts based on author field by descending
void insertNode (book** first, book* new_book)
{
	if (!(*first))
	{
		(*first) = new_book;
		(*first)->next = NULL;
	}
	else
	{
		int compared = compare (*first, new_book, 'a');
		if (compared <= 0)
		{
			(new_book)->next = *first;
			(*first) = new_book;
			return;
		}

		book* curr = *first;
		while (curr->next)
		{
			if (compare (curr, new_book, 'a') > 0 && compare (curr->next, new_book, 'a') <= 0)
			{
				new_book->next = curr->next;
				curr->next = new_book;
				return;
			}
			else
			{
				curr = curr->next;
			}
		}

		curr->next = new_book;
		new_book->next = NULL;
	}
}


//prints the whole list
void printList (book* first)
{
	printf ("----------------------------------------------------------------------------------------\nAuthor\t\t\t\t Name\t\t\t      Published\t  Pages\t  Price|\n----------------------------------------------------------------------------------------\n");
	book* curr = first;
	do
	{
		printf ("%-20s| %-40s| %4d\t| %4d\t| %4d |\n", curr->author, curr->name, curr->published, curr->pages, curr->price);
		curr = curr->next;
	} while (curr);
	printf ("----------------------------------------------------------------------------------------\n\n");
}


//prints particular element taken by id
void printIdElem (book* first, int elid)
{
	book* curr = first;
	for (int i = 0; i < elid; i++)
	{
		curr = curr->next;

		if (!curr)
			return;
	}

	printf ("%-20s| %-40s| %4d\t| %4d\t| %4d |\n", curr->author, curr->name, curr->published, curr->pages, curr->price);
	return;
}

//prints particular element by pointer
void printElem (book* print)
{
	book* curr = print;
	printf ("%-20s| %-40s| %4d\t| %4d\t| %4d |\n", curr->author, curr->name, curr->published, curr->pages, curr->price);
}


//reads whole list from file
void readList (FILE* fp, book** first)
{
	char* tmp;
	char str[100];
	while (fgets (str, 100, fp))
	{
		book* new_book = (book*)malloc (sizeof (book));

		tmp = strtok (str, "\t");
		strcpy (new_book->author, tmp);
		tmp = strtok (NULL, "\t");
		strcpy (new_book->name, tmp);
		tmp = strtok (NULL, "\t");
		new_book->published = strtol (tmp, &tmp, 10);
		tmp = strtok (NULL, "\t");
		new_book->pages = strtol (tmp, &tmp, 10);
		tmp = strtok (NULL, "\t");
		new_book->price = strtol (tmp, &tmp, 10);
		new_book->next = NULL;

		insertNode (first, new_book);
	}

	fclose (fp);
}


//reads whole list from keyboard
void readKeybList (book** first, FILE* inp)
{
	char tmp[100];
	int itmp;
	book* new_book = (book*)malloc (sizeof (book));
	printf ("Enter author: ");
	fgets (tmp, 100 - 1, stdin);
	strtok (tmp, "\n");
	strcpy (new_book->author, tmp);

	printf ("Enter book name: ");
	fgets (tmp, 100 - 1, stdin);
	strtok (tmp, "\n");
	strcpy (new_book->name, tmp);

	printf ("Enter publishing year: ");
	itmp = checkIntInput ();
	//scanf("%d", &itmp);
	new_book->published = itmp;

	printf ("Enter pages count: ");
	itmp = checkIntInput ();
	//scanf("%d", &itmp);
	new_book->pages = itmp;

	printf ("Enter price: ");
	itmp = checkIntInput ();
	//scanf("%d", &itmp);
	new_book->price = itmp;

	new_book->next = NULL;

	insertNode (first, new_book);
	resetFile (inp, *first);
}

//removes element if its page count is less than minPages
book* removeElems (book* first, int minPages, FILE* inp)
{
	book* curr = first, * prev = NULL;
	while (curr)
	{
		if (!prev && (curr->pages < minPages))
		{
			first = curr->next;
			free (curr);
			curr = first;
			continue;
		}

		if (curr->pages < minPages)
		{
			prev->next = curr->next;
			free (curr);
			curr = prev->next;
			continue;
		}

		prev = curr;
		curr = curr->next;
	}
	resetFile (inp, first);
	return first;
}

//removes element by id
book* removeIdElems (book* first, int id, FILE* Filee)
{
	book* curr = first, * prev = NULL;

	for (int i = 0; i < id - 1; i++)
	{
		prev = curr;
		curr = curr->next;

		if (!curr) return first;
	}

	if (curr == first)
	{
		first = curr->next;
		free (curr);
	}
	else
	{
		prev->next = curr->next;
		free (curr);
	}

	resetFile (Filee, first);
	return first;
}

