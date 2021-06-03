#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 100

int main(int argc, char* argv[])
{
	char nume_fisier[SIZE];

	int pd[2];
	int res = pipe(pd);

	if (res == -1) {
		perror("pipe() error");
		exit(EXIT_FAILURE);
	}

	printf("Un nume de fisier : ");
	scanf("%s", &nume_fisier);

	write(pd[1], &nume_fisier, sizeof(char[SIZE]));

	int id = fork();

	if (id == 0) {

		close(pd[1]);

		char fisier[SIZE];

		read(pd[0], &fisier, sizeof(char[SIZE]));

		char command[100];
		sprintf(command, "file %s", fisier);

		FILE* file = popen(command, "r");
		char nume[100];
		fscanf(file, "%s", &nume);
		printf("\n  ");
		while (fscanf(file, "%s", &nume) != EOF) {
			printf("%s ", nume);
		}
		fclose(file);

		printf("\n\n");

		close(pd[0]);
		exit(0);
	}

	int status;
	wait(&status);

	return 0;
}
