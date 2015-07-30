/**
 * 72 Edit Distance                                                        Hard
 * 
 * Given two words word1 and word2, find the minimum number of steps required
 * to convert word1 to word2. (each operation is counted as 1 step.)
 * 
 * You have the following 3 operations permitted on a word:
 * 
 * a) Insert a character
 * b) Delete a character
 * c) Replace a character
 * 
 * Tags: Dynamic Programming, String
 * Similar Problems: (M) One Edit Distance
 */

#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int minDistance( const std::string & word1, const std::string & word2 ) {
        return min_distance_dp( word1, word2 );
    }
private:
    /**
     * O(mn) runtime, O(mn) space
     * 
     * D( i, j ) the minimum distance between word1[ 0 ... i - 1 ]
     * and word2[ 0 ... j - 1 ]
     * D( i, 0 ) = i
     * D( 0, j ) = j
     * D( i, j ) = min  D( i - 1, j ) + 1,
     *                      if Delete word1[ i - 1 ] from word1[ 0 ... i - 1 ]
     *                  D( i, j - 1 ) + 1,
     *                      if Insert word2[ j - 1 ] to word1[ 0 ... i - 1 ] at the end
     *                  D( i - 1, j - 1 ) + 0 if word1[ i - 1 ] == word2[ j - 1 ]
     *                                      1 if word1[ i - 1 ] != word2[ j - 1 ] Replacement
     */
    int min_distance_dp( const std::string & w1, const std::string & w2 ) {
        std::vector< std::vector< int > >
            D( w1.length() + 1, std::vector< int >( w2.length() + 1, 0 ) );
        
        D[ 0 ][ 0 ] = 0;
        for ( int i = 1; i <= w1.length(); ++i ) D[ i ][ 0 ] = i;
        for ( int j = 1; j <= w2.length(); ++j ) D[ 0 ][ j ] = j;
        for ( int i = 1; i <= w1.length(); ++i ) {
            for ( int j = 1; j <= w2.length(); ++j ) {
                D[ i ][ j ] = std::min( D[ i - 1 ][ j ], D[ i ][ j - 1 ] ) + 1;
                D[ i ][ j ] = std::min(
                        D[ i ][ j ],
                        D[ i - 1 ][ j - 1 ] + ( w1[ i - 1 ] != w2[ j - 1 ] ) );
            }
        }
        return D[ w1.length() ][ w2.length() ];
    }
    /**
     * O( mn ) runtime, O( n ) space
     * 
     * Space optimized DP
     */
    int min_distance_dp2( const std::string & w1, const std::string & w2 ) {
        std::vector< int > D( w2.length() + 1, 0 );
        std::vector< int > D2( w2.length() + 1, 0 );
        for ( int j = 0; j <= w2.length(); ++j ) D[ j ] = j;
        for ( int i = 1; i <= w1.length(); ++i ) {
            D2[ 0 ] = i;
            for ( int j = 1; j <= w2.length(); ++j ) {
                D2[ j ] = std::min( D[ j ], D2[ j - 1 ] ) + 1;
                D2[ j ] = std::min( D2[ j ],
                                    D[ j - 1 ] + ( w1[ i - 1 ] != w2[ j - 1 ] ) );
            }
            D2.swap( D );
        }
        return D[ w2.length() ];
    }
};
