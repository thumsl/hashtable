#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 50
#define MAX_WORD_SIZE 50

#define error(x) { fprintf(stderr, x); return (1); }

typedef struct table {
	char *word;
	int count;
	struct table *next;
} table;

int hash(char *string)
{
	int i, key = 0;
	for (i = 0; string[i] != '\0'; i++)
		key += string[i];

	return key % TABLE_SIZE;
}

void init_table(table *t)
{
	int i;

	for (i = 0; i < TABLE_SIZE; i++) {
		t[i].word = NULL;
		t[i].next = NULL;
		t[i].count = 0;
	}
}

int add_to_table(table *t, char *string)
{
	int key = hash(string);

	if (t[key].word == NULL) { 	// t[key] doesn't contain a word yet
		t[key].count++;
		t[key].word = malloc(sizeof(char) * MAX_WORD_SIZE);
		strcpy(t[key].word, string);
		return 1;
	}
	else {
		printf("the word is %s and the pointer next is %p\n", t[key].word, t[key].next);
		if (strcmp(t[key].word, string) == 0) { // [key] is the right position
			t[key].count++;
			return 1;
		}
		else if (t[key].next == NULL) { // collides with [key] but its the first collision
			t[key].next = malloc(sizeof(table));
			t[key].next -> word = malloc(sizeof(char) * MAX_WORD_SIZE);
			t[key].next -> next = NULL;
			t[key].next -> count = 1;
			strcpy(t[key].next -> word, string);
			return 0;
		}
		else { // collision
			table* aux = t[key].next;
			while (strcmp(aux -> word, string) != 0 && aux -> next != NULL)
				aux = aux -> next;

			if (strcmp(aux -> word, string) == 0) {
				aux -> count++;
				return 1;
			}
			else {
				aux -> next = malloc(sizeof(table));
				aux -> next -> word = malloc(sizeof(char) * MAX_WORD_SIZE);
				aux -> next -> next = NULL;
				aux -> next -> count = 1;
				strcpy(aux -> next -> word, string);
				return 0;
			}
		}
	}
}

int main(int argc, char *args[])
{
	if (argc < 2)
		error("No file informed.\n");

	/*
		read file (args[1]) and send each word found
		(characters between spaces) to the hash table
	*/

	table t[TABLE_SIZE];
	init_table(t);

	char s[MAX_WORD_SIZE];

	while (scanf("%s", s) && s[0] != '0') {
		printf("The hash for %s is %d.\n", s, hash(s));
		add_to_table(t, s);
	}

	int i;
	for (i = 0; i < TABLE_SIZE; i++) {

		if (i==0) putchar('\n');

		if (i < 10)
			printf(" [%d]: ", i);
		else
			printf("[%d]: ", i);

		if (t[i].word != NULL)
			printf("%s (%d) --> ", t[i].word, t[i].count);

		if (t[i].next != NULL) {
			table *aux = t[i].next;
			while (aux != NULL) {
				printf("%s (%d) --> ", aux -> word, aux -> count);
				aux = aux -> next;
			}
		}

		putchar('\n');
	}

	return 0;
}
