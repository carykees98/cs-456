# Assignment 1 - Part 1: "Decryption"

The reason for the quotes around "Decryption" is that, while the goal of the assignment was to determine what the ciphertext said, we didn't have the private key, only the [public key](./publickeys.key), and therefore had to find a method of decryption other than that usually used with RSA.

The method that I used found the encrypted version of every ascii character from 0 (NULL) to 127 (DEL), and compared those values with those found in the [ciphertext](./ciphertext.txt) using a python dictionary. The letter associated with each matched encrypted version was then printed out to a file called "[plaintext.txt](./plaintext.txt)".

## Plaintext

```
You are reading the plaintext of our second assignment in cryptography.
For this assignment, first implement your own RSA cryptosystem for text files.
Second, re-encrypt this plaintext with your own RSA keys and then submit the
encrypted text file via email along with the RSA secret keys (which are the
RSA modulus and RSA secret decryption exponent used). You may implement RSA
in any programming language of your choice. Submit the source for your RSA
program in a separate compressed file by email. This assignment is due in a
month from today.
```