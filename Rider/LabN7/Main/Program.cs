using System;
using Org.BouncyCastle.Asn1;
using Org.BouncyCastle.Asn1.CryptoPro;
using Org.BouncyCastle.Crypto;
using Org.BouncyCastle.Crypto.Generators;
using Org.BouncyCastle.Crypto.Parameters;
using Org.BouncyCastle.Crypto.Signers;
using Org.BouncyCastle.Security;

class Program
{
    static void Main()
    {
        // Generate a key pair
        var keyPair = GenerateKeyPair();
        

        // Message to be signed
        var message = "Hello, GOST R 34.10-94!";
        var message2 = "Hello, gOST R 34.10-94!";

        // Sign the message using the private key
        var signature = SignMessage(message, keyPair.Private);
        var signature2 = SignMessage(message2, keyPair.Private);
        Console.WriteLine(signature);
        

        // Verify the signature using the public key
        if (VerifySignature(message, signature, keyPair.Public))
        {
            Console.WriteLine("Signature is valid.");
        }
        else
        {
            Console.WriteLine("Signature is not valid.");
        }
    }
    static AsymmetricCipherKeyPair GenerateKeyPair()
    {
        // Specify the key size (e.g., 256 bits)
        int keySize = 256;
    
        // Get the key pair generator
        var keyPairGenerator = GeneratorUtilities.GetKeyPairGenerator("ECGOST3410");
    
        // Set up key generation parameters with the specified key size
        var keyGenParam = new KeyGenerationParameters(new SecureRandom(), keySize);
    
        // Initialize the key pair generator with parameters
        keyPairGenerator.Init(keyGenParam);
    
        // Generate the key pair
        return keyPairGenerator.GenerateKeyPair();
    }


    //
    // static AsymmetricCipherKeyPair GenerateKeyPair()
    // {
    //     // Specify the key size (e.g., 256 bits)
    //     int keySize = 256;
    //
    //     var keyGenerationParameters = new Gost3410KeyGenerationParameters(
    //         new SecureRandom(), CryptoProObjectIdentifiers.GostR3410x94CryptoProA);
    //
    //     var keyGenerationParametersWithSize = new ParametersWithRandom(keyGenerationParameters, new SecureRandom());
    //
    //     var keyPairGenerator = GeneratorUtilities.GetKeyPairGenerator("ECGOST3410");
    //     keyPairGenerator.Init(keyGenerationParametersWithSize, keySize);
    //
    //     return keyPairGenerator.GenerateKeyPair();
    // }

    // Function to perform the GOST R 34.10-94 digital signature algorithm
    static byte[] SignMessage(string message, AsymmetricKeyParameter privateKey)
    {
        var messageBytes = System.Text.Encoding.UTF8.GetBytes(message);
        var signer = SignerUtilities.GetSigner("ECGOST3410");
        signer.Init(true, privateKey);
        signer.BlockUpdate(messageBytes, 0, messageBytes.Length);
        return signer.GenerateSignature();
    }

    // Function to verify the GOST R 34.10-94 digital signature
    static bool VerifySignature(string message, byte[] signature, AsymmetricKeyParameter publicKey)
    {
        var messageBytes = System.Text.Encoding.UTF8.GetBytes(message);
        var signer = SignerUtilities.GetSigner("ECGOST3410");
        signer.Init(false, publicKey);
        signer.BlockUpdate(messageBytes, 0, messageBytes.Length);
        return signer.VerifySignature(signature);
    }
}
