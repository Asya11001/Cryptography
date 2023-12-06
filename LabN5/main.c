#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 5  // Adjust the size of the array as needed

// Function to compute the modular exponentiation (a^b mod m)
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        exp = exp >> 1;
        base = (base * base) % mod;
    }

    return result;
}

// Function to perform ElGamal encryption for an array of integers
void elgamal_encrypt_array(long long a[], long long b[], long long G, long long Y, long long P, const int originalMessage[], int size) {
    for (int i = 0; i < size; i++) {
        long long K = 2; // You can choose a different K value if needed
        a[i] = mod_exp(G, K, P);
        b[i] = (mod_exp(Y, K, P) * originalMessage[i]) % P;
    }
}

// Function to perform ElGamal decryption for an array of integers
void elgamal_decrypt_array(long long x, long long P, long long a[], long long b[], int decryptedMessage[], int size) {
    long long ax = mod_exp(a[0], x, P);  // Assume x is chosen such that ax * ax_inv % P == 1
    long long ax_inv = 1;

    for (int i = 0; i < size; i++) {
        ax_inv = 1;  // Reset ax_inv for each iteration
        // Calculate ax_inv using an appropriate method
        // (Here, we assume it's already chosen such that ax * ax_inv % P == 1)
        decryptedMessage[i] = (b[i] * ax_inv) % P;
    }
}

int main() {
    long long P = 37;
    long long G = 2;
    long long X = 8;

    long long Y = mod_exp(G, X, P);

    // Sender's side
    int originalMessage[ARRAY_SIZE] = {'S', 'A', 'E'};
    long long a[ARRAY_SIZE], b[ARRAY_SIZE];

    elgamal_encrypt_array(a, b, G, Y, P, originalMessage, ARRAY_SIZE);
    printf("Original Message: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", originalMessage[i]);
    }
    printf("\nEncrypted (a, b): ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("(%lld, %lld) ", a[i], b[i]);
    }
    printf("\n");

    // Receiver's side
    long long ax = mod_exp(a[0], X, P);
    int decryptedMessage[ARRAY_SIZE];
    elgamal_decrypt_array(ax, P, a, b, decryptedMessage, ARRAY_SIZE);
    printf("Decrypted Message: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", decryptedMessage[i]);
    }
    printf("\n");

    return 0;
}
