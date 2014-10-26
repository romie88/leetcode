#include "Multiply.Strings.cpp"

#include <iostream>

int main()
{
	std::string n1( "359" );
	std::string n2( "73478" );

	Solution s;
	std::cout << s.multiply( n1, n2 ) << std::endl;

	std::cout << s.multiply( "9335", "0" ) << std::endl;

	std::cout << s.multiply( "0", "9335" ) << std::endl;

	std::cout << s.multiply( "6", "501" ) << std::endl;

	return 0;
}
