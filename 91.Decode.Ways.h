/**
 * Algorithms 91 Decode Ways                                             Medium
 *
 * A message containing letters from A-Z is being encoded to numbers using the
 * following mapping:
 *
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 *
 * Given an encoded message containing digits, determine the total number of
 * ways to decode it.
 *
 * For example,
 * Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).
 *
 * The number of ways decoding "12" is 2.
 *
 * Tags: Dynamic Programming, String
 */

#include <string>

class Solution {
public:
    int numDecodings( const std::string & s ) {
        return num_decodings_DP( s );
    }
private:
    /**
     * exponential runtime
     *
     * T( n ) = T( n - 1 ) + T( n - 2 )
     * it is a Fibonacci sequence thus exponential
     *
     * Recursively search all the possibilities
     */
    int num_decodings_recursive_helper( const std::string & s, const int i ) {
        if ( i == s.length() || s[ i ] < '1' && s[ i ] > '9' ) return 1;
        int c = num_decodings_recursive_helper( s, i + 1 );
        if ( i + 1 < s.length()
          && ( ( s[ i ] == '1' && s[ i + 1 ] >= '0' && s[ i + 1 ] <= '9' )
            || ( s[ i ] == '2' && s[ i + 1 ] >= '0' && s[ i + 1 ] <= '6' ) ) )
            c += num_decodings_recursive_helper( s, i + 2 );
        return c;
    }
    int num_decodings_recursive( const std::string & s ) {
        if ( s.empty() ) return 0;
        return num_decodings_recursive_helper( s, 0 );
    }

    /**
     * O( n ) runtime, O( 1 ) space - DP
     *
     * dp[ i ] is the number of ways to decode the substring [ 0, i - 1 ]
     * with length i.
     *
     * dp[ 0 ] = 0
     * dp[ i ] = dp[ i - 1 ] + dp[ i - 2 ]   if s[ i - 2 ] and s[ i - 1 ] can
     *                                       be decoded together;
     *         = dp[ i - 1 ]                 otherwise
     *
     * Note that we do not need to have a whole vector just need two
     * variables.
     */
    int num_decodings_DP( const std::string & s ) {
        if ( s.empty() ) return 0;
        if ( s.size() == 1 )
            return s[ 0 ] >= '1' && s[ 0 ] <= '9' ? 1 : 0;

        int dp2 = 1;//equivalent to dp[ i - 2 ]
        int dp1 = s[ 0 ] >= '1' && s[ 0 ] <= '9' ? 1 : 0;//equivalent to dp[ i - 1 ]
        for ( int j = 1; j < s.length(); ++j ) {
            int tmp = ( ( s[ j ] >= '1' && s[ j ] <= '9' ) ? dp1 : 0 )
                    + ( ( s[ j - 1 ] == '1' && s[ j ] >= '0' && s[ j ] <= '9' )
                     || ( s[ j - 1 ] == '2' && s[ j ] >= '0' && s[ j ] <= '6' ) ? dp2 : 0 );
            dp2 = dp1;
            dp1 = tmp;
        }
        return dp1;
    }
};