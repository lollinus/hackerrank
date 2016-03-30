#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void print_seq(int **s, int size) {
    int i;
    int j;
    fprintf(stderr, ">>>>>>\n");
    for (i = 0; i < size; i++) {
        if (s[i] != 0) {
            fprintf(stderr, "%d: ", i);
            for (j = 0; j <= s[i][0]; j++) {
                fprintf(stderr, "%d, ", s[i][j]);
            }
            fprintf(stderr, "\n");
        }
    }
    fprintf(stderr, "<<<<<<\n");
}

typedef struct {
  int size;
  int used;
  int *seq;
} seq_t;

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    int lastans = 0;
    int N;
    int Q;
    seq_t *seq = 0;
    int i;
    int command;
    int x;
    int y;
    int max_seq = 0;
    int max_used = 0;

    fprintf(stderr, "Let's begin\n");

    scanf("%d %d\n", &N, &Q);

    fprintf(stderr, "N=%d, Q=%d\n", N, Q);
    
    seq = (seq_t*)malloc(sizeof(*seq) * N);
    if (seq == 0) {
        perror("Allocation failed");
    }
    memset(seq, 0, sizeof(*seq) * N);
   
    for (i = 0; i < Q; i++) {
        int pos;
        scanf("%d %d %d\n", &command, &x, &y);
        pos = (x ^ lastans) % N;
        if (command == 1) {
            fprintf(stderr, "%d: inserting seq: x=%d(%d) val: y=%d lastans=%d N=%d\n", i, x, pos, y, lastans, N);
            if (seq[pos].size == 0) {
		seq[pos].size = 8;
		seq[pos].used = 0;
		seq[pos].seq = malloc(sizeof(int) * seq[pos].size);
		if (seq[pos].seq == 0) {
		  perror("Sequence allocation failed\n");
		}
	    }

	    if (seq[pos].size == seq[pos].used) {
	      seq[pos].size *= 1.5; /* grow by 1.5 time to accomodate additonal values without unneccessary reallocations */
	      int *new_seq = realloc(seq[pos].seq, sizeof(int) * seq[pos].size);
	      if (new_seq == 0) {
		perror("Sequence extenting failed\n");
	      }
	      seq[pos].seq = new_seq;
	    }

	    seq[pos].seq[seq[pos].used] = y;
	    seq[pos].used ++;

	    max_seq = max_seq < seq[pos].size ? seq[pos].size : max_seq;
	    max_used = max_used < seq[pos].used ? seq[pos].used : max_used;
        } else if (command == 2) {
            int seq_pos = (y % seq[pos].used);
            lastans = seq[pos].seq[seq_pos];
            fprintf(stderr, "%d: printing seq: x=%d(%d) position: y=%d(%d) lastans=%d N=%d\n", i, x, pos, y, seq_pos, lastans, N);
	    fprintf(stdout, "%d\n", lastans);
        } else {
            fprintf(stderr, "Unknown command %d\n", command);
            exit(1);
        }
        //print_seq(seq, N);
    }
    
    /* cleanup */
    for (i = 0; i < N; i++) {
        if (seq[i].seq != 0) {
            free(seq[i].seq);
	    seq[i].size = 0;
	    seq[i].used = 0;
        }
    }
    free(seq);   
    seq = 0;

    fprintf(stderr, "max_seq=%d, max_used=%d\n", max_seq, max_used);
    
    return 0;
}
