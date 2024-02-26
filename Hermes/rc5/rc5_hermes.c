#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

void main_B();
void read_F(), read_B();
void setup_F(), setup_B();
void encrypt_F(), encrypt_B();

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }

    int n = atoi(argv[1]);

    uint8_t k[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    uint32_t S[26] = {0};
    uint32_t L[6] = {0};
    uint32_t pt[2] = {0};

    uint32_t* encrypted = malloc(n * 2 * sizeof(uint32_t));
    uint32_t* decrypted = malloc(n * 2 * sizeof(uint32_t));

    if (!encrypted || !decrypted) {
        perror("Memory allocation failed");
        free(encrypted);
        free(decrypted);
        return 1;
    }

    setup_F(S, k, L);

    // Encrypt
    for (int i = 0; i < n; i++) {
        pt[0] = i * 2;
        pt[1] = i * 2 + 1;

        encrypt_F(S, pt);

        encrypted[i * 2    ] = pt[0];
        encrypted[i * 2 + 1] = pt[1];
    }

    // Decrypt
    for (int i = 0; i < n; i++) {
        pt[0] = encrypted[i * 2    ];
        pt[1] = encrypted[i * 2 + 1];

        encrypt_B(S, pt);
        if (!(pt[0] == i * 2    )) fprintf(stderr,"assertion failed near line 52\n");
        if (!(pt[1] == i * 2 + 1)) fprintf(stderr,"assertion failed near line 53\n");

        decrypted[i * 2    ] = pt[0];
        decrypted[i * 2 + 1] = pt[1];
    }

    /*
    for (int i = 0; i < n * 2; i += 2) {
        printf("Block %d - Encrypted: %u %u, Decrypted: %u %u\n", i / 2, encrypted[i], encrypted[i + 1], decrypted[i], decrypted[i + 1]);
    }
    */

    free(encrypted);
    free(decrypted);

    setup_B(S, k, L);
    /*
    read_B(pt, k);
    if (tmpR != 0)
      fprintf(stderr,"tmpR not zero at end of block starting at line 5\n");
    if (tmpL != 0)
      fprintf(stderr,"tmpL not zero at end of block starting at line 5\n");
    { int i_; for (i_=0; i_<2; i_++)
       if  (pt[i_] != 0)
         fprintf(stderr,"element of pt not zero at end of block starting at line 4\n");
    }
    { int i_; for (i_=0; i_<6; i_++)
       if  (L[i_] != 0)
         fprintf(stderr,"element of L not zero at end of block starting at line 4\n");
    }
    { int i_; for (i_=0; i_<26; i_++)
       if  (S[i_] != 0)
         fprintf(stderr,"element of S not zero at end of block starting at line 4\n");
    }
    { int i_; for (i_=0; i_<16; i_++)
       if  (k[i_] != 0)
         fprintf(stderr,"element of k not zero at end of block starting at line 3\n");
    }
    */
}

void main_B()
{
  {
    uint8_t k[16] = {0};
    uint32_t S[26] = {0};
    uint32_t L[6] = {0};
    uint32_t pt[2] = {0};
    uint32_t tmpL = 0;
    uint32_t tmpR = 0;
    read_F(pt, k);
    setup_F(S, k, L);
    if (!(pt[1] == 2)) fprintf(stderr,"assertion failed near line 22\n");
    if (!(pt[0] == 1)) fprintf(stderr,"assertion failed near line 21\n");
    encrypt_F(S, pt);
    tmpR += pt[1];
    tmpL += pt[0];
    pt[1] -= tmpR;
    pt[0] -= tmpL;
    if (pt[0] | pt[1]) {
      fprintf(stderr,"variables must be 0 before scan\n");
      exit(1);
    } else {
      scanf("%"SCNu32" %"SCNu32"\n", &pt[0], &pt[1]);
    }
    tmpR -= pt[1];
    tmpL -= pt[0];
    encrypt_B(S, pt);
    setup_B(S, k, L);
    read_B(pt, k);
    if (tmpR != 0)
      fprintf(stderr,"tmpR not zero at end of block starting at line 5\n");
    if (tmpL != 0)
      fprintf(stderr,"tmpL not zero at end of block starting at line 5\n");
    { int i_; for (i_=0; i_<2; i_++)
       if  (pt[i_] != 0)
         fprintf(stderr,"element of pt not zero at end of block starting at line 4\n");
    }
    { int i_; for (i_=0; i_<6; i_++)
       if  (L[i_] != 0)
         fprintf(stderr,"element of L not zero at end of block starting at line 4\n");
    }
    { int i_; for (i_=0; i_<26; i_++)
       if  (S[i_] != 0)
         fprintf(stderr,"element of S not zero at end of block starting at line 4\n");
    }
    { int i_; for (i_=0; i_<16; i_++)
       if  (k[i_] != 0)
         fprintf(stderr,"element of k not zero at end of block starting at line 3\n");
    }
  }
}

