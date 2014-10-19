#include "Maximum.Product.Subarray.cpp"

#include <iostream>

int main()
{
	Solution s;

	int a1[] = { -4, -3, -2 };
	std::cout << s.maxProduct( a1, sizeof( a1 ) / sizeof( a1[ 0 ] ) )
		      << std::endl;

	int a2[] = { -2, 0, -1 };
	std::cout << s.maxProduct( a2, sizeof( a2 ) / sizeof( a2[ 0 ] ) )
		      << std::endl;

	int a3[] = { -3, 0, 1, -2 };
	std::cout << s.maxProduct( a3, sizeof( a3 ) / sizeof( a3[ 0 ] ) )
		      << std::endl;
}
