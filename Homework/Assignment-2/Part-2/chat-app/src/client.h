#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "RSA.h"

namespace ckees
{
	class client
	{
	public:
		// Member Functions
		void run();
		void sendMessage(const std::string message);

		// Constructors
		client() = default;

	private:
		std::vector<unsigned char> generateAESKey(std::string phrase);
		void generateRSAKey();

		void userTwo(); // Socket Connector
		void userOne(); // Socket Listener

	private:
		std::vector<unsigned char> m_AESEncryptionKey;
		std::vector<unsigned char> m_AESDecryptionKey;
		std::string m_decryptionPhrase;

		ckees::RSA m_RSAEncrypt;
		ckees::RSA m_RSADecrypt;
	};
} // namespace ckees