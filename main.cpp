#include <iostream>

#include "argparse.h"

#include "stx.h"

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
		stx::Translate(stx::op_type::s_to_x, filename); 
		return EXIT_SUCCESS;
	}
	if (program["-s"] == true && program["-x"] == false)
	{
		stx::Translate(stx::op_type::x_to_s, filename); return EXIT_SUCCESS;
		return EXIT_SUCCESS;
	}
	
	std::cerr << program;
	return EXIT_FAILURE;
}