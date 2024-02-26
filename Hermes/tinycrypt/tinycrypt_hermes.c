#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

void main_B();
void read_F(), read_B();
void encrypt_F(), encrypt_B();

int main(int argc, char **argv) {
  if (argc < 2) {
      return 1;
  }

  int n = atoi(argv[1]);
  {
    uint32_t v[2] = {0};
    uint32_t k[4] = {1000, 2000, 3000, 4000};
    uint32_t tmpL = 0;
    uint32_t tmpR = 0;

    uint32_t* encrypted = malloc(n * 2 * sizeof(uint32_t));
    uint32_t* decrypted = malloc(n * 2 * sizeof(uint32_t));

    if (!encrypted || !decrypted) {
        perror("Memory allocation failed");
        free(encrypted);
        free(decrypted);
        return 1;
    }

    // Encrypt
    for (int i = 0; i < n; i++) {
        v[0] = i * 2;
        v[1] = i * 2 + 1;

        encrypt_F(v, k);

        encrypted[i * 2    ] = v[0];
        encrypted[i * 2 + 1] = v[1];
    }

    // Decrypt
    for (int i = 0; i < n; i++) {
        v[0] = encrypted[i * 2    ];
        v[1] = encrypted[i * 2 + 1];

        encrypt_B(v, k);
        if (!(v[0] == i * 2    )) fprintf(stderr,"assertion failed near line 52\n");
        if (!(v[1] == i * 2 + 1)) fprintf(stderr,"assertion failed near line 53\n");

        decrypted[i * 2    ] = v[0];
        decrypted[i * 2 + 1] = v[1];
    }

    free(encrypted);
    free(decrypted);

    return 0;

    /*
    for (int i = 0; i < n * 2; i += 2) {
        printf("Block %d - Encrypted: %u %u, Decrypted: %u %u\n", i / 2, encrypted[i], encrypted[i + 1], decrypted[i], decrypted[i + 1]);
    }
    */

    /*
    if (tmpR != 0)
      fprintf(stderr,"tmpR not zero at end of block starting at line 5\n");
    if (tmpL != 0)
      fprintf(stderr,"tmpL not zero at end of block starting at line 5\n");
    { int i_; for (i_=0; i_<4; i_++)
       if  (k[i_] != 0)
         fprintf(stderr,"element of k not zero at end of block starting at line 4\n");
    }
    { int i_; for (i_=0; i_<2; i_++)
       if  (v[i_] != 0)
         fprintf(stderr,"element of v not zero at end of block starting at line 4\n");
    }
    */
  }
}

void main_B()
{
  {
    uint32_t v[2] = {0};
    uint32_t k[4] = {0};
    uint32_t tmpL = 0;
    uint32_t tmpR = 0;
    read_F(v, k);
    encrypt_F(v, k);
    tmpR += v[1];
    tmpL += v[0];
    v[1] -= tmpR;
    v[0] -= tmpL;
    if (v[0] | v[1]) {
      fprintf(stderr,"variables must be 0 before scan\n");
      exit(1);
    } else {
      scanf("%"SCNu32" %"SCNu32"\n", &v[0], &v[1]);
    }
    tmpR -= v[1];
    tmpL -= v[0];
    encrypt_B(v, k);
    read_B(v, k);
    if (tmpR != 0)
      fprintf(stderr,"tmpR not zero at end of block starting at line 5\n");
    if (tmpL != 0)
      fprintf(stderr,"tmpL not zero at end of block starting at line 5\n");
    { int i_; for (i_=0; i_<4; i_++)
       if  (k[i_] != 0)
         fprintf(stderr,"element of k not zero at end of block starting at line 4\n");
    }
    { int i_; for (i_=0; i_<2; i_++)
       if  (v[i_] != 0)
         fprintf(stderr,"element of v not zero at end of block starting at line 4\n");
    }
  }
}

void read_F(uint32_t v[], uint32_t k[])
{
  {
    if (v[0] | v[1]) {
      fprintf(stderr,"variables must be 0 before scan\n");
      exit(1);
    } else {
      scanf("%"SCNu32" %"SCNu32"\n", &v[0], &v[1]);
    }
    if (k[0] | k[1] | k[2] | k[3]) {
      fprintf(stderr,"variables must be 0 before scan\n");
      exit(1);
    } else {
      scanf("%"SCNu32" %"SCNu32" %"SCNu32" %"SCNu32"\n", &k[0], &k[1], &k[2], &k[3]);
    }
  }
}

