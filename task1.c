#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 15000
#define DELIMITATORS " ,?!\'\""

int number_of_occurences(char **text, int nr_lines)
{
	int nr_occurences = 0, i;
	char *word, *token, *line;

	word = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	token = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	line = (char *)malloc((MAX_CHARS + 1) * sizeof(char));

	scanf("%s", word);

	for (i = 0; i < nr_lines; i++) {
		strcpy(line, text[i]);
		token = strtok(line, DELIMITATORS);

		while (token != NULL) {
			if (strcmp(token, word) == 0) {
				nr_occurences = nr_occurences + 1;
			}

			token = strtok(NULL, DELIMITATORS);
		}
	}

	free(word);
	free(token);
	free(line);

	return nr_occurences;
}

void replace_words(char **text, int nr_lines, char *word, char *replacer)
{
	int i;
	char *rest, *c;

	rest = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	if (strcmp(word, replacer) != 0) {
		for (i = 0; i < nr_lines; i++) {
			char *position_word = NULL;
			char *line = text[i];
			c = text[i];
			while (strstr(text[i], word) != NULL) {
				position_word = strstr(text[i], word);
				strcpy(rest, position_word + strlen(word));
				if (line == position_word) {
					if ((strchr
					     (DELIMITATORS,
					      (position_word +
					       strlen(word))[0]) != NULL)
					    ||
					    ((position_word +
					      strlen(word))[0] == '\0')) {
						strcpy(position_word, replacer);
						strcat(text[i], rest);
					} else {
						text[i] =
						    position_word +
						    strlen(word);
					}
				} else
				    if ((strchr
					 (DELIMITATORS,
					  (position_word - 1)[0]) != NULL)
					&&
					(((strchr
					   (DELIMITATORS,
					    (position_word +
					     strlen(word))[0]) != NULL)
					  || ((position_word + strlen(word))[0]
					      == '\0')))) {
					strcpy(position_word, replacer);
					strcat(text[i], rest);
				} else {
					text[i] = position_word + strlen(word);
				}

			}

			char *aux = strdup(line);
			text[i] = c;
			strcpy(text[i], aux);

			free(aux);

		}
	}

	free(rest);

	return;
}

int permute(char **text, int k, int nr_lines)
{
	char *word, *token, *line, *rest, *c;
	int i;

	word = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	token = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	line = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	rest = (char *)malloc((MAX_CHARS + 1) * sizeof(char));

	for (i = 0; i < nr_lines; i++) {
		char *row;
		row = text[i];
		char *position_word = NULL;
		c = text[i];
		strcpy(line, text[i]);

		token = strtok(line, DELIMITATORS);

		while (token != NULL) {
			strcpy(word,
			       token + (strlen(token) - k % strlen(token)));
			if (strlen(word) >= 1)
				strncat(word, token,
					strlen(token) - k % strlen(token));
			else
				strcpy(word, token);

			position_word = strstr(text[i], token);

			strcpy(rest, position_word + strlen(token));
			strcpy(position_word, word);
			strcat(text[i], rest);

			text[i] = position_word + strlen(token);

			token = strtok(NULL, DELIMITATORS);
		}

		char *aux = strdup(row);
		text[i] = c;
		strcpy(text[i], aux);
	}

	free(word);
	free(token);
	free(line);

	return;
}

int main(void)
{
	int nr_lines, i, j, option, nr_options, k;
	char **text, *word, *replacer, *garbage;

	scanf("%d", &nr_lines);

	word = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	replacer = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	garbage = (char *)malloc((MAX_CHARS + 1) * sizeof(char));

	text = (char **)malloc(nr_lines * sizeof(char *));
	for (i = 0; i < nr_lines; i++) {
		text[i] = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	}

	fgets(garbage, MAX_CHARS + 1, stdin);

	free(garbage);

	for (i = 0; i < nr_lines; i++) {

		fgets(text[i], MAX_CHARS + 1, stdin);
		if ((text[i][strlen(text[i]) - 1] == '\n')
		    && (strlen(text[i]) > 1)) {
			text[i][strlen(text[i]) - 1] = '\0';
		}

	}

	scanf("%d", &nr_options);

	for (j = 0; j < nr_options; j++) {
		scanf("%d", &option);

		if (option == 1) {
			printf("%d\n", number_of_occurences(text, nr_lines));
		} else if (option == 2) {
			scanf("%s", word);
			scanf("%s", replacer);

			replace_words(text, nr_lines, word, replacer);
			for (i = 0; i < nr_lines; i++) {
				if (text[i][0] == '\n') {
					printf("%s", text[i]);
				} else {
					puts(text[i]);
				}
			}
		} else if (option == 3) {
			scanf("%d", &k);
			permute(text, k, nr_lines);
			for (i = 0; i < nr_lines; i++) {
				if (text[i][0] == '\n') {
					printf("%s", text[i]);
				} else {
					puts(text[i]);
				}
			}
		}
	}

	free(word);
	free(replacer);

	for (i = 0; i < nr_lines; i++) {
		free(text[i]);
	}

	free(text);

	return 0;
}
