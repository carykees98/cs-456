# Assignment 2 - Part 1: Decryption

I was initially stumpted when it came to decrypting this assignment. There was one key thing missing that allowed me to do so, the private exponent: `a`.

This issue somewhat quickly became not so much of an issue as a hint was given in class telling us that the private exponent could be obtained from completing [Assignment 3](../../Assignment-3/).

After I completed Assignment 3 and obtained `a` I was able to finish my implementaiton of a decryption program for ElGamal and obtained the plaintext found below.


## Plaintext
```
CS456 Assignment 2 (Spring 2023)
Send back this plaintext unencrypted by email along with all the ElGamal keys used for the encryption.
Then, implement a simple socket-based chat protocol that uses a public-key cryptosystem (RSA or ElGamal) 
with a secret-key cryptosystem (DES or AES) in a programming language of your choice. Allow the users to 
choose the prime bit-length used for RSA/ElGamal and the secret passphrase used in DES/AES. 
Arrange an online demonstration of your program. You may work in groups of three.
```