void read_B(uint32_t v[], uint32_t k[])
{
  {
    printf("%"PRIu32" %"PRIu32" %"PRIu32" %"PRIu32"\n", k[0], k[1], k[2], k[3]);
    k[0] = k[1] = k[2] = k[3] = 0;
    printf("%"PRIu32" %"PRIu32"\n", v[0], v[1]);
    v[0] = v[1] = 0;
  }
}

void encrypt_F(uint32_t v[], uint32_t k[])
{
  {
    uint32_t v0 = 0;
    uint32_t v1 = 0;
    uint32_t sum = 0;
    uint32_t k0 = 0;
    uint32_t k1 = 0;
    uint32_t k2 = 0;
    uint32_t k3 = 0;
    const uint32_t delta = 0x9E3779B9;
    v0 ^= v[0]; v[0] ^= v0; v0 ^= v[0];
    v1 ^= v[1]; v[1] ^= v1; v1 ^= v[1];
    k0 += k[0];
    k1 += k[1];
    k2 += k[2];
    k3 += k[3];
    { int32_t i = 0;
      int32_t i_end = 32;
      while (i != i_end)
        {
          sum += delta;
          v0 += (((v1 << 4) + k0) ^ (v1 + sum)) ^ ((v1 >> 5) + k1);
          v1 += (((v0 << 4) + k2) ^ (v0 + sum)) ^ ((v0 >> 5) + k3);
          i++;
        }
    }
    k0 -= k[0];
    k1 -= k[1];
    k2 -= k[2];
    k3 -= k[3];
    sum -= delta << 5;
    v[0] ^= v0; v0 ^= v[0]; v[0] ^= v0;
    v[1] ^= v1; v1 ^= v[1]; v[1] ^= v1;
    if (k3 != 0)
      fprintf(stderr,"k3 not zero at end of block starting at line 30\n");
    if (k2 != 0)
      fprintf(stderr,"k2 not zero at end of block starting at line 30\n");
    if (k1 != 0)
      fprintf(stderr,"k1 not zero at end of block starting at line 30\n");
    if (k0 != 0)
      fprintf(stderr,"k0 not zero at end of block starting at line 30\n");
    if (sum != 0)
      fprintf(stderr,"sum not zero at end of block starting at line 30\n");
    if (v1 != 0)
      fprintf(stderr,"v1 not zero at end of block starting at line 30\n");
    if (v0 != 0)
      fprintf(stderr,"v0 not zero at end of block starting at line 30\n");
  }
}

void encrypt_B(uint32_t v[], uint32_t k[])
{
  {
    uint32_t v0 = 0;
    uint32_t v1 = 0;
    uint32_t sum = 0;
    uint32_t k0 = 0;
    uint32_t k1 = 0;
    uint32_t k2 = 0;
    uint32_t k3 = 0;
    const uint32_t delta = 0x9E3779B9;
    v[1] ^= v1; v1 ^= v[1]; v[1] ^= v1;
    v[0] ^= v0; v0 ^= v[0]; v[0] ^= v0;
    sum += delta << 5;
    k3 += k[3];
    k2 += k[2];
    k1 += k[1];
    k0 += k[0];
    { int32_t i = 32;
      int32_t i_end = 0;
      while (i != i_end)
        {
          i--;
          v1 -= (((v0 << 4) + k2) ^ (v0 + sum)) ^ ((v0 >> 5) + k3);
          v0 -= (((v1 << 4) + k0) ^ (v1 + sum)) ^ ((v1 >> 5) + k1);
          sum -= delta;
        }
    }
    k3 -= k[3];
    k2 -= k[2];
    k1 -= k[1];
    k0 -= k[0];
    v1 ^= v[1]; v[1] ^= v1; v1 ^= v[1];
    v0 ^= v[0]; v[0] ^= v0; v0 ^= v[0];
    if (k3 != 0)
      fprintf(stderr,"k3 not zero at end of block starting at line 30\n");
    if (k2 != 0)
      fprintf(stderr,"k2 not zero at end of block starting at line 30\n");
    if (k1 != 0)
      fprintf(stderr,"k1 not zero at end of block starting at line 30\n");
    if (k0 != 0)
      fprintf(stderr,"k0 not zero at end of block starting at line 30\n");
    if (sum != 0)
      fprintf(stderr,"sum not zero at end of block starting at line 30\n");
    if (v1 != 0)
      fprintf(stderr,"v1 not zero at end of block starting at line 30\n");
    if (v0 != 0)
      fprintf(stderr,"v0 not zero at end of block starting at line 30\n");
  }
}
