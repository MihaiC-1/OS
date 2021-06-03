#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 100

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("\n   Trebuie dat ca si argument un fisier si un cuvand!\n\n");
        exit(1);
    }

    // obtinere cuvant, ce trebuie sters, din linia de comanda
    char word[STRING_SIZE];
    strcpy(word, argv[1]);

	char word_2[STRING_SIZE];
	strcpy(word_2, argv[1]);
	int p = word_2[0];
	word_2[0] = p-32;

    // obtinere nume fisier din linia de comanda
    char file_name[STRING_SIZE];
    strcpy(file_name, argv[2]);

    char name[STRING_SIZE];
    strcpy(name, "f.txt");

	// deschidere fisiere

    FILE* temp = fopen(name, "w");
    FILE* file = fopen(file_name, "r");

    if (file == NULL)
    {
        perror("fopen() error");
		exit(EXIT_FAILURE);
	}

    // citire si scriere fisier
	int counter = 0;
	int c, i = 0;
	char ch;
	char wordd[STRING_SIZE];

	c = fgetc(file);

	while (c != EOF)
	{
		if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		{
			ch = c;
			wordd[i] = ch;
			i++;
		}
		else
		{
			if (strcmp(word, wordd) == 0)
			{
				fprintf(temp, "");
				counter++;
			}
			else if (strcmp(word_2, wordd) == 0)
			{
				fprintf(temp, "");
				counter++;
			}
			else
			{
				fprintf(temp, "%s", wordd);
			}
			for (i = 0; i < STRING_SIZE; i++)
			{
				wordd[i] = '\0';
			}
			fputc(c, temp);
			i = 0;
		}
		c = fgetc(file);
	}

    // inchidere fisier
    fclose(file);
    fclose(temp);

    // stergere fisier original
    remove(file_name);
    rename(name, file_name);
    printf("Au fost facute %d stergeri ale cuvantului '%s'. \n", counter, word);

	return 0;
}

