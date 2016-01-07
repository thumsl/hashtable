#include <stdio.h>

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

int main(int argc, char *args[])
{
	if (argc < 2)
		error("No file informed.\n");

	/*
		read file (args[1]) and send each word found
		(characters between spaces) to the hash table
	*/

	char s[MAX_WORD_SIZE];
	scanf("%s", s);

	while (s[0] != ' ') {
		printf("The hash for %s is %d.\n", s, hash(s));
		scanf("%s", s);
	}

	return 0;
}
