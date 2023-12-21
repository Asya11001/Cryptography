using System;
using System.Numerics;

class ChaumBlindSignature
{
    static void Main()
    {
        // Генерируем большие простые числа p и q
        BigInteger p = BigInteger.Parse("104729");
        BigInteger q = BigInteger.Parse("1009");

        // Вычисляем n = p * q
        BigInteger n = p * q;

        // Вычисляем функцию Эйлера от n: phi(n) = (p-1)(q-1)
        BigInteger phiN = (p - 1) * (q - 1);

        // Выбираем открытый ключ e так, чтобы 1 < e < phiN и e было взаимно просто с phiN
        BigInteger e = BigInteger.Parse("65537");

        // Вычисляем закрытый ключ d, такой что (d * e) mod phiN = 1
        BigInteger d = ModInverse(e, phiN);

        // сообщение (выбирается клиентом)
        BigInteger message = BigInteger.Parse("42");

        // Клиент: создает случайное значение r и вычисляет "слепую" подпись
        BigInteger r = GenerateRandomRelativelyPrime(phiN);
        BigInteger blindedMessage = Blinding(message, r, e, n);

        // Подписываем "слепое" сообщение
        BigInteger blindedSignature = Sign(blindedMessage, d, n);

        // Клиент: снимает слепоту с подписи
        BigInteger unblindedSignature = Unblinding(blindedSignature, r, n);

        // Верификация подписи
        bool isSignatureValid = Verify(message, unblindedSignature, e, n);

        Console.WriteLine("Сообщение: " + message);
        Console.WriteLine("Исходная подпись: " + unblindedSignature);
        Console.WriteLine("Верификация: " + isSignatureValid);
    }

    static BigInteger ModInverse(BigInteger a, BigInteger m)
    {
        // Расширенный алгоритм Евклида для нахождения обратного по модулю
        BigInteger m0 = m;
        BigInteger y = 0, x = 1;

        while (a > 1)
        {
            BigInteger q = a / m;
            BigInteger t = m;

            m = a % m;
            a = t;
            t = y;

            y = x - q * y;
            x = t;
        }

        return x < 0 ? x + m0 : x;
    }

    static BigInteger GenerateRandomRelativelyPrime(BigInteger phiN)
    {
        Random rand = new Random();
        BigInteger r;

        do
        {
            r = new BigInteger(rand.Next(2, (int)phiN - 1));
        } while (BigInteger.GreatestCommonDivisor(r, phiN) != 1);

        return r;
    }

    static BigInteger Blinding(BigInteger message, BigInteger r, BigInteger e, BigInteger n)
    {
        return BigInteger.ModPow(message * BigInteger.ModPow(r, e, n), 1, n);
    }

    static BigInteger Sign(BigInteger message, BigInteger d, BigInteger n)
    {
        return BigInteger.ModPow(message, d, n);
    }

    static BigInteger Unblinding(BigInteger blindedSignature, BigInteger r, BigInteger n)
    {
        BigInteger rInverse = ModInverse(r, n);
        return BigInteger.ModPow(blindedSignature * rInverse, 1, n);
    }

    static bool Verify(BigInteger message, BigInteger signature, BigInteger e, BigInteger n)
    {
        BigInteger computedMessage = BigInteger.ModPow(signature, e, n);
        return computedMessage == message;
    }
}
