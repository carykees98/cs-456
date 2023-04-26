# Assignment 2 - Part 2: Creating a Simple Chat App

## Instructions

The instructions for this part of the assignment came from [Part 1](../Part-1/). They were as follows:

```
CS456 Assignment 2 (Spring 2023)
Send back this plaintext unencrypted by email along with all the ElGamal keys used for the encryption.
Then, implement a simple socket-based chat protocol that uses a public-key cryptosystem (RSA or ElGamal) 
with a secret-key cryptosystem (DES or AES) in a programming language of your choice. Allow the users to 
choose the prime bit-length used for RSA/ElGamal and the secret passphrase used in DES/AES. 
Arrange an online demonstration of your program. You may work in groups of three.
```

## Design Choices

I had already implemented RSA for the second part of [Assignment 1](../../Assignment-1/Part-2/), however, that implementation required the use of files for the plaintext and ciphertext, something which I needed to change for this assignment. After a little bit of tweaking, I changed my RSA implementation to take in an unencrypted string and to return an encrypted one.

For AES we were allowed to use a library to make the assignment a little easier. The library I decided on was [plusaes](https://github.com/kkAyataka/plusaes) as it was a header only library which made it very easy to include where needed.

I decided to make a client class to make the handling of the RSA and AES keys easier. The client stores the keys and has two different modes of operation depending on the type of socket being used, either `request` or `reply`. The library that I used for this was [zmqpp](https://github.com/zeromq/zmqpp). It provided an easier to use socket interface than the Linux socket api and offered an object oriented approach which I prefer.