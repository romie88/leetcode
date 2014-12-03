#include "Distinct.Subsequences.cpp"
#include <iostream>

int main()
{
    std::string S( "b" );
    std::string T( "a" );

    Solution sln;
    std::cout << sln.numDistinct( S, T ) << std::endl;

    std::string S2( "adbdadeecadeadeccaeaabdabdbcdabddddabcaaadbabaaedeeddeaeebcdeabcaaaeeaeeabcddcebddebeebedaecccbdcbcedbdaeaedcdebeecdaaedaacadbdccabddaddacdddc" );
    std::string T2( "bcddceeeebecbc" );

    std::cout << sln.numDistinct( S2, T2 ) << std::endl;

    return 0;
}
