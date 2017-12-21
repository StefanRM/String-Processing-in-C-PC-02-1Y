#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 12000
#define DELIMITATORS " ,?!\'\""

int create_list(int n, char **lista, int *nr_aparitii, char **text, int N)
{
	int i, j, count;
	char *line, *token;

	line = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	token = (char *)malloc((MAX_CHARS + 1) * sizeof(char));

	for (i = 0; i < N; i++) {
		strcpy(line, text[i]);

		token = strtok(line, DELIMITATORS);

		if ((token != NULL) && (n == 0) && (token[0] != '\n')) {
			strcpy(lista[n], token);
			nr_aparitii[n] = 1;
			n = n + 1;
			token = strtok(NULL, DELIMITATORS);
		}

		while (token != NULL) {
			count = 0;

			for (j = 0; j < n; j++) {
				if ((strcmp(lista[j], token) == 0)
				    && (token[0] != '\n')) {
					nr_aparitii[j] = nr_aparitii[j] + 1;

					break;
				}
			}

			if ((j == n) && (token[0] != '\n')) {
				strcpy(lista[n], token);
				nr_aparitii[n] = 1;
				n = n + 1;
			}

			token = strtok(NULL, DELIMITATORS);
		}
	}

	free(token);
	free(line);

	return n;
}

int max_nr_words(char **text, int N)
{
	int i, j, nr = 0;
	char *line, *token;

	line = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	token = (char *)malloc((MAX_CHARS + 1) * sizeof(char));

	for (i = 0; i < N; i++) {
		strcpy(line, text[i]);

		token = strtok(line, DELIMITATORS);

		while (token != NULL) {
			nr = nr + 1;
			token = strtok(NULL, DELIMITATORS);
		}
	}

	free(token);
	free(line);

	return nr;
}

void bubble_sort(int *nr_aparitii, char **lista, int n)
{
	int c, d, t;
	char *aux;

	aux = (char *)malloc((MAX_CHARS + 1) * sizeof(char));

	for (c = 0; c < (n - 1); c++) {
		for (d = 0; d < n - c - 1; d++) {
			if (nr_aparitii[d] < nr_aparitii[d + 1]) {
				t = nr_aparitii[d];
				nr_aparitii[d] = nr_aparitii[d + 1];
				nr_aparitii[d + 1] = t;
				strcpy(aux, lista[d]);
				strcpy(lista[d], lista[d + 1]);
				strcpy(lista[d + 1], aux);
			} else if (nr_aparitii[d] == nr_aparitii[d + 1]) {
				if (strcmp(lista[d], lista[d + 1]) > 0) {
					strcpy(aux, lista[d]);
					strcpy(lista[d], lista[d + 1]);
					strcpy(lista[d + 1], aux);
				}
			}
		}
	}

	free(aux);

	return;

}

int dist(char *word1, char *word2)
{
	int i, lungime1 = strlen(word1), lungime2 = strlen(word2), d = 0;

	if (lungime1 > lungime2) {
		for (i = 0; i < lungime2; i++) {
			d = d + abs(word1[i] - word2[i]);
		}
		for (i = lungime2; i < lungime1; i++) {
			d = d + abs('\0' - word1[i]);
		}
	} else {
		for (i = 0; i < lungime1; i++) {
			d = d + abs(word1[i] - word2[i]);
		}
		for (i = lungime1; i < lungime2; i++) {
			d = d + abs('\0' - word2[i]);
		}
	}

	return d;

}

int sim(char **lista1, char **lista2, int *nr_aparitii1, int n,
	int *nr_aparitii2, int m)
{
	int i, similitudine = 100 * abs(n - m), min;

	if (n < m) {
		min = n;
	} else {
		min = m;
	}

	for (i = 0; i < min; i++) {
		similitudine =
		    similitudine + (nr_aparitii1[i] +
				    nr_aparitii2[i]) * dist(lista1[i],
							    lista2[i]);
	}

	return similitudine;
}

int main(void)
{
	char **text1, **text2, *garbage, *token;
	int i, N, M, n = 0, m = 0, nr_max1, nr_max2;
	char **lista1, **lista2;
	int *nr_aparitii1, *nr_aparitii2;

	garbage = (char *)malloc((MAX_CHARS + 1) * sizeof(char));

	scanf("%d", &N);

	text1 = (char **)malloc(N * sizeof(char *));
	for (i = 0; i < N; i++) {
		text1[i] = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	}

	fgets(garbage, MAX_CHARS + 1, stdin);

	for (i = 0; i < N; i++) {
		fgets(text1[i], MAX_CHARS + 1, stdin);
		if ((text1[i][strlen(text1[i]) - 1] == '\n')
		    && (strlen(text1[i]) > 1)) {
			text1[i][strlen(text1[i]) - 1] = '\0';
		}

	}

	nr_max1 = max_nr_words(text1, N);

	lista1 = (char **)malloc((nr_max1 + 1) * sizeof(char *));

	for (i = 0; i < nr_max1; i++) {
		lista1[i] = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	}

	nr_aparitii1 = (int *)calloc(nr_max1, sizeof(int));

	scanf("%d", &M);

	text2 = (char **)malloc(M * sizeof(char *));
	for (i = 0; i < M; i++) {
		text2[i] = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	}

	fgets(garbage, MAX_CHARS + 1, stdin);
	free(garbage);

	for (i = 0; i < M; i++) {
		fgets(text2[i], MAX_CHARS + 1, stdin);
		if ((text2[i][strlen(text2[i]) - 1] == '\n')
		    && (strlen(text2[i]) > 1)) {
			text2[i][strlen(text2[i]) - 1] = '\0';
		}

	}

	nr_max2 = max_nr_words(text2, M);

	lista2 = (char **)malloc((MAX_CHARS + 1) * sizeof(char *));

	for (i = 0; i < nr_max2; i++) {
		lista2[i] = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	}

	nr_aparitii2 = (int *)calloc(nr_max2, sizeof(int));

	n = create_list(n, lista1, nr_aparitii1, text1, N);

	bubble_sort(nr_aparitii1, lista1, n);

	m = create_list(m, lista2, nr_aparitii2, text2, M);

	bubble_sort(nr_aparitii2, lista2, m);

	printf("%d\n", sim(lista1, lista2, nr_aparitii1, n, nr_aparitii2, m));

	free(nr_aparitii1);
	free(nr_aparitii2);

	// for(i=0; i < nr_max1; i++)
	// {
	//     free(lista1[i]);
	// }

	// free(lista1);

	// for(i=0; i < nr_max2; i++)
	// {
	//     free(lista2[i]);
	// }

	// free(lista2);

	// for(i=0; i < N; i++)
	// {
	//     free(text1[i]);
	// }

	// free(text1);

	// for(i=0; i < M; i++)
	// {
	//     free(text2[i]);
	// }

	// free(text2);

	return 0;
}
