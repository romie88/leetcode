/**
 * Algorithms 10 Regular Expression Matching                               Hard
 * 
 * Implement regular expression matching with support for '.' and '*'.
 * 
 * '.' Matches any single character.
 * '*' Matches zero or more of the preceding element.
 * 
 * The matching should cover the entire input string (not partial).
 * 
 * The function prototype should be:
 * bool isMatch(const char *s, const char *p)
 * 
 * Some examples:
 * isMatch("aa","a") ? false
 * isMatch("aa","aa") ? true
 * isMatch("aaa","aa") ? false
 * isMatch("aa", "a*") ? true
 * isMatch("aa", ".*") ? true
 * isMatch("ab", ".*") ? true
 * isMatch("aab", "c*a*b") ? true
 * 
 * Tags: Dynamic Programming, Backtracking, String
 * Similar Problems: (H) Wildcard Matching
 */

#include <string>
#include <vector>
#include <stdexcept>

class Solution {
public:
    bool isMatch( const std::string & s, const std::string & p ) {
        return is_match_DP( s, p );
    }
private:
    /**
     * Worst case exponential runtime - Brute force recursive
     * 
     * Note when we try to match "x*" we cannot go greedy. For example,
     * s = "aaa" and p = "a*a".
     */
    bool is_match_recursive( const std::string & s, const std::string & p ) {
        return is_match_recursive_impl( s, 0, p, 0 );
    }
    bool is_match_recursive_impl( const std::string & s, int i,
                                  const std::string & p, int j ) {
        const int n = s.length();
        const int m = p.length();
        //we must check if regular expression string is empty or not first
        //consider the case s = "" and p = "a*"
        if ( m == j ) return n == i;
        //note that p contains "x*" then every match scans two characters.
        else if ( m - 1 == j ) {
            //p[ j ] cannot be '*'
            return n - 1 == i && ( s[ i ] == p[ j ] || '.' == p[ j ] );
        } else {
            //p has at least two characters left unmatched
            if ( p[ j + 1 ] != '*' ) {
                return i < n && ( s[ i ] == p[ j ] || '.' == p[ j ] )
                    && is_match_recursive_impl( s, i + 1, p, j + 1 );
            } else {
#if 0
                // "x*" does not match anything, i.e., zero x.
                if ( is_match_recursive_impl( s, i, p, j + 2 ) ) return true;
                return i < n && ( s[ i ] == p[ j ] || '.' == p[ j ] )
                    && is_match_recursive_impl( s, i + 1, p, j );
#endif
                while ( i < n && ( s[ i ] == p[ j ] || '.' == p[ j ] ) ) {
                    if ( is_match_recursive_impl( s, i, p, j + 2 ) )
                        return true;
                    ++i;
                }
                return is_match_recursive_impl( s, i, p, j + 2 );
            }
        }
    }
    /**
     * O( m * n ) runtime, O( m * n ) space - DP solution
     */
    bool is_match_DP( const std::string & s, const std::string & p ) {
        const int m = s.length();
        const int n = p.length();
        //D[ i ][ j ] == true if s[ 0 ... i - 1 ] and p[ 0 ... j - 1 ] match
        std::vector< std::vector< bool > > D( m + 1, std::vector< bool >( n + 1, false ) );
        D[ 0 ][ 0 ] = true;
        //all D[ i ][ 0 ] = false 1 <= i < m
        //so we know D[ i ][ j ] for j = 0;
        //to calculate D[ i ][ j ] we need to check p[ j - 1 ]
        for ( int i = 0; i <= m; ++i ) {
            //j = 0 cases we already initialized
            for ( int j = 1; j <= n; ++j ) {
                if ( p[ j - 1 ] != '*' ) {
                    D[ i ][ j ] = i > 0
                               && ( s[ i - 1 ] == p[ j - 1 ] || p[ j - 1 ] == '.' )
                               && D[ i - 1 ][ j - 1 ];
                } else {
                    //'*' should not be the first character in the pattern
                    if ( j <= 1 )
                        throw std::invalid_argument( "'*' should not be the first character in the pattern" );
                    
                    //'*' matches zero or one 
                    if ( D[ i ][ j - 2 ] || D[ i ][ j - 1 ] )
                        D[ i ][ j ] = true;
                    //match multiple preceding elements
                    else if ( i > 0
                           && ( s[ i - 1 ] == p[ j - 2 ] || p[ j - 2 ] == '.' )
                           && D[ i - 1 ][ j ] )
                        D[ i ][ j ] = true;
                }
            }
        }
        return D[ m ][ n ];
    }
};

