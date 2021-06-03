#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE 100

// create and write to a FIFO

int main()
{
	char* fifo1 = "./fifo";

	int res = mkfifo(fifo1, 0666);
	if (res == -1)
	{
		perror("mkfifo() error");
		exit(EXIT_FAILURE);
	}

	int fd = open(fifo1, O_WRONLY);
	if (fd == -1)
	{
		perror("open() error");
		exit(EXIT_FAILURE);
	}

	char nume_fisier[SIZE];
	printf("Scrieti un nume de fisier : ");
	scanf("%s", &nume_fisier);

	write(fd, nume_fisier, sizeof(nume_fisier));

	close(fd);

	unlink(fifo1);

	return 0;
}

// read from a FIFO

int main()
{
    char* fifo1 = "./fifo";

    int fd = open(fifo1, O_RDONLY);
    if (fd == -1)
    {
        perror("open() error : ");
        exit(EXIT_FAILURE);
    }

    char buf[SIZE];
    read(fd, buf, SIZE);

    char command[SIZE];
    sprintf(command, "file %s", buf);

    FILE* file = popen(command, "r");
    char nume[100];

    printf("\n     ");
    while(fscanf(file, "%s", &nume) != EOF)
    {
        printf("%s ", nume);
    }

    fclose(file);

    printf("\n\n");

    close(fd);

    return 0;
}
