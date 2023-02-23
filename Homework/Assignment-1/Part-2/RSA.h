#pragma once

#include <fstream>
#include <string>

#include <NTL/ZZ.h>

namespace ckees
{
	class RSA
	{
	public:
		// Member Functions
		void encryptFile(std::ifstream &plaintext, std::ofstream &cyphertext);
		void decryptFile(std::ifstream &cyphertext, std::ofstream &plaintext);
		void generateKeys(int bits);

		// Constructors
		RSA(std::string mode);

	private:
		NTL::ZZ m_modulus;
		NTL::ZZ m_publicExponent;
		NTL::ZZ m_privateExponent;
		NTL::ZZ m_phi;

		/*
		TO-DO:
			- Generate primes, generate exponents
			- Find a library that permits the usage of arbitrary length integers
		*/
	};
} // namespace ckees