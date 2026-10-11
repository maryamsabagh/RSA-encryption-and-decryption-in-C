/*
 * RSA encryption 
 *
 * Key generation:
 *   1. Pick two different primes p and q.
 *   2. n = p * q, and phi = (p-1)(q-1).
 *   3. Pick e with gcd(e, phi) = 1. The gcd must be 1 so that e has an
 *      inverse mod phi; otherwise no d exists and decryption is impossible.
 *   4. Find d so that (e * d) mod phi = 1, using the extended Euclidean algorithm.
 *   Public key = (e, n), shared with anyone.
 *   Private key = (d, n), kept secret.
 *
 * Encrypt: c = m^e mod n      Decrypt: m = c^d mod n
 *
 * Text is encrypted one character at a time: each character's ASCII code
 * (0 to 127) is used as m. Since m must be smaller than n (everything is
 * done mod n), we need n > 127.
 */

#include <stdio.h>
#include <string.h>
#define MAX_LEN 100

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

int read_prime(char name) {
    int n;
    printf("Enter a prime %c: ", name);
    scanf("%d", &n);

    if (is_prime(n) == 0) {
        printf("%d is not prime.\n", n);
        return 0;    // 0 means "failed", since 0 is never prime
    }
    printf("%d is prime\n", n);
    return n;
}

int mod_pow(int base, int exp, int n) { 
    if (exp == 0) {
        return 1;
    }
    int smaller = mod_pow(base, exp-1 , n);
        return base * smaller % n;
}


int main(void) {
    int p = read_prime('p');
    if (p==0){
        return 1;
   }
    int q = read_prime('q');
    if (q==0){
        return 1;
   }
    if (p == q) {
        printf("p and q must be different primes.\n");
        return 1;
   }
    int n = p * q;
    if (n<=127){
        printf("Choose larger values for p and q so n>127\n");
        return 1;
    }
    int phi = phi_n(p, q);
    int e = choose_e(phi);
    int d = mod_inverse(e, phi);

  

    printf("n = %d\n", n);
    printf("Public key  (e, n) = (%d, %d)\n", e, n);
    printf("Private key (d, n) = (%d, %d)\n", d, n);    

    while (getchar() != '\n');  // removes scanf’s \n from entering q 
    //entering message
    char text[MAX_LEN];
    printf("Enter a message: ");
    
    fgets(text, MAX_LEN, stdin);//reads characters one by one and stores their ASCII code in text, 99 of the 100 bc last one is for \0
    text[strcspn(text, "\n")] = '\0'; //makes sure the enter is not stored from fgets

    //encrypt public key (n,e) -> c= m^e mod n
    int encrpyted[MAX_LEN]; // to store encrpyted letters
    for (int i = 0; text[i] != '\0'; i++){
        encrpyted[i] = mod_pow(text[i], e, n);
        printf("%c = %d, Encrpyted letter = %d\n", text[i],text[i], encrpyted[i]); //%c prints the character and %d print the ASCII code stored in text
    }

    // decrypt with the private key (n,d) -> m = c^d mod n11
    printf("Decrypted message: ");
    for (int i = 0; i < strlen(text); i++){
        printf("%c", mod_pow(encrpyted[i], d, n));
    }
    printf("\n");

    return 0;
}

