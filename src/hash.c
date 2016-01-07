#include <stdio.h>
#include "hash.h"

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

	print_table(t);
	return 0;
}
