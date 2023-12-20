using System;
using System.Security.Cryptography;
using System.Text;

class Program
{
    static void Main()
    {
        // Generate an RSA key pair
        using (var rsa = new RSACryptoServiceProvider(2048))
        {
            // Message to be signed
            var message = "Hello, RSA Signature!";
            var message2 = "Hello, rSA Signature!";

            // Sign the message using the private key
            var signature = SignMessage(message, rsa);
            var signature2 = SignMessage(message2, rsa);

            // Verify the signature using the public key
            if (VerifySignature(message, signature, rsa))
            {
                Console.WriteLine("Signature is valid.");
            }
            else
            {
                Console.WriteLine("Signature is not valid.");
            }
        }
    }

    // Function to sign a message using RSA
    static byte[] SignMessage(string message, RSACryptoServiceProvider privateKey)
    {
        byte[] messageBytes = Encoding.UTF8.GetBytes(message);
        byte[] signature;

        using (var sha256 = SHA256.Create())
        {
            signature = privateKey.SignData(messageBytes, sha256);
        }

        return signature;
    }

    // Function to verify the RSA signature
    static bool VerifySignature(string message, byte[] signature, RSACryptoServiceProvider publicKey)
    {
        byte[] messageBytes = Encoding.UTF8.GetBytes(message);

        using (var sha256 = SHA256.Create())
        {
            return publicKey.VerifyData(messageBytes, sha256, signature);
        }
    }
}