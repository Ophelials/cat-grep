//  Copyright by Venusaur Doppelganger 2022
#include "s21_cat.h"

int main(int count, char **input) {
    struct flag flags = {0};
    if (count > 0) {
        if (getter(input, &flags)) {
            for (int i = 0; flags.filename[i]; i++) {
                FILE *file;
                file = fopen(flags.filename[i], "r");
                if (file) {
                    output(file, &flags);
                    fclose(file);
                } else {
                    printf("s21_cat: %s: No such file or directory\n", flags.filename[i]);
                }
            }
        }
    }
}

int getter(char **input, struct flag *flags) {
    int j = 0;
    int argument = 1;
    for (int i = 1; input[i]; i++) {
        if (input[i][0] == '-') {
            if (input[i][1] == 'e') {
                flags->e = 1;
                flags->v = 1;
            } else if (input[i][1] == 'n') {
                flags->n = 1;
            } else if (input[i][1] == 'b') {
                flags->b = 1;
            } else if (input[i][1] == 's') {
                flags->s = 1;
            } else if (input[i][1] == 't') {
                flags->t = 1;
                flags->v = 1;
            } else if (input[i][1] == 'v') {
                flags->v = 1;
            } else if (input[i][1] == 'E') {
                flags->e = 1;
            } else if (input[i][1] == 'T') {
                flags->t = 1;
            } else if (input[i][1] == '-') {
                flag_of_GNU(input, flags, i);
            } else {
                printf("s21_cat: invalid option -- '%c'\n", input[i][1]);
                argument = 0;
            }
        } else {
            flags->file = 1;
            flags->filename[j] = input[i];
            j++;
        }
    }
    if (flags->b == 1) {
        flags->n = 0;
    }
    return argument;
}

void flag_of_GNU(char **input, struct flag *flags, int number) {
    if (strcmp("--number-nonblank", input[number]) == 0) {
        flags->b = 1;
    } else if (strcmp("--number", input[number]) == 0) {
        flags->n = 1;
    } else if (strcmp("--squeeze-blank", input[number]) == 0) {
        flags->s = 1;
    }
}

void output(FILE *file, struct flag *flags) {
    char sym;
    while (fscanf(file, "%c", &sym) != EOF) {
        print_with_flags(sym, flags);
    }
}

void print_with_flags(char sym, struct flag *flags) {
    int null_str = 0;
    if (flags->s == 1 && flags->search_s == 0 && sym == '\n') {
        flags->search_s += 1;
    } else if (flags->search_s != 0 && sym == '\n') {
        flags->search_s += 1;
        null_str = 1;
    } else if (flags->search_s > 1 && sym != '\n') {
        flags->search_s = 0;
        if (flags->e == 1) {
            printf("$");
        }
        printf("\n");
        if (flags->n != 0) {
            printf("%6d\t", flags->n);
            flags->n += 1;
        }
    } else {
        flags->search_s = 0;
    }
    if (flags->n != 0 || flags->b != 0) {
        if (check_new_str == 1) {
            printf("%6d\t", flags->n);
            flags->n += 1;
            check_new_str = 0;
        }
        if (flags->n == 1) {
            printf("%6d\t", flags->n);
            flags->n += 1;
        }
        if (flags->b == 1) {
            printf("%6d\t", flags->b);
            flags->b += 1;
        }
        if (sym == '\n' && flags->n != 0 && !null_str) {
            check_new_str = 1;
        }
        if (sym == '\n' && flags->b != 0) {
            flags->search_b += 1;
        }
        if (sym != '\n' && flags->search_b != 0 && flags->search_s == 0) {
            printf("%6d\t", flags->b);
            flags->search_b = 0;
            flags->b += 1;
        }
    }
    if (flags->e == 1 && sym == '\n' && !null_str) {
        printf("$");
    }
    if (flags->v == 1) {
        if (sym < 32 && sym != 9 && sym != 10) {
            printf("^");
            sym += 64;
        }
        if (sym == 127) {
            printf("^");
            sym = '?';
        }
    }
    if (flags->t == 1 && sym == '\t') {
        printf("^");
        sym = 'I';
    }
    if (!null_str) {
        printf("%c", sym);
    }
}
