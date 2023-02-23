# Assignment 1 - Part 1: "Decryption"

The reason for the quotes around "Decryption" is that, while the goal of the assignment was to determine what the ciphertext said, we didn't have the private key, only the [public key](./publickeys.key), and therefore had to find a method of decryption other than that usually used with RSA.

The method that I used found the encrypted version of every ascii character from 0 (NULL) to 127 (DEL), and compared those values with those found in the [ciphertext](./ciphertext.txt) using a python dictionary. The letter associated with each matched encrypted version was then printed out to a file called "[plaintext.txt](./plaintext.txt)".