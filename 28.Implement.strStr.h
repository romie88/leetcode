/**
 * Algorithms 28 Implement strStr()                                        Easy
 * 
 * Implement strStr().
 * 
 * Returns the index of the first occurrence of needle in haystack, or -1 if
 * needle is not part of haystack.
 * 
 * Update (2014-11-02):
 * 
 * The signature of the function had been updated to return the index instead
 * of the pointer. If you still see your function signature returns a char * or
 * String, please click the reload button to reset your code definition.
 * 
 * Tags: Two Pointers, String
 */

#include <string>
#include <vector>

class Solution {
public:
    int strStr( const std::string & haystack, const std::string & needle ) {
        return strstr_KMP( haystack, needle );
    }
private:
    /**
     * O( n * m ) runtime, O( 1 ) space - brute force
     */
    int strstr_brute_force( const std::string & t, const std::string & p ) {
        const int n = t.length();
        const int m = p.length();
        for ( int i = 0; i <= n - m; ++i ) {
            int j = 0;
            for ( j = 0; j < p.length(); ++j )
                if ( t[ i + j ] != p[ j ] ) break;
            if ( j == m ) return i;
        }
        return -1;
    }
    /**
     * Alternate brute force implementation; clean and no special if statements
     */
    int strstr_brute_force_2( const std::string & haystack,
                              const std::string & needle ) {
        for ( int i = 0; ; ++i ) {
            for ( int j = 0; ; ++j ) {
                if ( j == needle.length() ) return i;
                if ( i + j == haystack.length() ) return -1;
                if ( needle[ j ] != haystack[ i + j ] ) break;
            }
        }
    }
    /**
     * O( n + m ) runtime, O( m ) space - KMP algorithm
     */
    std::vector< int > calculate_prefix_function( const std::string  & p ) {
        const int m = p.length();
        std::vector< int > prefix( m, 0 );
        int k = 0;//the number of characters matched so far
        for ( int i = 1; i < m; ++i ) {
            while ( k > 0 && p[ k ] != p[ i ] )
                k = prefix[ k - 1 ];
            if ( p[ k ] == p[ i ] )
                ++k;
            prefix[ i ] = k;
        }
        return prefix;
    }
    int strstr_KMP( const std::string & t, const std::string & p ) {
        const int n = t.length();
        const int m = p.length();
        if ( m == 0 ) return 0;
        if ( n < m ) return -1;
        
        std::vector< int > prefix = calculate_prefix_function( p );
        int k = 0;//the number of characters matched so far
        for ( int i = 0; i < n; ++i ) {
            while ( k > 0 && t[ i ] != p[ k ] )
                k = prefix[ k - 1 ];
            
            if ( t[ i ] == p[ k ] ) ++k;
            if ( k == m ) return i - m + 1;
        }
        return -1;
    }
};
/**
 * Solution
 * 
 * O(nm) runtime, O(1) space – Brute force:
 * 
 * You could demonstrate to your interviewer that this problem can be solved
 * using known efficient algorithms such as Rabin-Karp algorithm, KMP algorithm,
 * and the Boyer-Moore algorithm. Since these algorithms are usually studied in
 * an advanced algorithms class, it is sufficient to solve it using the most
 * direct method in an interview – The brute force method.
 * 
 * The brute force method is straightforward to implement. We scan the needle
 * with the haystack from its first position and start matching all subsequent
 * letters one by one. If one of the letters does not match, we start over
 * again with the next position in the haystack.
 * 
 * The key is to implement the solution cleanly without dealing with each edge
 * case separately.
 */
