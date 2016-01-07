#include <stdio.h>

#define TABLE_SIZE 50
#define error(x) { fprintf(stderr, x); return (1); }

int hash(char *string)
{
	int i, key = 0;
	for (i = 0; string[i] != '\0'; i++)
		key += string[i];

	return key % TABLE_SIZE;
}

int main(int argc, char *args[]) {
	if (argc < 2)
		error("No file informed.\n");
	printf("The hash for %s is %d.\n", args[1], hash(args[1]));

	return 0;
}
