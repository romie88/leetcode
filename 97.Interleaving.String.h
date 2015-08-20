/**
 * Algorithms 97 Interleaving String                                       Hard
 *
 * Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
 *
 * For example,
 * Given:
 * s1 = "aabcc",
 * s2 = "dbbca",
 *
 * When s3 = "aadbbcbcac", return true.
 * When s3 = "aadbbbaccc", return false.
 *
 * Tags: Dynamic Programming, String
 */

class Solution {
public:
    bool isInterleave( const std::string & s1,
                       const std::string & s2,
                       const std::string & s3 ) {
        return is_interleave_recursive( s1, s2, s3 );
    }
private:
    /**
     * O( 2^n ) runtime - brute force recursion
     *
     * The recursive problem has many overlapping subproblems
     * For example, s1 = "XXX" s2 = "XXX" s3 = "XXXXXX".
     */
    bool is_interleave_recursive( const std::string & s1,
                                  const std::string & s2,
                                  const std::string & s3 ) {
        if ( s1.length() + s2.length() != s3.length() ) return false;

        return is_interleave_recursive_impl( s1, 0, s2, 0, s3, 0 );
    }
    bool is_interleave_recursive_impl( const std::string & s1,
                                       int                 i1,
                                       const std::string & s2,
                                       int                 i2,
                                       const std::string & s3,
                                       int                 i3 ) {
        if ( i1 == s1.length() ) {
            while ( i2 < s2.length() )
                if ( s2[ i2++ ] != s3[ i3++ ] ) return false;
            return true;
        }
        if ( i2 == s2.length() ) {
            while ( i1 < s1.length() )
                if ( s1[ i1++ ] != s3[ i3++ ] ) return false;
            return true;
        }

        return ( s1[ i1 ] == s3[ i3 ]
              && is_interleave_recursive_impl( s1, i1 + 1, s2, i2, s3, i3 + 1 ) )
            || ( s2[ i2 ] == s3[ i3 ]
              && is_interleave_recursive_impl( s1, i1, s2, i2 + 1, s3, i3 + 1 ) );
    }

    /**
     * O( m * n ) runtime, O( n ) space - DP
     *
     * where m is the length of s1, n is the length of s2.
     *
     * let dp[ i ][ j ] where i = 0, 1, ..., l1
     *                        j = 0, 1, ..., l2
     * dp[ i ][ j ] is true if s1[ 0 ... i - 1 ] and s2[ 0 ... j - 1 ] is
     * interleaving s3[ 0 ... i + j - 1 ]
     *
     * dp[ 0 ][ 0 ] is true
     * dp[ 0 ][ j ] is true if s2[ 0 ... j - 1 ] == s3[ 0 ... j - 1 ]
     *
     * Actually we can optimize the space usage by reducing the matrix
     * into a vector.
     */
    bool is_interleave_DP( const std::string & s1,
                           const std::string & s2,
                           const std::string & s3 ) {
        if ( s1.length() + s2.length() != s3.length() ) return false;
        if ( s2.empty() ) return s1 == s3;

        std::vector< bool > P( false, s2.length() + 1 );
        P[ 0 ] = true;
        for ( int j = 1; j <= s2.length(); ++j ) {
            P[ j ] = P[ j - 1 ] && s2[ j - 1 ] == s3[ j - 1 ];
        }
        for ( int i = 1; i <= s1.length(); ++i ) {
            P[ 0 ] = P[ 0 ] && s1[ i - 1 ] == s3[ i - 1 ];
            for ( int j = 1; j <= s2.length(); ++j ) {
                P[ j ] = P[ j ] && s1[ i - 1 ] == s3[ i + j - 1 ]
                      || P[ j - 1 ] && s2[ j - 1 ] == s3[ i + j - 1 ];
            }
        }
        return P[ s2.length() ];
    }
};