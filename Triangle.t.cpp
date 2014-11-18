#include "Triangle.cpp"
#include <iostream>

int main()
{
    int a1[] = { 1 };
    int a2[] = { 2, 3 };
    std::vector< int > v1( a1, a1 + sizeof( a1 ) / sizeof( a1[ 0 ] ) );
    std::vector< int > v2( a2, a2 + sizeof( a2 ) / sizeof( a2[ 0 ] ) );

    std::vector< std::vector< int > > t;
    t.push_back( v1 );
    t.push_back( v2 );

    Solution sln;
    std::cout << sln.minimumTotal( t ) << std::endl;

    return 0;
}
