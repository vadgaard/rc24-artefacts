#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define DELTA 0x9e3779b9
#define NUM_ROUNDS 32

void encrypt(uint32_t v[2], const uint32_t k[4]) {
    uint32_t v0 = v[0], v1 = v[1], sum = 0, i;
    uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];

    for (i = 0; i < NUM_ROUNDS; i++) {
        sum += DELTA;
        v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
    }

    v[0] = v0;
    v[1] = v1;
}

void decrypt(uint32_t v[2], const uint32_t k[4]) {
    uint32_t v0 = v[0], v1 = v[1], sum = DELTA * NUM_ROUNDS, i;
    uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];

    for (i = 0; i < NUM_ROUNDS; i++) {
        v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        sum -= DELTA;
    }

    v[0] = v0;
    v[1] = v1;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }

    int n = atoi(argv[1]);

    uint32_t k[4] = {1000, 2000, 3000, 4000};
    uint32_t v[2] = {0};

    uint32_t* encrypted = malloc(n * 2 * sizeof(uint32_t));
    uint32_t* decrypted = malloc(n * 2 * sizeof(uint32_t));

    if (!encrypted || !decrypted) {
        perror("Memory allocation failed");
        free(encrypted);
        free(decrypted);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        v[0] = i * 2;
        v[1] = i * 2 + 1;

        encrypt(v, k); // Encrypt the block

        encrypted[i * 2] = v[0];
        encrypted[i * 2 + 1] = v[1];
    }

    // Decrypt
    for (int i = 0; i < n; i++) {
        v[0] = encrypted[i * 2    ];
        v[1] = encrypted[i * 2 + 1];

        decrypt(v, k);

        decrypted[i * 2    ] = v[0];
        decrypted[i * 2 + 1] = v[1];
    }

    /*
    for (int i = 0; i < n * 2; i += 2) {
        printf("Block %d - Encrypted: %u %u, Decrypted: %u %u\n", i / 2, encrypted[i], encrypted[i + 1], decrypted[i], decrypted[i + 1]);
    }
    */

    free(encrypted);
    free(decrypted);

    return 0;
}

