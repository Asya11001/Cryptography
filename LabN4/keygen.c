#include <stdio.h>
#include <stdlib.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

// Function to generate RSA key pair and save them to files
void generateKeyPair(const char* privateKeyFile, const char* publicKeyFile) {
    RSA* rsa_keypair = RSA_generate_key(2048, 65537, NULL, NULL);

    // Save private key to file
    FILE* private_key_file = fopen(privateKeyFile, "wb");
    if (!private_key_file) {
        perror("Error opening private key file");
        exit(EXIT_FAILURE);
    }
    PEM_write_RSAPrivateKey(private_key_file, rsa_keypair, NULL, NULL, 0, NULL, NULL);
    fclose(private_key_file);

    // Save public key to file
    FILE* public_key_file = fopen(publicKeyFile, "wb");
    if (!public_key_file) {
        perror("Error opening public key file");
        exit(EXIT_FAILURE);
    }
    PEM_write_RSAPublicKey(public_key_file, rsa_keypair);
    fclose(public_key_file);

    RSA_free(rsa_keypair);
}

int main() {
    const char* private_key_file = "private_key.pem";
    const char* public_key_file = "public_key.pem";

    generateKeyPair(private_key_file, public_key_file);

    printf("Key pair generated and saved.\n");

    return 0;
}