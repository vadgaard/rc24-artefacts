/* Translated from Janus program */
#include <stdio.h>      /* printf */
#include <math.h>
#include <stdlib.h>     /* atoi */


void crout_forward(int **A, int **LDU, int &n);
void crout_reverse(int **A, int **LDU, int &n);

void mult_forward(int &m1, int &m2);
void mult_reverse(int &m1, int &m2);

void multLD_forward(int **LDU, int **B, int &n);
void multLD_reverse(int **LDU, int **B, int &n);

void multU_forward(int **LDU, int **B, int &n);
void multU_reverse(int **LDU, int **B, int &n);

void crout_forward(int **A, int **LDU, int &n) {
    int j = 0;
    int i = 0;
    int k = 0;
    // assert(j == 0);
    while (!(j == n)) {
        i += j;
        // assert(i == j);
        while (!(i == n)) {
            LDU[i][j] += A[i][j];
            // assert(k == 0);
            while (!(k == j)) {
                if (k == j) {
                    LDU[i][j] -= LDU[i][k];
                    // assert(k == j);
                }
                else {
                    LDU[i][j] -= LDU[i][k] * LDU[k][j];
                    // assert(!(k == j));
                }
                k += 1;
                // assert(!(k == 0));
            }
            k -= j;
            i += 1;
            // assert(!(i == j));
        }
        i -= n;
        i += j + 1;
        // assert(i == j + 1);
        while (!(i == n)) {
            LDU[j][i] += A[j][i];
            // assert(k == 0);
            while (!(k == j)) {
                if (k == i) {
                    LDU[j][j] -= LDU[j][k];
                    // assert(k == j);
                }
                else {
                    LDU[j][i] -= LDU[j][k] * LDU[k][i];
                    // assert(!(k == j));
                }
                k += 1;
                // assert(!(k == 0));
            }
            k -= j;
            // printf("BEFORE DIVISION: ji: %d, jj: %d\n", LDU[j][i], LDU[j][j]);
            int t = LDU[j][i];
                t = LDU[j][j];
                t = 1;
            // printf("AFTER DIVISION: i: %d, j: %d\n", i, j);
            LDU[j][i] -= t * LDU[j][j] - t;
            // assert(t == LDU[j][i]);
            i += 1;
            // assert(!(i == j + 1));
        }
        i -= n;
        j += 1;
        // assert(!(j == 0));
    }
    j -= n;
    // assert(k == 0);
    // assert(i == 0);
    // assert(j == 0);
}
void crout_reverse(int **A, int **LDU, int &n) {
    int j = 0;
    int i = 0;
    int k = 0;
    j += n;
    // assert(j == n);
    while (!(j == 0)) {
        j -= 1;
        i += n;
        // assert(i == n);
        while (!(i == j + 1)) {
            i -= 1;
            int t = LDU[j][i];
            LDU[j][i] += t * LDU[j][j] - t;
            // assert(t == LDU[j][i] / LDU[j][j]);
            k += j;
            // assert(k == j);
            while (!(k == 0)) {
                k -= 1;
                if (k == j) {
                    LDU[j][j] += LDU[j][k];
                    // assert(k == i);
                }
                else {
                    LDU[j][i] += LDU[j][k] * LDU[k][i];
                    // assert(!(k == i));
                }
                // assert(!(k == j));
            }
            LDU[j][i] -= A[j][i];
            // assert(!(i == n));
        }
        i -= j + 1;
        i += n;
        // assert(i == n);
        while (!(i == j)) {
            i -= 1;
            k += j;
            // assert(k == j);
            while (!(k == 0)) {
                k -= 1;
                if (k == j) {
                    LDU[i][j] += LDU[i][k];
                    // assert(k == j);
                }
                else {
                    LDU[i][j] += LDU[i][k] * LDU[k][j];
                    // assert(!(k == j));
                }
                // assert(!(k == j));
            }
            LDU[i][j] -= A[i][j];
            // assert(!(i == n));
        }
        i -= j;
        // assert(!(j == n));
    }
    // assert(k == 0);
    // assert(i == 0);
    // assert(j == 0);
}

void mult_forward(int &m1, int &m2) {
    int t = m1;
    printf("B m1 %d m2 %d t %d\n", m1, m2, t);
    m1 += t * m2 - t;
    printf("A m1 %d m2 %d t %d\n", m1, m2, t);
    // assert(t == m1 / m2);
}
void mult_reverse(int &m1, int &m2) {
    int t = m1 / m2;
    printf("A m1 %d m2 %d t %d\n", m1, m2, t);
    m1 -= t * m2 - t;
    printf("B m1 %d m2 %d t %d\n", m1, m2, t);
    // assert(t == m1);
}

