using System;
using Org.BouncyCastle.Crypto;
using Org.BouncyCastle.Crypto.Generators;
using Org.BouncyCastle.Crypto.Parameters;
using Org.BouncyCastle.Security;

class Program
{
    static void Main()
    {
        // Generate an RSA key pair
        var keyPair = GenerateRSAKeyPair();

        // Message to be encrypted
        var message = "Hello, RSA Encryption!";

        // Encrypt the message using the public key
        var encryptedData = EncryptMessage(message, keyPair.Public);

        // Decrypt the message using the private key
        var decryptedMessage = DecryptMessage(encryptedData, keyPair.Private);

        Console.WriteLine("Original Message: " + message);
        Console.WriteLine("Encrypted Message: " + Convert.ToBase64String(encryptedData));
        Console.WriteLine("Decrypted Message: " + decryptedMessage);
    }

    // Function to generate an RSA key pair
    static AsymmetricCipherKeyPair GenerateRSAKeyPair()
    {
        var keyGenerationParameters = new KeyGenerationParameters(new SecureRandom(), 2048); // You can adjust the key size as needed

        var keyPairGenerator = GeneratorUtilities.GetKeyPairGenerator("RSA");
        keyPairGenerator.Init(keyGenerationParameters);

        return keyPairGenerator.GenerateKeyPair();
    }

    // Function to encrypt a message using RSA
    static byte[] EncryptMessage(string message, AsymmetricKeyParameter publicKey)
    {
        var messageBytes = System.Text.Encoding.UTF8.GetBytes(message);
        var cipher = CipherUtilities.GetCipher("RSA/NONE/PKCS1Padding");
        cipher.Init(true, publicKey);
        return cipher.DoFinal(messageBytes);
    }

    // Function to decrypt a message using RSA
    static string DecryptMessage(byte[] encryptedData, AsymmetricKeyParameter privateKey)
    {
        var cipher = CipherUtilities.GetCipher("RSA/NONE/PKCS1Padding");
        cipher.Init(false, privateKey);
        var decryptedBytes = cipher.DoFinal(encryptedData);
        return System.Text.Encoding.UTF8.GetString(decryptedBytes);
    }
}
