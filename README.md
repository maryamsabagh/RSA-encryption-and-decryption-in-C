# RSA Encryption and Decryption in C

A from-scratch implementation of RSA algorithm in C. It generates a key pair from two primes, then encrypts and decrypts a text message one character at a time.

## How it works

1. Pick two different primes $p$ and $q$.
2. Compute $n = p \times q$ and $\varphi = (p - 1)(q - 1)$.
3. Choose $e$ such that $\gcd(e, \varphi) = 1$.
4. Find $d$ such that $e \cdot d \equiv 1 \pmod{\varphi}$, using the extended Euclidean algorithm.

- Public key: $(e, n)$
- Private key: $(d, n)$

$$c = m^e \bmod n \qquad\qquad m = c^d \bmod n$$

Each character's ASCII code is used as $m$. Since $m$ must be smaller than $n$, the program requires $n > 127$.

## Files

| File | Contents |
|------|----------|
| `RSA.c` | `main` and user input/output |
| `rsa_math.c` | RSA math: primality test, gcd, choosing e, modular inverse, modular exponentiation |
| `rsa_math.h` | Function prototypes for `rsa_math.c` |

## Build and run

```
gcc RSA.c rsa_math.c -o rsa
./rsa
```

## Example

```
Enter a prime p: 61
Enter a prime q: 53
n = 3233
Public key  (e, n) = (7, 3233)
Private key (d, n) = (1783, 3233)
Enter a message: Hi
H = 72, Encrypted letter = 1087
i = 105, Encrypted letter = 3020
Decrypted message: Hi
```

## Limitations

This is a learning project, not secure cryptography:
- Uses small primes and `int`, so $n$ must stay below about 46,000 to avoid overflow.
- Encrypts letter by letter, so the same letter always produces the same number.
- No padding (real RSA uses schemes like OAEP).
