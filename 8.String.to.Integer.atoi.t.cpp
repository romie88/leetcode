#include "String.to.Integer.atoi.cpp"

#include <iostream>

int main()
{
	Solution s;
	std::cout << s.atoi( "-2147483648" ) << std::endl;
	std::cout << s.atoi( "-2147483647" ) << std::endl;
	std::cout << s.atoi( "-2147483649" ) << std::endl;

	std::cout << s.atoi( "2147483647" ) << std::endl;
	std::cout << s.atoi( "2147483648" ) << std::endl;
	std::cout << s.atoi( "2147483649" ) << std::endl;

	return 0;
}
