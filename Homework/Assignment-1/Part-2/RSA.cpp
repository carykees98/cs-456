#include <fstream>

#include "RSA.h"
#include <NTL/ZZ.h>

namespace ckees
{
	void RSA::encryptFile(std::ifstream &plaintext, std::ofstream &ciphertext)
	{
		char currentDecrypted;
		NTL::ZZ currentEncrypted;
		while (plaintext.get(currentDecrypted))
		{
			if (currentDecrypted != '\0')
			{
				NTL::LowLevelPowerMod(currentEncrypted, NTL::conv<NTL::ZZ>(currentDecrypted), m_publicExponent, m_modulus);
				ciphertext << currentEncrypted << std::endl;
			}
			else
				break;
		}
	}

	void RSA::decryptFile(std::ifstream &ciphertext, std::ofstream &plaintext)
	{
		NTL::ZZ currentDecrypted_ZZ;
		NTL::ZZ currentEncrypted;

		while (ciphertext >> currentEncrypted)
		{
			NTL::LowLevelPowerMod(currentDecrypted_ZZ, currentEncrypted, m_privateExponent, m_modulus);
			plaintext << (char)NTL::conv<int>(currentDecrypted_ZZ);
		}
	}

	void RSA::generateKeys(int bits)
	{
		std::ofstream publicKey("public.key");
		std::ofstream privateKey("private.key");

		NTL::ZZ p = NTL::RandomPrime_ZZ(1024);
		NTL::ZZ q = NTL::RandomPrime_ZZ(1024);

		m_modulus = p * q;
		m_phi = ((p - 1) * (q - 1)) / NTL::GCD(p - 1, q - 1);
		m_publicExponent = NTL::RandomPrime_ZZ(256);

		while (NTL::GCD(m_phi, m_publicExponent) != 1)
		{
			m_publicExponent = NTL::RandomPrime_ZZ(256);
		}

		m_privateExponent = NTL::InvMod(m_publicExponent, m_phi);

		publicKey << m_modulus << std::endl
				  << m_publicExponent << std::endl;
		publicKey.close();

		privateKey << m_modulus << std::endl
				   << m_privateExponent << std::endl;
		privateKey.close();
	}

	RSA::RSA(std::string mode)
	{
		if (mode == "decrypt")
		{
			std::ifstream privateKey("private.key");
			privateKey >> m_modulus >> m_privateExponent;
			privateKey.close();
		}
	}
} // namespace ckees