void read_F(uint32_t pt[], uint8_t k[])
{
  {
    if (pt[0] | pt[1]) {
      fprintf(stderr,"variables must be 0 before scan\n");
      exit(1);
    } else {
      scanf("%"SCNu32" %"SCNu32"\n", &pt[0], &pt[1]);
    }
    if (k[0] | k[1] | k[2] | k[3]) {
      fprintf(stderr,"variables must be 0 before scan\n");
      exit(1);
    } else {
      scanf("%"SCNu8" %"SCNu8" %"SCNu8" %"SCNu8"\n", &k[0], &k[1], &k[2], &k[3]);
    }
    if (k[4] | k[5] | k[6] | k[7]) {
      fprintf(stderr,"variables must be 0 before scan\n");
      exit(1);
    } else {
      scanf("%"SCNu8" %"SCNu8" %"SCNu8" %"SCNu8"\n", &k[4], &k[5], &k[6], &k[7]);
    }
    if (k[8] | k[9] | k[10] | k[11]) {
      fprintf(stderr,"variables must be 0 before scan\n");
      exit(1);
    } else {
      scanf("%"SCNu8" %"SCNu8" %"SCNu8" %"SCNu8"\n", &k[8], &k[9], &k[10], &k[11]);
    }
    if (k[12] | k[13] | k[14] | k[15]) {
      fprintf(stderr,"variables must be 0 before scan\n");
      exit(1);
    } else {
      scanf("%"SCNu8" %"SCNu8" %"SCNu8" %"SCNu8"\n", &k[12], &k[13], &k[14], &k[15]);
    }
  }
}

void read_B(uint32_t pt[], uint8_t k[])
{
  {
    printf("%"PRIu8" %"PRIu8" %"PRIu8" %"PRIu8"\n", k[12], k[13], k[14], k[15]);
    k[12] = k[13] = k[14] = k[15] = 0;
    printf("%"PRIu8" %"PRIu8" %"PRIu8" %"PRIu8"\n", k[8], k[9], k[10], k[11]);
    k[8] = k[9] = k[10] = k[11] = 0;
    printf("%"PRIu8" %"PRIu8" %"PRIu8" %"PRIu8"\n", k[4], k[5], k[6], k[7]);
    k[4] = k[5] = k[6] = k[7] = 0;
    printf("%"PRIu8" %"PRIu8" %"PRIu8" %"PRIu8"\n", k[0], k[1], k[2], k[3]);
    k[0] = k[1] = k[2] = k[3] = 0;
    printf("%"PRIu32" %"PRIu32"\n", pt[0], pt[1]);
    pt[0] = pt[1] = 0;
  }
}

void setup_F(uint32_t S[], uint8_t k[], uint32_t L[])
{
  {
    const uint32_t P = 0xB7E15163;
    const uint32_t Q = 0x9E3779B9;
    const uint32_t w = 32;
    const uint32_t u = 4;
    const int32_t t = 26;
    const uint32_t b = 16;
    const uint32_t c = 4;
    int8_t i = 0;
    int8_t j = 0;
    uint32_t X = 0;
    uint32_t Y = 0;
    { int32_t i = b;
      int32_t i_end = 0;
      while (i != i_end)
        {
          i--;
          { int tmp_ = 8 & 0x1f;
            L[i / u] = ((L[i / u] << tmp_) | (L[i / u] >> (32 - tmp_))) & 0xffffffff;
            tmp_ = 0; }
          L[i / u] += k[i];
        }
    }
    { int32_t i = 0;
      int32_t i_end = t;
      while (i != i_end)
        {
          S[i] += P + (i * Q);
          i++;
        }
    }
    { int32_t l = 0;
      int32_t l_end = 3 * t;
      while (l != l_end)
        {
          S[i] += X + Y;
          { int tmp_ = 3 & 0x1f;
            S[i] = ((S[i] << tmp_) | (S[i] >> (32 - tmp_))) & 0xffffffff;
            tmp_ = 0; }
          X -= -(l != 0)&S[(((i - 1) % t) + t) % t];
          X += S[i];
          L[j] += X + Y;
          { int tmp_ = (X + Y) & 0x1f;
            L[j] = ((L[j] << tmp_) | (L[j] >> (32 - tmp_))) & 0xffffffff;
            tmp_ = 0; }
          Y -= -(l != 0)&L[(((j - 1) % c) + c) % c];
          Y += L[j];
          i++;
          l++;
          j++;
          i -= -((l % t) == 0)&t;
          j -= -((l % c) == 0)&c;
        }
    }
    X -= S[t - 1];
    Y -= -(j != 0)&L[j - 1];
    Y -= -(j == 0)&L[c - 1];
    j -= (3 * t) - (((3 * t) / c) * c);
    if (Y != 0)
      fprintf(stderr,"Y not zero at end of block starting at line 52\n");
    if (X != 0)
      fprintf(stderr,"X not zero at end of block starting at line 52\n");
    if (j != 0)
      fprintf(stderr,"j not zero at end of block starting at line 51\n");
    if (i != 0)
      fprintf(stderr,"i not zero at end of block starting at line 51\n");
  }
}

