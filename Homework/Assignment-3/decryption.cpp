#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

#include <NTL/ZZ.h>

struct publicKey
{
	NTL::ZZ prime;
	NTL::ZZ paramA, paramB;
	NTL::ZZ genX, genY;
	NTL::ZZ pointX, pointY;
	NTL::ZZ multiplier = NTL::ZZ(3);

	std::string nullifier;

	publicKey()
	{
		std::ifstream publicKey("public.key");

		publicKey >> nullifier >> nullifier >> prime;
		publicKey.get();
		publicKey.get();
		std::getline(publicKey, nullifier);
		publicKey >> nullifier >> nullifier >> paramA;
		publicKey >> nullifier >> nullifier >> paramB;
		publicKey.get();
		publicKey.get();
		publicKey >> genX;
		publicKey.get();
		publicKey >> genY;
		publicKey >> nullifier;
		publicKey >> nullifier >> nullifier;
		publicKey.get();
		publicKey.get();
		publicKey >> pointX;
		publicKey.get();
		publicKey >> pointY;

		publicKey.close();
	}
};

std::pair<NTL::ZZ, NTL::ZZ> pointDouble(std::pair<NTL::ZZ, NTL::ZZ> point, publicKey key);

std::pair<NTL::ZZ, NTL::ZZ> pointAdd(std::pair<NTL::ZZ, NTL::ZZ> point, publicKey key);

char decryptCharacter(std::pair<NTL::ZZ, NTL::ZZ> toDecrypt, std::pair<NTL::ZZ, NTL::ZZ> halfMask, publicKey key);

int main(int argc, char const *argv[])
{
	publicKey key;

	std::vector<std::pair<std::pair<NTL::ZZ, NTL::ZZ>, std::pair<NTL::ZZ, NTL::ZZ>>> cipher;

	std::ifstream ciphertext("ciphertext.txt");
	std::ofstream plaintext("plaintext.txt");
	NTL::ZZ halfMaskX, halfMaskY;
	NTL::ZZ currentX, currentY;

	while (ciphertext >> currentX >> currentY >> halfMaskX >> halfMaskY)
	{
		cipher.emplace_back(std::pair<NTL::ZZ, NTL::ZZ>(currentX, currentY), std::pair<NTL::ZZ, NTL::ZZ>(halfMaskX, halfMaskY));
	}

	ciphertext.close();

	char currentCharacter;

	for (auto [current, halfMask] : cipher)
	{
		plaintext << decryptCharacter(current, halfMask, key);
	}

	return 0;
}

std::pair<NTL::ZZ, NTL::ZZ> pointDouble(std::pair<NTL::ZZ, NTL::ZZ> point, publicKey key)
{
	NTL::ZZ slope;
	NTL::ZZ top, bottom;
	NTL::ZZ newX, newY;

	top = ((3 * (point.first * point.first)) + key.paramA) % key.prime;
	bottom = NTL::InvMod((2 * point.second) % key.prime, key.prime) % key.prime;

	slope = (bottom * top) % key.prime;

	newX = ((slope * slope) - (2 * point.first)) % key.prime;
	newY = (-1 * (point.second + (slope * (newX - point.first)))) % key.prime;

	return std::pair<NTL::ZZ, NTL::ZZ>(newX, newY);
}

std::pair<NTL::ZZ, NTL::ZZ> pointAdd(std::pair<NTL::ZZ, NTL::ZZ> point1, std::pair<NTL::ZZ, NTL::ZZ> point2, publicKey key)
{
	NTL::ZZ slope;
	NTL::ZZ deltaY, deltaX;
	NTL::ZZ newX, newY;

	deltaY = (point2.second - point1.second) % key.prime;
	deltaX = NTL::InvMod(((point2.first - point1.first) % key.prime), key.prime) % key.prime;

	slope = (deltaX * deltaY) % key.prime;

	newX = ((slope * slope) - (point1.first + point2.first)) % key.prime;
	newY = (-1 * (point2.second + (slope * (newX - point2.first)))) % key.prime;

	return std::pair<NTL::ZZ, NTL::ZZ>(newX, newY);
}

char decryptCharacter(std::pair<NTL::ZZ, NTL::ZZ> toDecrypt, std::pair<NTL::ZZ, NTL::ZZ> halfMask, publicKey key)
{
	std::pair<NTL::ZZ, NTL::ZZ> fullMask;
	std::pair<NTL::ZZ, NTL::ZZ> message;

	fullMask = pointDouble(halfMask, key);
	fullMask = pointAdd(fullMask, halfMask, key);
	fullMask.second = (-1 * fullMask.second) % key.prime;

	message = pointAdd(toDecrypt, fullMask, key);

	return (char)NTL::conv<int>(message.first);
}