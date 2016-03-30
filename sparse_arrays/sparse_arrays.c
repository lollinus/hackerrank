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

int main() {
    int N;
    int Q;
    int i;
    char **strings;
    char **queries;
    int count;
    int last_found;

    fprintf(stderr, "Let's begin\n");
    scanf("%d\n", &N);

    fprintf(stderr, "N=%d\n", N);
    strings = malloc(sizeof(*strings) * N);
    /* ZERO init strings */
    memset(strings, 0, sizeof(*strings) * N);
    for (i = 0; i < N; i++) {
        strings[i] = malloc(sizeof(*(strings[i])) * 21);
        scanf("%20s\n", strings[i]);
    }

    scanf("%d\n", &Q);
    fprintf(stderr, "Q=%d\n", Q);
    queries = malloc(sizeof(*queries) * Q);
    memset(queries, 0, sizeof(*queries) * Q);
    
    for (i = 0; i < Q; i++) {
        queries[i] = malloc(sizeof(*(strings[i])) * 21);
        scanf("%20s\n", queries[i]);
    }

    last_found = 0;
    for (i = 0; i < Q; i++) {
        count = 0;
        int j;
        for (j = last_found; j < N; j++) {
            if (strcmp(strings[j], queries[i]) == 0) {
                count++;
                last_found = j;
            }
        }
        fprintf(stdout, "%d\n", count);
    }

    for (i = 0; i < N; i++) {
        free(strings[i]);
    }
    free(strings);
    for (i = 0; i < Q; i++) {
        free(queries[i]);
    }
    free(queries);
    return 0;
}
