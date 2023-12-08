#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>
#include <openssl/evp.h>

// Функция для выполнения операции xor
void xor_operation(char *m, const char *MiY, int p) {
    for (int i = 0; i < strlen(MiY); ++i) {
        m[i] = m[i] ^ MiY[i];
        m[i] = m[i] % p;
    }
}

// Функция для хэширования сообщения
void hash_message(char *m, const char *M, const char *Y, int p) {
    int len = strlen(M);
    for (int i = 0; i < len; ++i) {
        xor_operation(m, Y, p);
        m[0] = m[0] ^ M[i];
        m[0] = m[0] % p;
    }
}

// Функция для подписи сообщения
void sign_message(char *r, char *s, const char *a, const char *x, const char *k, const char *m, int q, const char *p) {
    int ak_mod_p = (atoi(a) * atoi(k)) % atoi(p);
    *r = ak_mod_p % q;

    int xm = (atoi(x) * atoi(m)) % q;
    int kxm = atoi(k) * xm;
    *s = (atoi(x) * (*r) + kxm) % q;
}

// Функция для проверки подписи
int verify_signature(const char *r, const char *s, const char *a, const char *y, const char *m, int q, int p) {
    int v = 0;
    int r_inverse = 0;

    // Вычисление v
    // Здесь должна быть реализована операция возведения в степень v = m^(q-2) mod q

    // Вычисление z1 и z2
    int z1 = (atoi(s) * v) % q;
    int z2 = ((q - atoi(r)) * v) % q;

    // Вычисление u
    int a_z1 = (atoi(a) * z1) % p;
    int y_z2 = (atoi(y) * z2) % p;
    int u = (a_z1 * y_z2) % q;

    // Проверка подписи
    return (u == atoi(r));
}

int main() {
    // Задаем параметры алгоритма
    const char *p = "31";
    const char *q = "5";
    const char *a = "16";
    const char *x = "3";
    const char *y = "4";

    // Задаем сообщение
    const char *M = "EBF";

    // Задаем случайные числа k и m
    const char *k = "3";
    const char *m = "2";

    // Подписываем сообщение
    char r, s;
    sign_message(&r, &s, a, x, k, m, atoi(q), p);

    // Выводим подпись
    printf("Digital Signature (r, s): (%d, %d)\n", r, s);

    // Проверяем подпись
    int is_valid = verify_signature(&r, &s, a, y, m, atoi(q), atoi(p));

    if (is_valid) {
        printf("Signature is valid.\n");
    } else {
        printf("Signature is invalid.\n");
    }

    return 0;
}
