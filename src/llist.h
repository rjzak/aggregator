/**
 * File: llist.h
 * Author: Richard Zak
 * E-Mail: richard.j.zak@gmail.com
 * Date: Tuesday 10 March 2015
 * Description: Function prototypes for a linked list.

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

#ifndef _LLIST_H__
#define _LLIST_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
  int counter;
  char* string;
  struct node_t* next;
} node;

typedef struct list_t {
	int items;
	node* root;
} list;

void list_init(list* l);
void add_string(list* l, char* value);
short add_string_recursive(node* n, char* value);

void print_list(list* l, FILE* dest);
void print_node(node* n, FILE* dest);

void list_destroy(list *l);
void node_destroy(node* n);

#endif
