// rsa_math.c: the RSA math functions

#include "rsa_math.h"

int phi_n(int p, int q){
    return (p-1)*(q-1);
}

int is_prime(int n){
    if (n < 2){
        return 0;
    }

    for (int i = 2 ; i < n; i++){
        if (n % i == 0){
            return 0;
        }
    }
    return 1;
}


int gcd(int e, int phi){ // need gcd(e, phi(n))=1, (e,n) -> public key
    while (phi!= 0) {
        int r = e % phi;
        e = phi;
        phi = r;
    }
    return e;
}

int choose_e(int phi){
    int e = 3;
    while (gcd(e, phi)!= 1) {
        e++;
    }
    return e;
}

int mod_inverse(int e, int phi) {
    int old_r = phi; int old_d = 0; //phi has 0 e's
    int r = e; int d = 1; //e has 1 e's

    while (r >1) {
        int q = old_r / r; 

        int new_d = old_d - q * d ; // ext euclidean -> d pretty much counts have many e's are in r

        old_d = d;
        d= new_d;

        int new_r = old_r % r; 
        old_r = r;
        r = new_r;
    }
    if (d < 0) d += phi;    // make d positive
    return d;
}

int mod_pow(int base, int exp, int n) { 
    if (exp == 0) {
        return 1;
    }
    int smaller = mod_pow(base, exp-1 , n);
        return base * smaller % n;
}
