#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHARS 12000
#define DELIMITATORS " ,?!\'\""

int wildcard_string_matching(char *pattern, char *word)
{
	char *word_after_asterisk_match = NULL, *pattern_after_asterisk = NULL;

	while ((word[0] != '\0') && (pattern[0] != '*')) {
		if ((pattern[0] != word[0]) && (pattern[0] != '.')) {
			return 0;
		}
		pattern = pattern + 1;
		word = word + 1;
	}

	while (word[0] != '\0') {
		if (pattern[0] == '*') {
			pattern = pattern + 1;
			if (!(pattern[0])) {
				return 1;
			}
			pattern_after_asterisk = pattern;
			word_after_asterisk_match = word + 1;
		} else if ((pattern[0] == word[0]) || (pattern[0] == '.')) {
			pattern++;
			word++;
		} else {
			pattern = pattern_after_asterisk;
			word = word_after_asterisk_match;
			word_after_asterisk_match =
			    word_after_asterisk_match + 1;
		}
	}

	while (pattern[0] == '*') {
		pattern = pattern + 1;
	}

	return !(pattern[0]);
}

int main()
{
	int nr_lines, i, j, nr_options, matches;
	char **text, *garbage, *pattern, *line, *token;

	scanf("%d", &nr_lines);

	garbage = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	pattern = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	line = (char *)malloc((MAX_CHARS + 1) * sizeof(char));
	token = (char *)malloc((MAX_CHARS + 1) * sizeof(char));

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
		scanf("%s", pattern);
		matches = 0;
		for (i = 0; i < nr_lines; i++) {
			strcpy(line, text[i]);
			token = strtok(line, DELIMITATORS);

			while (token != NULL) {
				if (wildcard_string_matching(pattern, token) ==
				    1) {
					matches = matches + 1;
				}

				token = strtok(NULL, DELIMITATORS);
			}
		}

		printf("%d\n", matches);
	}

	free(pattern);
	free(line);
	free(token);

	for (i = 0; i < nr_lines; i++) {
		free(text[i]);
	}

	free(text);

	return 0;
}
