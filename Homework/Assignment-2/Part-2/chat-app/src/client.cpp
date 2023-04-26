#include "client.h"

#include <sstream>
#include <vector>

#include <zmqpp/zmqpp.hpp>
#include <plusaes.hpp>

#define clearScreen "\033c"

namespace ckees
{
	void client::run()
	{
		int userNum;
		std::cout << clearScreen;
		m_AESDecryptionKey = generateAESKey("");
		std::cout << clearScreen;
		generateRSAKey();

		while (true)
		{
			std::cout << clearScreen
					  << "Are you user 1 or 2?" << std::endl
					  << ">>> ";
			std::cin >> userNum;

			std::cout << clearScreen;

			if (userNum == 1)
			{
				userOne();
				break;
			}
			else if (userNum == 2)
			{
				userTwo();
				break;
			}
			else
			{
				std::cout << "Invalid user number." << std::endl
						  << std::endl;
			}
		}
	}

	void client::userOne()
	{
		// Setup
		std::string endpoint = "tcp://*:5555";
		zmqpp::context context;
		zmqpp::socket clientSocket(context, zmqpp::socket_type::reply);
		zmqpp::message message;

		clientSocket.bind(endpoint);

		// recieve RSA public key
		std::string info, modulus, publicExponent, phi;
		clientSocket.receive(info);
		std::istringstream(info) >> modulus >> publicExponent >> phi;
		m_RSAEncrypt = RSA(NTL::ZZ(NTL::INIT_VAL, modulus.c_str()), NTL::ZZ(NTL::INIT_VAL, publicExponent.c_str()), NTL::ZZ(NTL::INIT_VAL, phi.c_str()));

		// send RSA public key
		std::ostringstream RSAInfo;
		RSAInfo << m_RSADecrypt.getModulus() << " " << m_RSADecrypt.getPublicExp() << " " << m_RSADecrypt.getPhi();
		message << RSAInfo.str();
		clientSocket.send(message);

		// recieve encrypted AES passphrase
		std::string phrase;
		clientSocket.receive(phrase);
		phrase = m_RSADecrypt.decryptString(phrase);
		m_AESEncryptionKey = generateAESKey(phrase);

		// send encrypted AES passphrase
		message << m_RSAEncrypt.encryptString(m_decryptionPhrase).c_str();
		clientSocket.send(message);

		// setup for loop
		std::string messageBuffer;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clears the buffer

		//  main message loop
		while (true)
		{
			int throwaway;
			clientSocket.receive(messageBuffer);
			plusaes::decrypt_ecb((const unsigned char *)messageBuffer.c_str(), messageBuffer.size(), (const unsigned char *)m_AESDecryptionKey.data(), throwaway, (unsigned char *)messageBuffer.data(), messageBuffer.size(), NULL);
			if (messageBuffer.find_first_of('`') != messageBuffer.npos)
			{
				messageBuffer.erase(messageBuffer.begin() + messageBuffer.find_first_of('`'), messageBuffer.end());
			}
			std::cout << messageBuffer << std::endl;

			std::cout << ">>> ";
			std::getline(std::cin, messageBuffer);
			int lengthMod16 = messageBuffer.length() % 16;
			if (lengthMod16 != 0)
			{
				messageBuffer.resize(messageBuffer.length() + lengthMod16);
				for (size_t i = messageBuffer.back() - lengthMod16; i < messageBuffer.back(); i++)
				{
					messageBuffer[i] = '`';
				}
			}
			plusaes::encrypt_ecb((const unsigned char *)messageBuffer.c_str(), messageBuffer.length(), (const unsigned char *)m_AESEncryptionKey.data(), m_AESEncryptionKey.size(), (unsigned char *)messageBuffer.data(), messageBuffer.size(), false);
			message << messageBuffer;
			clientSocket.send(message);
		}
	}

