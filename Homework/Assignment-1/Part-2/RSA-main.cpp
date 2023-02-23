#include <iostream>
#include <fstream>
#include <string>

#include "RSA.h"

void printMenu();

int main(int argc, char const *argv[])
{
	if (argc == 1)
	{
		std::cerr << "No arguments passed" << std::endl
				  << "-----------------" << std::endl;
		printMenu();
		exit(EXIT_FAILURE);
	}

	if (std::string(argv[1]) == "--help")
	{
		printMenu();
		exit(EXIT_FAILURE);
	}
	else if (std::string(argv[1]) == "encrypt")
	{
		if (argc < 5)
		{
			std::cout << "Too few arguments: Expected 4, Received " << argc - 1 << std::endl
					  << "-----------------" << std::endl;
			printMenu();
			exit(EXIT_FAILURE);
		}

		int numberOfBits = std::stoi(argv[2]);
		std::ifstream plaintext(argv[3]);
		std::ofstream cyphertext(argv[4]);
		ckees::RSA encryptor("encrypt");

		encryptor.generateKeys(numberOfBits);
		encryptor.encryptFile(plaintext, cyphertext);
	}
	else if (std::string(argv[1]) == "decrypt")
	{
		if (argc < 4)
		{
			std::cout << "Too few arguments: Expected 3, Received " << argc - 1 << std::endl
					  << "-----------------" << std::endl;
			printMenu();
			exit(EXIT_FAILURE);
		}

		std::ifstream cyphertext(argv[2]);
		std::ofstream plaintext(argv[3]);
		ckees::RSA decryptor("decrypt");

		decryptor.decryptFile(cyphertext, plaintext);
	}
	else
	{
		std::cerr << "Invalid argument: " << argv[1] << std::endl
				  << "-----------------" << std::endl;
		printMenu();
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}

void printMenu()
{
	std::cout << "Usage: " << std::endl
			  << std::endl
			  << "--help: Displays this menu" << std::endl
			  << std::endl
			  << "RSA encrypt <number of bits> <plaintext file> <cyphertext file>" /* << "[optional: <public key file> <private key file>]" */ << std::endl
			  << "RSA decrypt <cyphertext file> <plaintext file>" /* << "[Optional: <private key file>]" */ << std::endl;
}
