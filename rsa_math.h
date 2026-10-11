// rsa_math.h: the RSA math functions (their code is in rsa_math.c)

#ifndef RSA_MATH_H   // these 3 lines stop the file being included twice
#define RSA_MATH_H

int phi_n(int p, int q);
int is_prime(int n);
int gcd(int e, int phi);
int choose_e(int phi);
int mod_inverse(int e, int phi);
int mod_pow(int base, int exp, int n);

#endif