void setup_B(uint32_t S[], uint8_t k[], uint32_t L[])
{
  {
    const uint32_t P = 0xB7E15163;
    const uint32_t Q = 0x9E3779B9;
    const uint32_t w = 32;
    const uint32_t u = 4;
    const int32_t t = 26;
    const uint32_t b = 16;
    const uint32_t c = 4;
    int8_t i = 0;
    int8_t j = 0;
    uint32_t X = 0;
    uint32_t Y = 0;
    j += (3 * t) - (((3 * t) / c) * c);
    Y += -(j == 0)&L[c - 1];
    Y += -(j != 0)&L[j - 1];
    X += S[t - 1];
    { int32_t l = 3 * t;
      int32_t l_end = 0;
      while (l != l_end)
        {
          j += -((l % c) == 0)&c;
          i += -((l % t) == 0)&t;
          j--;
          l--;
          i--;
          Y -= L[j];
          Y += -(l != 0)&L[(((j - 1) % c) + c) % c];
          { int tmp_ = (X + Y) & 0x1f;
            L[j] = ((L[j] >> tmp_) | (L[j] << (32 - tmp_))) & 0xffffffff;
            tmp_ = 0; }
          L[j] -= X + Y;
          X -= S[i];
          X += -(l != 0)&S[(((i - 1) % t) + t) % t];
          { int tmp_ = 3 & 0x1f;
            S[i] = ((S[i] >> tmp_) | (S[i] << (32 - tmp_))) & 0xffffffff;
            tmp_ = 0; }
          S[i] -= X + Y;
        }
    }
    { int32_t i = t;
      int32_t i_end = 0;
      while (i != i_end)
        {
          i--;
          S[i] -= P + (i * Q);
        }
    }
    { int32_t i = 0;
      int32_t i_end = b;
      while (i != i_end)
        {
          L[i / u] -= k[i];
          { int tmp_ = 8 & 0x1f;
            L[i / u] = ((L[i / u] >> tmp_) | (L[i / u] << (32 - tmp_))) & 0xffffffff;
            tmp_ = 0; }
          i++;
        }
    }
    if (Y != 0)
      fprintf(stderr,"Y not zero at end of block starting at line 52\n");
    if (X != 0)
      fprintf(stderr,"X not zero at end of block starting at line 52\n");
    if (j != 0)
      fprintf(stderr,"j not zero at end of block starting at line 51\n");
    if (i != 0)
      fprintf(stderr,"i not zero at end of block starting at line 51\n");
  }
}

void encrypt_F(uint32_t S[], uint32_t pt[])
{
  {
    const uint32_t r = 12;
    uint32_t A = 0;
    uint32_t B = 0;
    A ^= pt[0]; pt[0] ^= A; A ^= pt[0];
    B ^= pt[1]; pt[1] ^= B; B ^= pt[1];
    A += S[0];
    B += S[1];
    { int32_t i = 1;
      int32_t i_end = r + 1;
      while (i != i_end)
        {
          A ^= B;
          { int tmp_ = B & 0x1f;
            A = ((A << tmp_) | (A >> (32 - tmp_))) & 0xffffffff;
            tmp_ = 0; }
          A += S[2 * i];
          B ^= A;
          { int tmp_ = A & 0x1f;
            B = ((B << tmp_) | (B >> (32 - tmp_))) & 0xffffffff;
            tmp_ = 0; }
          B += S[(2 * i) + 1];
          i++;
        }
    }
    A ^= pt[0]; pt[0] ^= A; A ^= pt[0];
    B ^= pt[1]; pt[1] ^= B; B ^= pt[1];
    if (B != 0)
      fprintf(stderr,"B not zero at end of block starting at line 95\n");
    if (A != 0)
      fprintf(stderr,"A not zero at end of block starting at line 95\n");
  }
}

void encrypt_B(uint32_t S[], uint32_t pt[])
{
  {
    const uint32_t r = 12;
    uint32_t A = 0;
    uint32_t B = 0;
    B ^= pt[1]; pt[1] ^= B; B ^= pt[1];
    A ^= pt[0]; pt[0] ^= A; A ^= pt[0];
    { int32_t i = r + 1;
      int32_t i_end = 1;
      while (i != i_end)
        {
          i--;
          B -= S[(2 * i) + 1];
          { int tmp_ = A & 0x1f;
            B = ((B >> tmp_) | (B << (32 - tmp_))) & 0xffffffff;
            tmp_ = 0; }
          B ^= A;
          A -= S[2 * i];
          { int tmp_ = B & 0x1f;
            A = ((A >> tmp_) | (A << (32 - tmp_))) & 0xffffffff;
            tmp_ = 0; }
          A ^= B;
        }
    }
    B -= S[1];
    A -= S[0];
    B ^= pt[1]; pt[1] ^= B; B ^= pt[1];
    A ^= pt[0]; pt[0] ^= A; A ^= pt[0];
    if (B != 0)
      fprintf(stderr,"B not zero at end of block starting at line 95\n");
    if (A != 0)
      fprintf(stderr,"A not zero at end of block starting at line 95\n");
  }
}

/*
int main(int ac, char **av)
{
  if (ac>1 && strcmp(av[1],"-r")==0) main_B();
  else main_F();
  exit(0);
}
*/
