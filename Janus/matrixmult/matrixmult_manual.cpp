#include <iostream>

void matrixMultiply(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][j] * B[j][k];
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
      return 1;
    }

    int n = 0;

    n += (int) atoi(argv[1]);

    // Allocate matrices A and B
    int** A = new int*[n];
    int** B = new int*[n];
    int** C = new int*[n];
    for (int i = 0; i < n; i++) {
        A[i] = new int[n];
        B[i] = new int[n];
        C[i] = new int[n];
    }

    // Initialize matrices A and B for demonstration purposes
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        A[i][j] = (i * j + i) % 4 + 1;
        B[i][j] = (i * j + j) % 4 + 1;
        C[i][j] = 0;
      }
    }

    matrixMultiply(A, B, C, n);

    // Print the result
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         std::cout << C[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // Clean up allocated memory
    for (int i = 0; i < n; i++) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
