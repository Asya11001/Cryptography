#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

// Function to compute the SHA-256 hash of a string
void computeHash(const char *input, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(hash, &sha256);
}

// Function to sign a message using RSA
void signMessage(const char *message, const char *privateKeyFile, unsigned char signature[]) {
    // Load private key
    FILE *privateKeyFilePtr = fopen(privateKeyFile, "rb");
    if (!privateKeyFilePtr) {
        perror("Error opening private key file");
        exit(EXIT_FAILURE);
    }

    RSA *privateKey = PEM_read_RSAPrivateKey(privateKeyFilePtr, NULL, NULL, NULL);
    fclose(privateKeyFilePtr);
    if (!privateKey) {
        perror("Error reading private key");
        exit(EXIT_FAILURE);
    }

    // Compute hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    computeHash(message, hash);

    unsigned int signatureLength = 256;
    int result = RSA_sign(NID_sha256, hash, SHA256_DIGEST_LENGTH, signature, &signatureLength, privateKey);
    if (result != 1) {
        perror("Error signing message");
        exit(EXIT_FAILURE);
    }

    // Send message, hash, and signature to the recipient
    // ...

    // Clean up
    RSA_free(privateKey);
}

int verifySignature(const char *message, const unsigned char *signature, const char *publicKeyFile) {
    // Load public key
    FILE *publicKeyFilePtr = fopen(publicKeyFile, "rb");
    if (!publicKeyFilePtr) {
        perror("Error opening public key file");
        exit(EXIT_FAILURE);
    }

    RSA *publicKey = PEM_read_RSAPublicKey(publicKeyFilePtr, NULL, NULL, NULL);
    fclose(publicKeyFilePtr);
    if (!publicKey) {
        ERR_print_errors_fp(stderr);  // Print OpenSSL error information
        perror("Error reading public key");
        exit(EXIT_FAILURE);
    }

    // Compute hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    computeHash(message, hash);

    // Verify the signature
    int result = RSA_verify(NID_sha256, hash, SHA256_DIGEST_LENGTH, signature, 256, publicKey);

    // Clean up
    RSA_free(publicKey);

    return result;
}


int main() {
    const char *message = "Your message here";
    const char *privateKeyFile = "private_key.pem";
    const char *publicKeyFile = "public_key.pem";

    // Sender signs the message
    unsigned char signature[256]; // Adjust size based on the key size

    signMessage(message, privateKeyFile, signature);

    // Receiver verifies the signature
    int isSignatureValid = verifySignature(message, signature, publicKeyFile);

    if (isSignatureValid == 1) {
        printf("Signature is valid.\n");
    } else {
        printf("Signature is not valid.\n");
    }

    return 0;
}