void multLD_forward(int **LDU, int **B, int &n) {
    int i = 0;
    int j = 0;
    int k = 0;
    i += n;
    // assert(i == n);
    i -= 1;
    // assert(j == 0);
    while (!(j == n)) {
        int t = B[i][j];
        B[i][j] += t * LDU[i][i] - t;
        // assert(t == B[i][j] / LDU[i][i]);
        k += i;
        // assert(k == i);
        while (!(k == 0)) {
            k -= 1;
            B[i][j] += LDU[k][i] * B[k][j];
            // assert(!(k == i));
        }
        j += 1;
        // assert(!(j == 0));
    }
    j -= n;
    while (!(i == 0)) {
        // assert(!(i == n));
        i -= 1;
        // assert(j == 0);
        while (!(j == n)) {
            int t = B[i][j];
            B[i][j] += t * LDU[i][i] - t;
            // assert(t == B[i][j] / LDU[i][i]);
            k += i;
            // assert(k == i);
            while (!(k == 0)) {
                k -= 1;
                B[i][j] += LDU[k][i] * B[k][j];
                // assert(!(k == i));
            }
            j += 1;
            // assert(!(j == 0));
        }
        j -= n;
    }
    // assert(k == 0);
    // assert(j == 0);
    // assert(i == 0);
}
void multLD_reverse(int **LDU, int **B, int &n) {
    int i = 0;
    int j = 0;
    int k = 0;
    // assert(i == 0);
    j += n;
    // assert(j == n);
    while (!(j == 0)) {
        j -= 1;
        // assert(k == 0);
        while (!(k == i)) {
            B[i][j] -= LDU[k][i] * B[k][j];
            k += 1;
            // assert(!(k == 0));
        }
        k -= i;
        int t = B[i][j] / LDU[i][i];
        B[i][j] -= t * LDU[i][i] - t;
        // assert(t == B[i][j]);
        // assert(!(j == n));
    }
    i += 1;
    while (!(i == n)) {
        // assert(!(i == 0));
        j += n;
        // assert(j == n);
        while (!(j == 0)) {
            j -= 1;
            // assert(k == 0);
            while (!(k == i)) {
                B[i][j] -= LDU[k][i] * B[k][j];
                k += 1;
                // assert(!(k == 0));
            }
            k -= i;
            int t = B[i][j] / LDU[i][i];
            B[i][j] -= t * LDU[i][i] - t;
            // assert(t == B[i][j]);
            // assert(!(j == n));
        }
        i += 1;
    }
    i -= n;
    // assert(k == 0);
    // assert(j == 0);
    // assert(i == 0);
}

void multU_forward(int **LDU, int **B, int &n) {
    int i = 0;
    int j = 0;
    int k = 0;
    // assert(i == 0);
    // assert(j == 0);
    while (!(j == n)) {
        k += i + 1;
        // assert(k == i + 1);
        while (!(k == n)) {
            B[i][j] += LDU[k][i] * B[k][j];
            k += 1;
            // assert(!(k == i + 1));
        }
        k -= n;
        j += 1;
        // assert(!(j == 0));
    }
    j -= n;
    i += 1;
    while (!(i == n)) {
        // assert(!(i == 0));
        // assert(j == 0);
        while (!(j == n)) {
            k += i + 1;
            // assert(k == i + 1);
            while (!(k == n)) {
                B[i][j] += LDU[k][i] * B[k][j];
                k += 1;
                // assert(!(k == i + 1));
            }
            k -= n;
            j += 1;
            // assert(!(j == 0));
        }
        j -= n;
        i += 1;
    }
    i -= n;
    // assert(k == 0);
    // assert(j == 0);
    // assert(i == 0);
}
void multU_reverse(int **LDU, int **B, int &n) {
    int i = 0;
    int j = 0;
    int k = 0;
    i += n;
    // assert(i == n);
    i -= 1;
    j += n;
    // assert(j == n);
    while (!(j == 0)) {
        j -= 1;
        k += n;
        // assert(k == n);
        while (!(k == i + 1)) {
            k -= 1;
            B[i][j] -= LDU[k][i] * B[k][j];
            // assert(!(k == n));
        }
        k -= i + 1;
        // assert(!(j == n));
    }
    while (!(i == 0)) {
        // assert(!(i == n));
        i -= 1;
        j += n;
        // assert(j == n);
        while (!(j == 0)) {
            j -= 1;
            k += n;
            // assert(k == n);
            while (!(k == i + 1)) {
                k -= 1;
                B[i][j] -= LDU[k][i] * B[k][j];
                // assert(!(k == n));
            }
            k -= i + 1;
            // assert(!(j == n));
        }
    }
    // assert(k == 0);
    // assert(j == 0);
    // assert(i == 0);
}

/*
int main(int argc, char **argv) {
    int n = 0;
    int x = 0;
    int y = 0;

    n += 3;

    int** A   = new int*[3];
    int** B   = new int*[3];
    int** LDU = new int*[3];
    for (int i = 0; i < 3; ++i) {
      A[i]   = new int[3];
      B[i]   = new int[3];
      LDU[i] = new int[3];
    }

    x += 2;
    y += 4;
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        A[i][j] = (i * j + i) % 4 + 1;
        B[j][i] = (i * j + j) % 4 + 1;
      }
    }
    crout_forward(A, LDU, n);
    multLD_forward(LDU, B, n);
    multU_forward(LDU, B, n);
    crout_reverse(A, LDU, n);

    // Print the result
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < 3; ++i) {
      delete[] A[i];
      delete[] B[i];
      delete[] LDU[i];
    }
    delete[] A;
    delete[] B;
    delete[] LDU;

    return 0;
}
*/

int main(int argc, char **argv) {
    if (argc < 2) {
      return 1;
    }

    int n = 0;

    n += (int) atoi(argv[1]);

    int** A   = new int*[n];
    int** B   = new int*[n];
    int** LDU = new int*[n];
    for (int i = 0; i < n; ++i) {
      A[i]   = new int[n];
      B[i]   = new int[n];
      LDU[i] = new int[n];
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        A[i][j] = ((i * j + i) % 4) + 1;
        B[i][j] = ((i * j + j) % 4) + 1;
        LDU[i][j] = 0;
      }
    }
    crout_forward(A, LDU, n);
    multLD_forward(LDU, B, n);
    multU_forward(LDU, B, n);
    crout_reverse(A, LDU, n);

    // // Print the result
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         std::cout << A[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    for (int i = 0; i < n; ++i) {
      delete[] A[i];
      delete[] B[i];
      delete[] LDU[i];
    }
    delete[] A;
    delete[] B;
    delete[] LDU;

    return 0;
}
