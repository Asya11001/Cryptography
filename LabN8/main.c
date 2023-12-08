#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функция для вычисления a^b mod p
long long power(long long a, long long b, long long p) {
    long long result = 1;
    a = a % p;
    while (b > 0) {
        if (b & 1) {
            result = (result * a) % p;
        }
        b = b >> 1;
        a = (a * a) % p;
    }
    return result;
}

// Функция для вычисления общего ключа по алгоритму Диффи-Хеллмана
long long diffieHellman(long long alpha, long long p, long long x, long long y) {
    long long A = power(alpha, x, p);
    long long B = power(alpha, y, p);
    long long keyA = power(B, x, p);
    long long keyB = power(A, y, p);

    if (keyA == keyB) {
        return keyA;
    } else {
        return -1;  // Ошибка: ключи не совпадают
    }
}

// Функция для вычисления общего ключа по алгоритму MTI
long long mti(long long alpha, long long p, long long x, long long y, long long a, long long b) {
    long long za = power(alpha, a, p);
    long long zb = power(alpha, b, p);

    long long keyA = (power(zb, x, p) * power(za, x, p)) % p;
    long long keyB = (power(za, y, p) * power(zb, y, p)) % p;

    if (keyA == keyB) {
        return keyA;
    } else {
        return -1;  // Ошибка: ключи не совпадают
    }
}

int main() {
    // Задаем параметры алгоритма
    long long p = 41;
    long long alpha = 5;
    long long x = 15;
    long long y = 7;

    // Вычисляем общий ключ по Диффи-Хеллману
    long long dhKey = diffieHellman(alpha, p, x, y);

    // Вычисляем общий ключ по MTI
    long long a = 29;
    long long b = 19;
    long long mtiKey = mti(alpha, p, x, y, a, b);

    // Выводим результаты
    printf("Diffie-Hellman Key: %lld\n", dhKey);
    printf("MTI Key: %lld\n", mtiKey);

    return 0;
}
