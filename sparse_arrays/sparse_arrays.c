/* -*- mode: c; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil; coding: iso-latin-1-unix; -*- vim: set ts=4 sts=4 sw=4 syntax=c et: */
/*
 * There are N strings. Each string's length is no more than 20
 * characters. There are also Q queries. For each query, you are given a
 * string, and you need to find out how many times this string occurred
 * previously.
 *   
 * Input Format
 *   
 * The first line contains N, the number of strings.
 * The next N lines each contain a string.
 * The N+2nd line contains Q, the number of queries.
 * The following QQ lines each contain a query string.
 *   
 * Constraints
 *   
 * 1 <= N <= 1000
 * 1 <= Q <= 1000
 * 1 <= length of any string <= 20
 */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define N_MAX 1000
#define Q_MAX 1000
#define STR_MAX 21

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

typedef struct str_lst {
    struct str_lst *next;
    char str[STR_MAX];
    int count;
} str_lst_t;

int count_nodes(str_lst_t *s) {
    int res = 0;
    while(s) {
        res++;
        s = s->next;
    }
    return res;
}

void print_nodes(str_lst_t *s) {
    while(s) {
        fprintf(stderr, "{%s, %d}", s->str, s->count);
        s = s->next;
    }
    fprintf(stderr, "\n");
}

str_lst_t *find_node(str_lst_t *s, char *q) {
    while(s) {
        if (strncmp(s->str, q, ARRAY_SIZE(s->str)) == 0) {
            break;
        }
        s = s->next;
    }
    return s;
}

str_lst_t *add_node(str_lst_t *s, char *str) {
    str_lst_t *new_node = malloc(sizeof(*new_node));
    strncpy(new_node->str, str, ARRAY_SIZE(new_node->str));
    new_node->count = 1;
    new_node->next = s;
    return new_node;
}

/** 
 * Add string to list. 
 * If string already exits then increment counter.
 * If string doesn't exist then add new string with counter set to 1.
 *
 * @param s list to which add string
 * @param str string to be added
 *
 * @return 
 */
str_lst_t *add_inc_str(str_lst_t *s, char *str) {
    str_lst_t *node = find_node(s, str);
    if (node) {
        node->count++;
    } else {
        s = add_node(s, str);
    }
    return s;
}

int main() {
    int N;
    int Q;
    int i;
    str_lst_t *strings;
    char **queries;

    fprintf(stderr, "Let's begin\n");
    scanf("%d\n", &N);

    fprintf(stderr, "N=%d\n", N);
    strings = malloc(sizeof(*strings));
    memset(strings, 0, sizeof(*strings));
    for (i = 0; i < N; i++) {
        char str[STR_MAX];
        scanf("%20s\n", str);
        strings->next = add_inc_str(strings->next, str);
    }

    scanf("%d\n", &Q);
    fprintf(stderr, "Q=%d\n", Q);
    queries = calloc(Q, sizeof(char*));
    if (queries == 0) {
        perror("Query array allocation failed\n");
    }
    for (i = 0; i < Q; i++) {
        queries[i] = (char*)malloc(sizeof(char) * STR_MAX);
        scanf("%20s\n", queries[i]);
    }

    for (i = 0; i < Q; i++) {
        str_lst_t *found = find_node(strings->next, queries[i]);
        if (found) {
            fprintf(stdout, "%d\n", found->count);
        } else {
            fprintf(stdout, "%d\n", 0);
        }
    }

    print_nodes(strings->next);
    /* cleanup */
    while (strings) {
        str_lst_t *next = strings->next;
        free(strings);
        strings = next;
    }
    for (i = 0; i < Q; i++) {
        free(queries[i]);
    }
    free(queries);
    return 0;
}
