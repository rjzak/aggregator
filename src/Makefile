# File: Makefile
# Author: Richard Zak
# E-Mail: richard.j.zak@gmail.com
# Date: Tuesday 10 March 2015
# Description: Makefile for STDIN aggregator
#
# Copyright (c) 2015, Richard Zak
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, copies of the Software, and
# to permit persons to whom the Software is furnished to do so, subject to the
# following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

CC=gcc
MISC=-Wall -O2

all: agg

main.o: main.c
	${CC} -c main.c ${MISC}

llist.o: llist.c llist.h
	${CC} -c llist.c ${MISC}

agg: main.o llist.o
	${CC} main.o llist.o -o agg ${MISC}

agg.exe: main.c llist.c llist.h
	i586-mingw32msvc-gcc main.c llist.c -o agg.exe ${MISC}

test: agg
	cat test.txt | ./agg
	cat test.txt | ./agg -m 4
	cat test.txt | ./agg -c ":" 1

.phony: clean
clean:
	rm -f *.o agg