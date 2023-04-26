#pragma once

#include <fstream>
#include <string>

#include <NTL/ZZ.h>

namespace ckees
{
	class RSA
	{
	public:
		// Constructors
		RSA() : m_modulus(0), m_publicExponent(0), m_privateExponent(0), m_phi(0) {}
		RSA(long numberOfBits);
		RSA(NTL::ZZ modulus, NTL::ZZ publicExponent, NTL::ZZ phi) : m_modulus(modulus), m_publicExponent(publicExponent), m_phi(phi) {} // Public Key Constructor

		// Member Functions
		std::string encryptString(const std::string &message);
		std::string decryptString(const std::string &encryptedMessage);

		// Getters
		NTL::ZZ getModulus() { return m_modulus; }
		NTL::ZZ getPublicExp() { return m_publicExponent; }
		NTL::ZZ getPhi() { return m_phi; }

	private:
		void generateKeys(long numberOfBits);

	private:
		NTL::ZZ m_modulus;
		NTL::ZZ m_publicExponent;
		NTL::ZZ m_privateExponent;
		NTL::ZZ m_phi;
	};
} // namespace ckees