	void client::userTwo()
	{
		// Setup
		std::string endpoint = "tcp://localhost:5555";
		zmqpp::context context;
		zmqpp::socket clientSocket(context, zmqpp::socket_type::request);
		zmqpp::message message;

		clientSocket.connect(endpoint);

		// send RSA public key
		std::ostringstream RSAInfo;
		RSAInfo << m_RSADecrypt.getModulus() << " " << m_RSADecrypt.getPublicExp() << " " << m_RSADecrypt.getPhi();
		message << RSAInfo.str();
		clientSocket.send(message);

		// receive RSA public key
		std::string info, modulus, publicExponent, phi;
		clientSocket.receive(info);
		std::istringstream(info) >> modulus >> publicExponent >> phi;
		m_RSAEncrypt = RSA(NTL::ZZ(NTL::INIT_VAL, modulus.c_str()), NTL::ZZ(NTL::INIT_VAL, publicExponent.c_str()), NTL::ZZ(NTL::INIT_VAL, phi.c_str()));

		// send encrypted AES passphrase
		message << m_RSAEncrypt.encryptString(m_decryptionPhrase).c_str();
		clientSocket.send(message);

		// recieve encrypted AES passphrase
		std::string phrase;
		clientSocket.receive(phrase);
		phrase = m_RSADecrypt.decryptString(phrase);
		m_AESEncryptionKey = generateAESKey(phrase);

		// setup for loop
		std::string messageBuffer;
		unsigned char buffer;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clears the buffer

		// main message loop
		while (true)
		{
			std::cout << ">>> ";
			std::getline(std::cin, messageBuffer);
			int lengthMod16 = messageBuffer.length() % 16;
			if (lengthMod16 != 0)
			{
				messageBuffer.resize(messageBuffer.length() + lengthMod16);
				for (size_t i = messageBuffer.back() - lengthMod16; i < messageBuffer.back(); i++)
				{
					messageBuffer[i] = '`';
				}
			}
			plusaes::encrypt_ecb((const unsigned char *)messageBuffer.c_str(), messageBuffer.length(), (const unsigned char *)m_AESEncryptionKey.data(), m_AESEncryptionKey.size(), (unsigned char *)messageBuffer.data(), messageBuffer.size(), false);
			message << messageBuffer;
			clientSocket.send(message);

			int throwaway;
			clientSocket.receive(messageBuffer);
			plusaes::decrypt_ecb((const unsigned char *)messageBuffer.c_str(), messageBuffer.size(), (const unsigned char *)m_AESDecryptionKey.data(), throwaway, (unsigned char *)messageBuffer.data(), messageBuffer.size(), NULL);
			if (messageBuffer.find_first_of('`') != messageBuffer.npos)
			{
				messageBuffer.erase(messageBuffer.begin() + messageBuffer.find_first_of('`'), messageBuffer.end());
			}
			std::cout << messageBuffer << std::endl;
		}
	}

	std::vector<unsigned char> client::generateAESKey(std::string phrase)
	{
		static int count = 0;
		int length;

		if (count == 0)
		{
			while (true)
			{
				std::cout << "What would you like to use as your passphrase for AES? (16 - 32 characters long)" << std::endl
						  << ">>> ";
				std::getline(std::cin, phrase);

				if (phrase.length() < 16)
				{
					std::cout << "Your passphrase is too short." << std::endl
							  << std::endl;
				}
				else
				{
					m_decryptionPhrase = phrase;
					break;
				}
			}
		}
		count++;

		if (phrase.length() >= 16 && phrase.length() < 24)
		{
			length = 16;
		}
		else if (phrase.length() >= 24 && phrase.length() < 32)
		{
			length = 24;
		}
		else if (phrase.length() >= 32)
		{
			length = 32;
		}

		const char key[length + 1] = "";

		strncpy(const_cast<char *>(key), phrase.c_str(), length);

		if (length == 16)
		{
			return plusaes::key_from_string((const char(*)[17]) & key);
		}
		else if (length == 24)
		{
			return plusaes::key_from_string((const char(*)[25]) & key);
		}
		else if (length == 32)
		{
			return plusaes::key_from_string((const char(*)[33]) & key);
		}
		else
			return std::vector<unsigned char>();
	}

	void client::generateRSAKey()
	{
		long numberOfBits;
		std::cout << "How many bits would you like to use for the RSA encryption?" << std::endl
				  << ">>> ";
		std::cin >> numberOfBits;

		m_RSADecrypt = RSA(numberOfBits);
	}
} // namespace ckees