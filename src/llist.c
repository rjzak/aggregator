/**
 * File: llist.c
 * Author: Richard Zak
 * E-Mail: richard.j.zak@gmail.com
 * Date: Tuesday 10 March 2015
 * Description: Implementation of a linked list.

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
#include "llist.h"

void list_init(list* l) {
	l->items = 0;
	l->root = NULL;
}

void add_string(list* l, char* value) {
	if (l->root == NULL) {
		l->root = (node*) malloc(sizeof(node));
		l->root->counter = 1;
		l->root->string = (char*) malloc(sizeof(char*) * strlen(value) + 1);
		strcpy(l->root->string, value);
		l->root->next = NULL;
		l->items = 1;
		//printf("ROOT was null, now contains first item %s.\n", value);
	} else {
		if (add_string_recursive(l->root, value) > 0)
			l->items++;
	}
}

short add_string_recursive(node* n, char* value) {
	if (strcmp(n->string, value) == 0) {
		n->counter++;
		//printf("Incremented counter, %s already found.\n", value);
		//printf("\t%s == %s\n", n->string, value);
		return 0;
	} else {
		if (n->next == NULL) {
			n->next = (node*) malloc(sizeof(node));
			n->next->counter = 1;
			n->next->string = (char*) malloc(sizeof(char*) * strlen(value) + 1);
			strcpy(n->next->string, value);
			n->next->next = NULL;
			//printf("New node created for %s.\n", value);
			return 1;
		} else {
			//printf("Haven't reached same value or end of list, going to next item.\n");
			return add_string_recursive(n->next, value);
		}
	}
}

void print_list(list* l, FILE* dest, int min_count) {
	fprintf(dest, "%d elements\n", l->items);
	print_node(l->root, dest, min_count);
	fprintf(dest, "\n");
}

void print_node(node* n, FILE* dest, int min_count) {
	if (n == NULL) {
		fprintf(dest, "END\n");
		return;
	}

	if (n->counter >= min_count)
		fprintf(dest, "\t%s: %d\n", n->string, n->counter);

	if (n->next != NULL)
		print_node(n->next, dest, min_count);
}

void list_destroy(list *l) {
	if (l->root != NULL) {
		node_destroy(l->root);
		free(l->root);
		l->root = NULL;
	}
	l->items = 0;
}

void node_destroy(node* n) {
	if (n == NULL) return;
	else node_destroy(n->next);
	free(n->next);
	free(n->string);
}
