def main():
    cyphertext = open("ciphertext.txt", 'r')
    plaintext = open("plaintext.txt", 'w')
    publicKey = open("publickeys.key", 'r')

    modulus, exponent = publicKey.read().split()
    modulus = int(modulus)
    exponent = int(exponent)
    publicKey.close()

    encryptionKey = {}

    for i in range(0, 127):
        encryptionKey[chr(i)] = encrypt(i, modulus, exponent)

    encryptedText = cyphertext.read().split()
    decryptedText = []

    for character in encryptedText:
        for char in encryptionKey:
            if int(character) == encryptionKey[char]:
                decryptedText.append(char)

    for character in decryptedText:
        plaintext.write(character)


def encrypt(ascii, modulus, exponent):
    return pow(ascii, exponent, modulus)


if __name__ == "__main__":
    main()
