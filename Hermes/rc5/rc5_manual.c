#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define K 16            // Key size in bytes
#define W 32            // Word size in bits
#define R 12            // Number of rounds
#define C (K / 4)       // Key size in words, assuming 4 bytes per word
#define T (2 * (R + 1)) // Size of the table S

uint32_t S[T]; // Subkey array for the expanded key

uint32_t rotl(uint32_t x, uint32_t y) {
    return (x << (y & (W - 1))) | (x >> (W - (y & (W - 1))));
}

uint32_t rotr(uint32_t x, uint32_t y) {
    return (x >> (y & (W - 1))) | (x << (W - (y & (W - 1))));
}

// Key expansion
void setup(const uint8_t* k) {
    uint32_t L[C] = {0}, i, j, k_, A = 0, B = 0;
    const uint32_t P = 0xB7E15163, Q = 0x9E3779B9;

    // Load key into L
    for (i = K - 1; i != (uint32_t)-1; i--) {
        L[i / 4] = (L[i / 4] << 8) + k[i];
    }

    // Initialize S
    S[0] = P;
    for (i = 1; i < T; i++) {
        S[i] = S[i - 1] + Q;
    }

    // Mix key into S
    for (A = B = i = j = 0, k_ = 3 * ((C > T) ? C : T); k_ > 0; k_--) {
        A = S[i] = rotl(S[i] + A + B, 3);
        B = L[j] = rotl(L[j] + A + B, A + B);
        i = (i + 1) % T;
        j = (j + 1) % C;
    }
}

void encrypt(uint32_t* pt) {
    uint32_t i, A = pt[0] + S[0], B = pt[1] + S[1];

    for (i = 1; i <= R; i++) {
        A = rotl(A ^ B, B) + S[2 * i];
        B = rotl(B ^ A, A) + S[2 * i + 1];
    }

    pt[0] = A;
    pt[1] = B;
}

void decrypt(uint32_t* pt) {
    uint32_t i, A = pt[0], B = pt[1];

    for (i = R; i > 0; i--) {
        B = rotr(B - S[2 * i + 1], A) ^ A;
        A = rotr(A - S[2 * i], B) ^ B;
    }

    pt[1] = B - S[1];
    pt[0] = A - S[0];
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number of blocks>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    uint8_t key[K] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    uint32_t pt[2] = {0};

    uint32_t* encrypted = malloc(n * 2 * sizeof(uint32_t));
    uint32_t* decrypted = malloc(n * 2 * sizeof(uint32_t));

    if (!encrypted || !decrypted) {
        perror("Memory allocation failed");
        free(encrypted);
        free(decrypted);
        return 1;
    }

    setup(key);

    // Encrypt
    for (int i = 0; i < n; i++) {
        pt[0] = i * 2;
        pt[1] = i * 2 + 1;

        encrypt(pt);

        encrypted[i * 2    ] = pt[0];
        encrypted[i * 2 + 1] = pt[1];
    }

    // Decrypt
    for (int i = 0; i < n; i++) {
        pt[0] = encrypted[i * 2    ];
        pt[1] = encrypted[i * 2 + 1];

        decrypt(pt);

        decrypted[i * 2    ] = pt[0];
        decrypted[i * 2 + 1] = pt[1];
    }

    /*
    for (int i = 0; i < n; i++) {
        printf("Block %d - Encrypted: %u %u, Decrypted: %u %u\n",
               i, encrypted[i * 2], encrypted[i * 2 + 1], decrypted[i * 2], decrypted[i * 2 + 1]);
    }
    */

    free(encrypted);
    free(decrypted);

    return 0;
}
