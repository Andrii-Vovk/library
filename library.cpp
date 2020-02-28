#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

#define MAXNAMELEN 100
#define MAXSTRLEN 100
#define MAXINTLEN 6

typedef struct book_node
{
    int id;
	char author[MAXNAMELEN];
	char name[MAXNAMELEN];
	int published;
	int pages;
	int price;

	struct book_node* next;
} book;

FILE* input;

book* removeElems(book* first, int minPages);
book* removeIdElems(book* first, int id);
void readList(FILE* fp, book** first);
void readKeybList(book** first);
void printList(book* first);
int checkIntInput();
void newestFive(book *first);
void printElem(book *print);
void giveid(book *first);
void insertNode(book** first, book* new_book);
void printIdElem(book* first, int elid);
int compare(book* one, book* two);
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
int main()
{
	book* firstBook = NULL;
	input = fopen("books.txt", "r");
	readList(input, &firstBook);
	fclose(input);
	printList(firstBook);
	printf("--------------5 Newest books-------------\n");
	newestFive(firstBook);
	removeElems(firstBook, 50);
	char choose;
	int count;
	int remid;
while(true)
{
	printf("If you want to add elems, enter a.\nIf you want to remove elems, press d.\n");
	scanf("%c", &choose);

	switch (choose)
	{
	case 'a':
		printf("How many elements do you want to add?\n");
		count = checkIntInput();
		for(int i = 0; i < count; i++)
		{
			getchar();
			readKeybList(&firstBook);
		}	
		getchar();
		printList(firstBook);
		 break;	
	case 'd':
		printList(firstBook);
		printf("Enter deleting id: ");
		remid = checkIntInput();
		removeIdElems(firstBook, remid); getchar(); break;
		printList(firstBook);
	default: return 0;
		break;
	}
}
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void toFile(FILE* output, book* elem)
{
	output = fopen("books.txt", "a+");
	
	fprintf(output, "\n%s\t%s\t%d\t%d\t%d", elem->author, elem->name, elem->published, elem->pages, elem->price);

	fclose(output);
}

void giveid(book *first)
{
    if(!first)
        return;
    else if(!first->next)
    {
        first->id = 1;
        return;
    }

    book *curr = first->next;
    book *prev = first;
    first->id = 1;
    while(curr)
    {
        curr->id = prev->id + 1;
        prev = curr;
        curr = curr->next;
    }
    return;
}

void newestFive(book *first)
{
    book *top[5];
	book *curr = first;
	int max = 0;
	int check = 0;
	for(int i = 0; i < 5; i++)
	{
		max = 0;
		curr = first;
		while (curr)
		{
			if(max < curr->published)
			{
				for(int j = 0; j < 5; j++)
					if(curr == top[j])
						check = 1;
				if(check == 0)
				{
					max = curr->published;
					top[i] = curr;
				}
			}
			check = 0;
			curr = curr->next;
		}
	}
	for(int i = 0; i < 5; i++)
		printElem(top[i]);
}
int compare(book* one, book* two, char mode)
{
	switch (mode)
	{
    case 'a':return strcmp(one->author, two->author); break;
	case 'n':return strcmp(one->name, two->name); break;
	case 'y':return (one->published) - (two->published); break;
	case 'p':return (one->pages) - (two->pages); break;
	
	default: return -300; break;
	}
	
}

void insertNode(book** first, book* new_book)
{
	if (!(*first))
	{
		(*first) = new_book;
		(*first)->next = NULL;
	}
	else
	{
		int compared = compare(*first, new_book, 'a');
		if (compared <= 0)
		{
			(new_book)->next = *first;
			(*first) = new_book;
            giveid(*first);
			return;
		}

		book* curr = *first;
		while (curr->next)
		{
			if (compare(curr, new_book, 'a') > 0 && compare(curr->next, new_book, 'a') <= 0)
			{
				new_book->next = curr->next;
				curr->next = new_book;
                giveid(*first);
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
    giveid(*first);
}

void printList(book* first)
{
	printf("----------------------------------------------------------------------------------------\nAuthor\t\t\t\t Name\t\t\t      Published\t  Pages\t  Price|\n----------------------------------------------------------------------------------------\n");
	book* curr = first;
	do
	{
		printf("%-20s| %-40s| %4d\t| %4d\t| %4d |\n",curr->author, curr->name, curr->published, curr->pages, curr->price);
		curr = curr->next;
	} while (curr);
	printf("----------------------------------------------------------------------------------------\n\n");
}

void printIdElem(book* first, int elid)
{
    book* curr = first;
    while (curr)
    {
       if(curr->id = elid)
       {
        printf("%-20s| %-40s| %4d\t| %4d\t| %4d |\n",curr->author, curr->name, curr->published, curr->pages, curr->price);
        return;
       } 
       curr = curr->next; 
    }
    return;
}
void printElem(book *print)
{
	book *curr = print;
	printf("%-20s| %-40s| %4d\t| %4d\t| %4d |\n",curr->author, curr->name, curr->published, curr->pages, curr->price);
}

void readList(FILE* fp, book** first)
{
	char* tmp;
	char str[MAXSTRLEN];
	while (fgets(str, MAXSTRLEN, fp))
	{
		book* new_book = (book*)malloc(sizeof(book));

		tmp = strtok(str, "\t");
		strcpy(new_book->author, tmp);
		tmp = strtok(NULL, "\t");
		strcpy(new_book->name, tmp);
		tmp = strtok(NULL, "\t");
		new_book->published = strtol(tmp, &tmp, 10);
		tmp = strtok(NULL, "\t");
		new_book->pages = strtol(tmp, &tmp, 10);
		tmp = strtok(NULL, "\t");
		new_book->price = strtol(tmp, &tmp, 10);
		new_book->next = NULL;

		insertNode(first, new_book);
	}

	fclose(fp);
}

void readKeybList(book** first)
{
	char tmp[MAXSTRLEN];
	int itmp;
		book* new_book = (book*)malloc(sizeof(book));
		printf("Enter author: ");
		fgets(tmp, MAXSTRLEN-1, stdin);
		strtok(tmp, "\n");
		strcpy(new_book->author, tmp);

		printf("Enter book name: ");
		fgets(tmp, MAXSTRLEN-1, stdin);
		strtok(tmp, "\n");
		strcpy(new_book->name, tmp);

		printf("Enter publishing year: ");
		itmp = checkIntInput();
		//scanf("%d", &itmp);
		new_book->published = itmp;

		printf("Enter pages count: ");
		itmp = checkIntInput();
		//scanf("%d", &itmp);
		new_book->pages = itmp;

		printf("Enter price: ");
		itmp = checkIntInput();
		//scanf("%d", &itmp);
		new_book->price = itmp;

		new_book->next = NULL;

		insertNode(first, new_book);
		toFile(input, new_book);
}


book* removeElems(book* first, int minPages)
{
	book* curr = first, *prev = NULL;
	while (curr)
	{
		if (!prev && (curr->pages < minPages))
		{
			first = curr->next;
			free(curr);
			curr = first;
			continue;
		}

		if (curr->pages < minPages)
		{
			prev->next = curr->next;
			free(curr);
			curr = prev->next;
			continue;
		}

		prev = curr;
		curr = curr->next;
	}
    giveid(first);
	return first;
}


book* removeIdElems(book* first, int id)
{
	book* curr = first, *prev = NULL;
	
	for(int i = 0; i < id-1; i++)
	{
		prev = curr;
		curr = curr->next;

		if(curr == NULL)
		{
			printf("ERROR! There is no node with such id\n");
			return first;
		}
	}
		if(prev == first)
		{
		first == prev->next;
		free(prev);
        giveid(first);
		return first;
		}
		else if(curr->next == NULL)
		{
			free(curr);
			prev->next = NULL;
            giveid(first);
			return first;
		}
	
		prev->next = curr->next;
		free(curr);
        giveid(first);
		return first;
	

}

int checkIntInput()
{
	char tmp[MAXINTLEN];
	int check = 0;
	int result;
	while(true)
	{
		scanf("%s", &tmp);
		for(int i = 0; i < strlen(tmp); i++)
		{
			if(!isdigit(tmp[i]))
			check = 1;	
		}
		if(check == 0) break;

		check = 0;
		printf("Enter valid number:");
	}
	result = atoi(tmp);
	return result;
}