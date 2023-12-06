#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Function to calculate modular exponentiation (a^b mod m)
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp >>= 1;
        base = (base * base) % mod;
    }
    return result;
}

long long mod_inverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1) return 0;

    while (a > 1) {
        if (m == 0)
            return -1;
        q = a / m;
        t = m;

        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // Check if modular inverse exists
    if (x1 < 0) {
        x1 += m0;
    }

    if (a != 1) {
        printf("Error: Modular inverse does not exist.\n");
        return -1; // or any other value to indicate an error
    }

    return x1;
}



// Function to generate ElGamal key pair
void generate_key_pair(long long p, long long g, long long *private_key, long long *public_key) {
    *private_key = rand() % (p - 2) + 1; // Random private key in [1, p-2]
    *public_key = mod_exp(g, *private_key, p); // Calculate public key
}

// Function to sign a message using ElGamal
void sign_message(long long p, long long g, long long x, long long k, long long hash, long long *a, long long *b) {
    *a = mod_exp(g, k, p);
    if (*a == 0) {
        // Handle the case where a is zero (avoid division by zero)
        // You might need to choose a different k in this case
        printf("Error: Choose a different k.\n");
        return;
    }

    long long k_inv = mod_inverse(k, p - 1);
    if (k_inv == -1) {
        // Handle the case where the modular inverse does not exist
        printf("Error: Modular inverse does not exist.\n");
        return;
    }

    *b = (k_inv * (hash - x * (*a) + (p - 1) * (p - 1))) % (p - 1);
    if (*b < 0) {
        *b += (p - 1);
    }
}

// Function to verify the ElGamal signature
int verify_signature(long long p, long long g, long long public_key, long long a, long long b, long long hash) {
    long long left = (mod_exp(public_key, a, p) * mod_exp(a, b, p)) % p;
    long long right = mod_exp(g, hash, p);
    return left == right;
}

int main() {
    srand(time(NULL));
    // Parameters (you can change these)
    long long p = 37;
    long long g = 2;

    // Alice's key pair
    long long private_key_alice, public_key_alice;
    generate_key_pair(p, g, &private_key_alice, &public_key_alice);

    // Message to sign
    long long hash = 21;

    // Alice signs the message
    long long k = rand() % (p - 2) + 1;
    printf("k: %lld\n", k);
    long long a, b;
    sign_message(p, g, private_key_alice, k, hash, &a, &b);


    // Bob verifies the signature
    if (verify_signature(p, g, public_key_alice, a, b, hash)) {
        printf("Signature is valid.\n");
    } else {
        printf("Signature is (in)valid.\n");
    }

    return 0;
}
