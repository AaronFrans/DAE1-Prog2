#include "pch.h"
#include <iostream>
#include <sstream>
#include <fstream>

void DoConsoleRead()
{
	std::string line{  };
	std::string string{  };
	while (std::getline(std::cin, line))
	{
		if (line.empty()) {
			break;
		}
		string += line += " ";
	}
	std::cout << string << "\n";
}
void DoFileRead()
{
	std::string input{  };
	std::string line{};
	std::ifstream is{ "Resources/SoftwareQuotesInput.txt" };
	while (is)
	{

		std::getline(is, line);
		input += line.empty()? "\n" : line;

	}

	std::ofstream os{ "Resources/SoftwareQuotesOutput.txt" };
	if (os)
	{
		os << input;
	}

}


int main()
{
	//DoConsoleRead();
	DoFileRead();
}

