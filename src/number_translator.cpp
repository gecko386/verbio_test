#include <iostream>
#include "NumericParser.hpp"

/********************************************************************************/
/*                     Number words to digits                 	                */
/*                                                                              */
/*   using agreements in:                                                       */
/*   https://englishlessonsbrighton.co.uk/saying-large-numbers-english/         */
/*                                                                              */
/********************************************************************************/



int main(int argc, char **argv)
{
	NumericParser np;
	std::string input, output;

	while (std::getline(std::cin, input))
	{
		output = np.parse(input);
		std::cout << output << std::endl;
	}

	return 0;
}
