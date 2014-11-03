#include "Word.Break.II.cpp"
#include <iostream>

int main()
{
	std::string s( "aaaaaaa" );
	const char * words[] = {
		"aaaa",
		"aa",
		"a"
	};
	std::unordered_set< std::string >
		dict( words, words + sizeof( words ) / sizeof( words[ 0 ] ) );

	Solution sln;
	std::vector< std::string > result = sln.wordBreak( s, dict );

	for ( const auto & r : result )
		std::cout << r << std::endl;
	
	return 0;
}
