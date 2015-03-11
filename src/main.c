/**
 * File: main.c
 * Author: Richard Zak
 * E-Mail: richard.j.zak@gmail.com
 * Date: Tuesday 10 March 2015
 * Description: STDIN aggregator

Copyright (c) 2015, Richard Zak

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, copies of the Software, and
to permit persons to whom the Software is furnished to do so, subject to the
following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include "llist.h"

#ifndef LINE_MAX
#define LINE_MAX                2048 // For Win32
#endif

void chomp(char *s);
char *squeeze(char *str);

int main(int argc, char* argv[]) {
	char *delimiter = NULL;
	int delimiter_index = -1;

	if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-H") == 0 || strcmp(argv[1], "--help") == 0)) {
		printf("Output aggregator. Takes in many lines from standard input, and outputs only unique lines back to standard output.\n");
		printf("Version 0.2. March 2015.\nhttps://github.com/rjzak/aggregator\n");
		return EXIT_SUCCESS;
	}

	if (argc > 1 && argc < 4 && (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-C") == 0)) {
		printf("Cut off for the input to be stored. Essentially a string split.\n");
		printf("Use: %s -c <Delimiter> <Index in the resulting array to keep>\n", argv[0]);
		printf("Version 0.2. March 2015.\nhttps://github.com/rjzak/aggregator\n");
		return EXIT_SUCCESS;
	}

	if (argc == 4 && (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-C") == 0)) {
		delimiter = argv[2];
		errno = 0;
		delimiter_index = atoi(argv[3]);
		if (errno == EINVAL || errno == ERANGE) {
			fprintf(stderr, "Invalid index: %s.\n", argv[3]);
			return EXIT_FAILURE;
		}
	}

	list l;
	list_init(&l);

	//char line[LINE_MAX];
	char *line = (char*) malloc(sizeof(char) * LINE_MAX);
	while (fgets(line, LINE_MAX, stdin) != NULL) {
		if (delimiter != NULL && delimiter_index >= 0) {
			char *part = NULL;
			part = strtok(line, delimiter);
			if (delimiter_index == 0) {
				if (part == NULL) continue;
				//line = part;
				strcpy(line, part);
			} else {
				int i = 0;
				for(; i < delimiter_index; i++) {
					part = strtok(NULL, delimiter);
				}
				//line = part;
				strcpy(line, part);
			}
		}
		chomp(line);
		line = squeeze(line);
		add_string(&l, line);
	} // END WHILE

	print_list(&l, stdout);

	list_destroy(&l);
	return EXIT_SUCCESS;
}

void chomp(char *s) {
	// http://cboard.cprogramming.com/c-programming/70320-how-remove-newline-string.html#post500281
    while(*s && *s != '\n' && *s != '\r') s++;
    *s = 0;
}

char *squeeze(char *str) {
	// https://stackoverflow.com/questions/1458131/remove-extra-white-space-from-inside-a-c-string
	int r, w;
	r = w = 0;
	while (str[r]) {
		if (isspace(str[r]) || iscntrl(str[r])) {
			if (w > 0 && !isspace(str[w-1]))
				str[w++] = ' ';
		} else str[w++] = str[r];
		r++;
	}
	str[w] = 0;
	return str;
}
