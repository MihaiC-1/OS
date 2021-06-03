#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int convert(char a[])
{
	int nr = 0;
	int i;
	for (i=0; i<strlen(a); i++)
	{
		int n = a[i];
		nr = nr*10 + (n-48);
	}
	return nr;
}

int main(int argc, char* argv[])
{
	//if (argc < 3)
	//{
		//printf("\n      Trebuie date cel putin 2 numere ca si argumente. \n \n");
	//}

	//int n = argc-1;
	//int nr[n];
	int i;

	int n;
	printf("Cate numere se vor introduce : ");
	scanf("%d", &n);
	int nr[n];

	for (i=0; i<n; i++) {
		//nr[i] = convert(argv[i+1]);
		printf("Numarul %d : ", i+1);
		scanf("%d", &nr[i]);
	}

	int rez = 0;

	for (i=0; i<n; i++) {
		if (rez == 0) {
			rez = nr[i];
		}
		else {
			int aux = nr[i];
			int pid = fork();

			if (pid == -1) {
				perror("fork() error");
				exit(EXIT_FAILURE);
			}

			if (pid == 0) {
				while (aux != rez)
				{
					if (rez > aux) {
						rez = rez - aux;
					}
					else {
						aux = aux - rez;
					}
				}
				exit(aux);
			}

			int status;
			wait(&status);
			int tstat = WEXITSTATUS(status);
			rez = tstat;
		}
	}

	printf("CMMDC-ul numerelor date este : %d\n", rez);

	return 0;
}
