#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Function to calculate (base ^ exponent) % modulo
long long power(long long base, long long exponent, long long modulo) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulo;
        base = (base * base) % modulo;
        exponent /= 2;
    }
    return result;
}

// Function to perform the extended Euclidean algorithm
long long extendedGCD(long long a, long long b, long long* x, long long* y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = extendedGCD(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

// Function to find modular inverse of a (mod m) using extended Euclidean algorithm
long long modInverse(long long a, long long m) {
    long long x, y;
    long long gcd = extendedGCD(a, m, &x, &y);
    if (gcd != 1) {
        printf("Inverse doesn't exist\n");
        exit(EXIT_FAILURE);
    } else {
        return (x % m + m) % m;
    }
}

// Function to encrypt a message using ElGamal
void encrypt(long long message, long long p, long long g, long long y, long long* a, long long* b) {
    // Generate random k
    srand(time(NULL));
    long long k = rand() % (p - 2) + 1;

    // Calculate a and b
    *a = power(g, k, p);
    long long yk = power(y, k, p);
    *b = (yk * message) % p;
}

// Function to decrypt a message using ElGamal
long long decrypt(long long a, long long b, long long x, long long p) {
    // Calculate ax
    long long ax = power(a, x, p);

    // Calculate modular inverse of ax
    long long axInverse = modInverse(ax, p);

    // Decrypt the message
    long long decryptedMessage = (axInverse * b) % p;
    return decryptedMessage;
}

int main() {
    // Parameters
    long long p = 37;
    long long g = 2;
    long long x = 8;

    // Calculate public key y
    long long y = power(g, x, p);

    // Original message
    long long message = 21;

    // Encrypt the message
    long long a, b;
    encrypt(message, p, g, y, &a, &b);

    // Decrypt the message
    long long decryptedMessage = decrypt(a, b, x, p);

    // Display results
    printf("Original Message: %lld\n", message);
    printf("Encrypted (a, b): (%lld, %lld)\n", a, b);
    printf("Decrypted Message: %lld\n", decryptedMessage);

    return 0;
}
