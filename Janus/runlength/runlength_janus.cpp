/* Translated from Janus program */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* atoi */
#include <time.h>       /* time */
#include <assert.h>


void encode_forward(unsigned int *text, unsigned int *arc);
void encode_reverse(unsigned int *text, unsigned int *arc);

void encode_forward(unsigned int *text, unsigned int *arc) {
    unsigned int i = 0;
    unsigned int j = 0;
    assert(i == 0 && j == 0);
    while (!(text[i] == 0)) {
        arc[j] += text[i];
        text[i] -= arc[j];
        assert(arc[j + 1] == 0);
        arc[j + 1] += 1;
        i += 1;
        while (!(arc[j] != text[i])) {
            text[i] -= arc[j];
            assert(!(arc[j + 1] == 0));
            arc[j + 1] += 1;
            i += 1;
        }
        j += 2;
        assert(!(i == 0 && j == 0));
    }
    assert(arc[j] == 0);
    j -= 2;
    i -= arc[j + 1];
    while (!(i == 0)) {
        assert(!(arc[j] == 0));
        j -= 2;
        i -= arc[j + 1];
    }
    assert(j == 0);
    assert(i == 0);
}
void encode_reverse(unsigned int *text, unsigned int *arc) {
    unsigned int i = 0;
    unsigned int j = 0;
    assert(i == 0);
    i += arc[j + 1];
    j += 2;
    while (!(arc[j] == 0)) {
        assert(!(i == 0));
        i += arc[j + 1];
        j += 2;
    }
    assert(text[i] == 0);
    while (!(i == 0 && j == 0)) {
        j -= 2;
        assert(arc[j] != text[i]);
        i -= 1;
        arc[j + 1] -= 1;
        while (!(arc[j + 1] == 0)) {
            text[i] += arc[j];
            assert(!(arc[j] != text[i]));
            i -= 1;
            arc[j + 1] -= 1;
        }
        text[i] += arc[j];
        arc[j] -= text[i];
        assert(!(text[i] == 0));
    }
    assert(j == 0);
    assert(i == 0);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("An integer should be provided.\n");
        return 1;
    }

    unsigned int n, *text, *arc;

    n = (unsigned int) atoi(argv[1]);

    text = (unsigned int*) calloc(  n, sizeof(unsigned int));
    arc  = (unsigned int*) calloc(2*n, sizeof(unsigned int));

    srand(time(NULL));

    // initialize text
    for (int i = 0; i < n-1; i++) {
        text[i] = rand() % 5 + 1;
    }

    encode_forward(text, arc);
    return 1;
}
