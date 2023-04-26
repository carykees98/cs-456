#include "RSA.h"

#include <fstream>
#include <sstream>

#include <NTL/ZZ.h>

namespace ckees
{
	std::string RSA::encryptString(const std::string &toEncrypt)
	{
		NTL::ZZ currentEncrypted;
		std::ostringstream encryptedMessage;

		for (auto &&character : toEncrypt)
		{
			NTL::LowLevelPowerMod(currentEncrypted, NTL::conv<NTL::ZZ>(character), m_publicExponent, m_modulus);
			encryptedMessage << currentEncrypted << "," << std::endl;
		}

		return encryptedMessage.str();
	}

	std::string RSA::decryptString(const std::string &toDecrypt)
	{
		NTL::ZZ currentDecrypted_ZZ;
		NTL::ZZ currentEncrypted;
		std::string current;
		std::istringstream encryptedStream(toDecrypt);
		std::ostringstream decryptedMessage;

		while (encryptedStream >> current)
		{
			currentEncrypted = NTL::ZZ(NTL::INIT_VAL, current.c_str());
			NTL::LowLevelPowerMod(currentDecrypted_ZZ, currentEncrypted, m_privateExponent, m_modulus);
			decryptedMessage << (char)NTL::conv<int>(currentDecrypted_ZZ);
		}

		return decryptedMessage.str();
	}

	void RSA::generateKeys(long numberOfBits)
	{
		NTL::ZZ p = NTL::RandomPrime_ZZ(numberOfBits);
		NTL::ZZ q = NTL::RandomPrime_ZZ(numberOfBits);

		m_modulus = p * q;
		m_phi = ((p - 1) * (q - 1)) / NTL::GCD(p - 1, q - 1);
		m_publicExponent = NTL::RandomPrime_ZZ(numberOfBits / 4);

		while (NTL::GCD(m_phi, m_publicExponent) != 1)
		{
			m_publicExponent = NTL::RandomPrime_ZZ(numberOfBits / 4);
		}

		m_privateExponent = NTL::InvMod(m_publicExponent, m_phi);
	}

	RSA::RSA(long numberOfBits)
	{
		generateKeys(numberOfBits);
	}
} // namespace ckees