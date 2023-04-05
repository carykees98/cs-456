#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

#include <NTL/ZZ.h>

struct publicKey
{
	NTL::ZZ p;
	NTL::ZZ g;
	NTL::ZZ b;

	// Not part of the public key file, obtained through completion of Assignment 3
	NTL::ZZ a;

	publicKey()
	{
		std::ifstream publicKey("public.key");
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				publicKey.get();
			}
			switch (i)
			{
			case 0:
				publicKey >> p;
			case 1:
				publicKey >> g;
			case 2:
				publicKey >> b;
			}
		}

		publicKey.close();

		publicKey.open("assignment3.answer");
		publicKey >> a;
	}
};

char decryptCharacter(NTL::ZZ halfMask, NTL::ZZ toDecrypt, publicKey key);

int main(int argc, char const *argv[])
{
	publicKey key;

	std::vector<std::pair<NTL::ZZ, NTL::ZZ>> cipher;

	std::ifstream ciphertext("ciphertext.txt");
	std::ofstream plaintext("plaintext.txt");
	NTL::ZZ halfMask;
	NTL::ZZ currentCharacter;
	char voidChar;

	while (ciphertext >> halfMask >> voidChar >> currentCharacter)
	{
		cipher.emplace_back(halfMask, currentCharacter);
	}
	ciphertext.close();

	for (auto &&[half, character] : cipher)
	{
		plaintext << decryptCharacter(half, character, key);
	}

	return 0;
}

char decryptCharacter(NTL::ZZ halfMask, NTL::ZZ toDecrypt, publicKey key)
{
	NTL::ZZ fullMask;
	NTL::ZZ message;

	NTL::LowLevelPowerMod(fullMask, halfMask, key.a, key.p); // sets the full mask
	fullMask = NTL::InvMod(fullMask, key.p);

	message = (toDecrypt * fullMask) % key.p;

	return (char)NTL::conv<int>(message);
}