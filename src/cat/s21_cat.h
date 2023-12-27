// Copyright by Venusaur 2022
#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flag {
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
    int file;
    char *filename[2048];
    int search_b;
    int search_s;
};


int check_new_str = 0;

int getter(char **input, struct flag *flags);
void flag_of_GNU(char **input, struct flag *flags, int number);
void output(FILE *file, struct flag *flags);
void print_with_flags(char sym, struct flag *flags);

#endif  // SRC_CAT_S21_CAT_H_
