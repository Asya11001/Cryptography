#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Функция для вычисления наибольшего общего делителя
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int getInverseNumber(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}
/*
// Функция для шифрования сообщения
void encrypt(char* message, int* encrypted, int length, int publicKey, int modulus) {
    for (int i = 0; i < length; i++) {
        encrypted[i] = fmod(pow(message[i], publicKey), modulus);
    }
}
*/
void encrypt(char* message, int* encrypted, int length, int publicKey, int modulus) {
    for (int i = 0; i < length; i++) {
        double result = 1.0;
        for (int j = 0; j < publicKey; j++) {
            result = fmod(result * message[i], modulus);
        }
        encrypted[i] = (int)result;
    }
}

void decrypt(int* encrypted, char* decrypted, int length, int privateKey, int modulus) {
    for (int i = 0; i < length; i++) {
        double result = 1.0;
        for (int j = 0; j < privateKey; j++) {
            result = fmod(result * encrypted[i], modulus);
        }
        decrypted[i] = (char)result;
    }
}

int getValueFromEulerFunction(int P, int Q){
    return (P - 1) * (Q - 1);
}

int main() {

    int P = 17;
    int Q = 19;
    int N = P * Q;
    int valueFromEulerFunction = getValueFromEulerFunction(P, Q);
    int publicKey = 5;  // открытый ключ
    int privateKey = getInverseNumber(publicKey, valueFromEulerFunction);  // закрытый ключ

    char message[] = "Some important information here";
    int messageLength = strlen(message);

    // Выделяем память под массивы для шифрованного и расшифрованного сообщения
    int* encryptedMessage = (int*)malloc(messageLength * sizeof(int));
    char* decryptedMessage = (char*)malloc(messageLength * sizeof(char));

    // Шифрование
    encrypt(message, encryptedMessage, messageLength, publicKey, N);

    // Расшифрование
    decrypt(encryptedMessage, decryptedMessage, messageLength, privateKey, N);

    // Вывод результатов
    printf("Original Message: %s\n", message);
    printf("Encrypted Message: ");
    for (int i = 0; i < messageLength; i++) {
        printf("%d ", encryptedMessage[i]);
    }
    printf("\nDecrypted Message: %s\n", decryptedMessage);

    // Освобождаем выделенную память
    free(encryptedMessage);
    free(decryptedMessage);

    return 0;
}