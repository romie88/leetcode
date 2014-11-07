#include "Candy.cpp"
#include <iostream>

int main()
{
	int r[] = { 2, 1 };
	std::vector< int > ratings( r, r + sizeof( r ) / sizeof( r[ 0 ] ) );

	Solution s;
	std::cout << s.candy( ratings ) << std::endl;
	
	return 0;
}
