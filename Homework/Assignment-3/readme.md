# Assignment 3: Decryption

The method of encryption for this assignment was Elliptical Curve ElGamal. The goal of this assignment was to decrypt the ciphertext to obtain the secret exponent, `a`, for use in [Assignment 2 - Part 1](../Assignment-2/Part-1/).

This was a fairly straight forward problem and unlike Assignment 2, all required components were provided in the [public key file](./public.key). Technically, the secret multiplier wasn't provided, however after a little bit of thinking I realized that it was 3. This is because while 2 is the smallest prime number, it is the only even one, making it the oddest of them all, and the second lowest prime was 3 meaning that was the only other possible answer.

After completing my implementation, which can be found in [decryption.cpp](./decryption.cpp), I obtained the following value for `a` and used it to finally solve the first part of assignment 2.

## Plaintext

```
a = 1489762725384264603055010538429289038837647105192096463886523026785052160514553816474316549886461400562000723398283898880104979767967109516953842986698784
```