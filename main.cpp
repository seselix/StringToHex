#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>

#include "argparse.h"

void Translate(bool isToHex, const char* filename);
std::string StringToHex(std::string& input);
std::string HexToString(std::string& input);

//	TODO add a warning before operation happens
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Require -x or -s and a filename";
		return EXIT_FAILURE;
	}
	std::string command {argv[1]};
	if (command == "-x" || command == "-s")
		Translate((command == "-x"), argv[2]);

	std::cout << "Translation success";
}

void Translate(bool isToHex, const char* filename)
{
	std::fstream f;
	f.open(filename, f.in);
	if (!f.is_open())
	{
		std::cout << "Failed to open file: " << filename;
		return;
	}
	else
	{
		// Read from File
		std::string filetext {};
		std::string tmp {};
		while (std::getline(f, tmp))
			filetext += tmp;
		f.close();

		// Write To File
		f.open(filename, f.out);
		if (isToHex)
			tmp = StringToHex(filetext);
		else	
			tmp = HexToString(filetext);

		f << tmp;
		f.close();
	}
}

std::string StringToHex(std::string& input)
{
	std::stringstream ss;
	for (int i = 0; i < input.size(); ++i)
		ss << std::setw(2) << std::hex << (int)input[i];
	return ss.str();
}

std::string HexToString(std::string& input)
{
	std::stringstream ss;
	for (int i = 0; i < input.size(); i += 2)
		ss << (unsigned char)std::stoi(input.substr(i,2), nullptr, 16);
	return ss.str();
}
