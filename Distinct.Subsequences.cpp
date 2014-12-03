//Distinct Subsequences 2012-10-18
//
//Given a string S and a string T, count the number of distinct subsequences
//of T in S.
//
//A subsequence of a string is a new string which is formed from the original
//string by deleting some (can be none) of the characters without disturbing
//the relative positions of the remaining characters. (ie, "ACE" is a
//subsequence of "ABCDE" while "AEC" is not).
//
//Here is an example:
//S = "rabbbit", T = "rabbit"
//
//Return 3.

//Tags:

#include <string>
#include <vector>

class Solution {
public:
    int numDistinct( std::string S, std::string T ) {

        if ( S.length() < T.length() )
            return 0;

        std::vector< std::vector< int > >
            t( T.length(), std::vector< int >( S.length(), 0 ) );
        
        t[ 0 ][ 0 ] = ( T[ 0 ] == S[ 0 ] );
        for ( int j = 1; j < S.length(); ++j )
        {
            t[ 0 ][ j ] = t[ 0 ][ j - 1 ] + ( T[ 0 ] == S[ j ] );
        }

        for ( int i = 1; i < T.length(); ++i )
        {
            for ( int j = i; j < S.length(); ++j )
            {
                if ( T[ i ] == S[ j ] )
                {
                    t[ i ][ j ] = t[ i - 1 ][ j - 1 ] + t[ i ][ j - 1 ];
                }
                else
                {
                    t[ i ][ j ] = t[ i ][ j - 1 ];
                }
            }
        }

        return t[ T.length() - 1 ][ S.length() - 1 ];
    }
};
