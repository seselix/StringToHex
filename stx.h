/*
            ..'''' `````|`````  ``..      ..'' 
         .''            |           ``..''     
      ..'               |           ..'`..     
....''                  |       ..''      ``.. 

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
SPDX-License-Identifier: MIT

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace stx
{

enum op_type
{
	s_to_x,
	x_to_s,
};

void Translate(const op_type& t, const std::string& filename);
std::string StringToHex(std::string& input);
std::string HexToString(std::string& input);


void Translate(const op_type& t, const std::string& filename)
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
		switch (t)
		{
		case op_type::s_to_x:
			tmp = StringToHex(filetext);
			break;
		case op_type::x_to_s:
			tmp = HexToString(filetext);
			break;
		default:
			break;
		}
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