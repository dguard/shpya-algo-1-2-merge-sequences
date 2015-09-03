#include <stdio.h>
#include <stdlib.h>

void check(int res, const char *msg) {
  if(!res) {
    perror(msg);
    exit(1);
  }
}

typedef struct {
  size_t len;
  int values[];
} Sequence;

Sequence *allocate(size_t n) {
  Sequence *pointer = NULL;
  if ((pointer = malloc(sizeof(Sequence) + n * sizeof(int)))) {
    pointer->len = n;
  }
  check(pointer != NULL, "can't allocate memory");
  return pointer;
}

Sequence *merge(Sequence *seq1, Sequence *seq2) {
  Sequence *new_seq = allocate(seq1->len + seq2->len);
  size_t i = 0, j = 0, k = 0;

  while (i != seq1->len || j != seq2->len) {
    if (j == seq2->len || (i < seq1->len && seq1->values[i] <= seq2->values[j])) {
      new_seq->values[k] = seq1->values[i];
      i++;
    } else {
      new_seq->values[k] = seq2->values[j];
      j++;
    }
    k++;
  }
  free(seq1);
  free(seq2);

  return new_seq;
}

int main() {
  size_t n, m;
  check(scanf("%zd%zd", &n, &m) == 2, "can't read value");

  Sequence *sequences[n];

  for(size_t i = 0; i < n; ++i) {
    Sequence *seq = allocate(m);
    for(size_t j = 0; j < m; ++j) {
      check(scanf("%d", &seq->values[j]) == 1, "can't read value");
    }
    sequences[i] = seq;
  }
  size_t k = n;

  while (k > 1) {
    size_t temp_len = k;
    k = 0;

    for(size_t i = 0; i < temp_len; i+=2) {
      if (i+1 < temp_len) {
        sequences[k] = merge(sequences[i], sequences[i+1]);
      } else {
        sequences[k] = sequences[i];
      }
      k++;
    }
  }

  for(size_t j = 0; j < n*m; j++) {
    printf("%d ", sequences[0]->values[j]);
  }
  printf("\n");
  free(sequences[0]);

  return 0;
}
