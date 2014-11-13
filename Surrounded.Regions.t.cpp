#include "Surrounded.Regions.cpp"
#include <iostream>

int main()
{
	char b[][11]= {
		"XOXOXOOOXO",
        "XOOXXXOOOX",
		"OOOOOOOOXX",
		"OOOOOOXOOX",
		"OOXXOXXOOO",
		"XOOXXXOXXO",
		"XOXOOXXOXO",
		"XXOXXOXOOX",
		"OOOOXOXOXO",
		"XXOXXXXOOO" };
	std::vector< std::vector< char > > board;
	for ( int i = 0; i < 10; ++i )
	{
		std::vector< char > v;
		for ( int j = 0; j < 10; ++j )
			v.push_back( b[ i ][ j ] );
		
		board.push_back( v );
	}

	for ( const auto & r : board )
	{
		for ( const auto & c : r )
			std::cout << c << " ";

		std::cout << std::endl;
	}
	std::cout << std::endl;

	Solution sln;
	sln.solve( board );

	for ( const auto & r : board )
	{
		for ( const auto & c : r )
			std::cout << c << " ";

		std::cout << std::endl;
	}
	
	return 0;
}
