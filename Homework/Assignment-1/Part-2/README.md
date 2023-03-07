# Assignment 1 - Part 2: Write RSA From Scratch

My language of choice for implementing RSA was C++. Perhaps not the most sensical as the language doesn't have native support for arbitrary length integers, however, it is the language that I am most familiar with so its the one I went with.

Because C++ doesn't have native support for some of the more crucial aspects of the implementation, I turned to a non-native library, specifically [NTL: A library for doing number theory](https://libntl.org/).

My implementation allows for varying bit integers to be used for `p` and `q`. During my testing I used integers with 1024 bits, in other words, the number of bits required for RSA-2048.