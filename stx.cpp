#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "argparse.h"

namespace stx //---------------------------------------------------- stx:: <- begin
{
void Translate(bool isToHex, std::string& filename);
std::string StringToHex(std::string& input);
std::string HexToString(std::string& input);
}

//	TODO add a warning before operation happens
int main(int argc, char* argv[])
{
	argparse::ArgumentParser program("stx");
	program.add_argument("-x", "--file_to_hex")
		.help("Converts [file] text to hexadecimal values. Either '-x' or '-s' is required. Not both")
		.default_value(false)
		.implicit_value(true);
	program.add_argument("-s", "--file_to_string")
		.help("Converts [file] text to ascii value. Either '-x' or '-s' is required. Not both")
		.default_value(false)
		.implicit_value(true);
	program.add_argument("file")
		.help("File to be converted")
		.required();

	try {
		program.parse_args(argc, argv);
	} catch (const std::runtime_error& err) {
		std::cerr << err.what() << std::endl;
		std::cerr << program;
		std::exit(1);
	}

	auto filename = program.get<>("file");

	if (program["-x"] == true && program["-s"] == false)
	{
		stx::Translate(true, filename); 
		return EXIT_SUCCESS;
	}
	if (program["-s"] == true && program["-x"] == false)
	{
		stx::Translate(false, filename); return EXIT_SUCCESS;
		return EXIT_SUCCESS;
	}
	
	std::cerr << program;
	return EXIT_FAILURE;
}

namespace stx //---------------------------------------------------- stx:: <- begin
{

void Translate(bool isToHex, std::string& filename)
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
		while (std::getline(f, tmp, (char)0x1f))
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

}