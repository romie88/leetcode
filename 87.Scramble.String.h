/**
 * Algorithms 87 Scramble String                                           Hard
 * 
 * Given a string s1, we may represent it as a binary tree by partitioning it
 * to two non-empty substrings recursively.
 * 
 * Below is one possible representation of s1 = "great":
 * 
 *     great
 *    /    \
 *   gr    eat
 *  / \    /  \
 * g   r  e   at
 *            / \
 *           a   t
 * 
 * To scramble the string, we may choose any non-leaf node and swap its two
 * children.
 * 
 * For example, if we choose the node "gr" and swap its two children, it
 * produces a scrambled string "rgeat".
 * 
 *     rgeat
 *    /    \
 *   rg    eat
 *  / \    /  \
 * r   g  e   at
 *            / \
 *           a   t
 * 
 * We say that "rgeat" is a scrambled string of "great".
 * 
 * Similarly, if we continue to swap the children of nodes "eat" and "at", it
 * produces a scrambled string "rgtae".
 * 
 *     rgtae
 *    /    \
 *   rg    tae
 *  / \    /  \
 * r   g  ta  e
 *        / \
 *       t   a
 * 
 * We say that "rgtae" is a scrambled string of "great".
 * 
 * Given two strings s1 and s2 of the same length, determine if s2 is a
 * scrambled string of s1.
 * 
 * Tags: Dynamic Programming, String
 */

#include <vector>
#include <iostream>

class Solution {
public:
    bool isScramble( const std::string & s1, const std::string & s2 ) {
        return is_scramble_DP( s1, s2 );
    }
private:
    /**
     * Brute force recursion with pruning
     */
    bool is_scramble_recursive_impl( const std::string & s1, int b1, int e1,
                                     const std::string & s2, int b2, int e2,
                                     std::vector< int > & ht ) {
        if ( e1 - b1 != e2 - b2 ) return false;
        if ( b1 == e1 ) return s1[ b1 ] == s2[ b2 ];
        
        //a little optimization by comparing s1[ b1, e1 ] with s2[ b2, e2 ]
        //if the same, return true immediately.
        bool is_same = true;
        for ( int i = b1, j = b2; i <= e1; ++i, ++j ) {
            if ( s1[ i ] != s2[ j ] ) {
                is_same = false;
                break;
            }
        }
        if ( is_same ) return true;
        
        //Before we brute force break s1 and s2 into segments and recurse
        //Pruning by making sure s1[ b1, e1 ] and s2[ b2, e2 ] contain
        //the same set of characters.
        //The most straightforward way is to copy strings, sort, then compare.
        //A better idea is to use bucket sort to count the characters of s1 and
        //s2.
        for ( int i = 0; i < ht.size(); ++i )
            ht[ i ] = 0;
        for ( int i = b1; i <= e1; ++i )
            ++ht[ s1[ i ] ];
        for ( int i = b2; i <= e2; ++i )
            --ht[ s2[ i ] ];
        for ( int i = 0; i < ht.size(); ++i )
            if ( ht[ i ] != 0 )
                return false;
        
        for ( int i = b1; i < e1; ++i ) {
            //[ b1, i ] & [ i + 1, e1 ]
            //[ b2, i - b1 + b2 ] & [ i - b1 + b2 + 1, e2 ]
            if ( is_scramble_recursive_impl( s1, b1, i, s2, b2, i - b1 + b2, ht )
              && is_scramble_recursive_impl( s1, i + 1, e1, s2, i - b1 + b2 + 1, e2, ht ) )
                return true;
            
            //[ b1, i ] & [ i + 1, e1 ]
            //[ e2 + b1 - i, e2 ] & [ b2, e1 + b2 - i - 1 ]
            if ( is_scramble_recursive_impl( s1, b1, i, s2, e2 + b1 - i, e2, ht )
              && is_scramble_recursive_impl( s1, i + 1, e1, s2, b2, e1 + b2 - i - 1, ht ) )
                return true;
        }
        
        return false;
    }
    bool is_scramble_recursive( const std::string & s1, const std::string & s2 ) {
        std::vector< int > ht( 256, 0 );
        return is_scramble_recursive_impl( s1, 0, s1.length() - 1,
                                           s2, 0, s2.length() - 1,
                                           ht );
    }
    /**
     * The above recursive solution solved many duplicated sub-problems.
     * For example, s1 = "rgeat", s2 = "great". When we pick i = 0 to break
     * the two strings, s1 -> "r" + "geat", s2 -> "g" + "reat". Now one of the
     * sub-problem is isScramble( "reat", "geat" ). For this sub-problem, pick
     * the first letter and we have sub-problem isScramble( "eat", "eat" ).
     * However initially if we pick i = 1, s1 -> "rg" + "eat", s2 -> "gr" + "eat".
     * Thus sub-problem isScramble( "eat", "eat" ) is solved twice.
     * 
     * Define DP[ k ][ i ][ j ] to be true if substring with length k
     * within s1 starting from index i and s2 starting from index j isScramble.
     * 
     * DP[ s1.length() ][ 0 ][ 0 ] is the answer we are looking for.
     * 
     * Initial condition: DP[ 1 ][ i ][ j ] = s1[ i ] == s[ j ]
     * Recursion equation: DP[ k ][ i ][ j ]
     * Let len be from 1 to k - 1.
     *    DP[ len ][ i ][ j ] && DP[ k - len ][ i + len ][ j + len ]
     * || DP[ len ][ i ][ j + k - len ] && DP[ k - len ][ i + len ][ j ]
     * DP[ k ][ i ][ j ] is true if for any len from 1 to k - 1 the above
     * equation evaluted to be true.
     * 
     * O( n^4 ) runtime, O( n^3 ) space
     */
    bool is_scramble_DP( const std::string & s1, const std::string & s2 ) {
        if ( s1.length() != s2.length() ) return false;
        
        std::vector< std::vector< std::vector< bool > > > DP( s1.length() + 1,
            std::vector< std::vector< bool > >( s1.length(),
                std::vector< bool >( s2.length(), false ) ) );
        for ( int i = 0; i < s1.length(); ++i )
            for ( int j = 0; j < s2.length(); ++j )
                DP[ 1 ][ i ][ j ] = s1[ i ] == s2[ j ];
        
        for ( int k = 2; k <= s1.length(); ++k ) {
            for ( int i = 0; i <= s1.length() - k; ++i ) {
                for ( int j = 0; j <= s2.length() - k; ++j ) {
                    DP[ k ][ i ][ j ] = false;
                    for ( int len = 1; len < k; ++len ) {
                        DP[ k ][ i ][ j ]
                            = ( DP[ len ][ i ][ j ] && DP[ k - len ][ i + len ][ j + len ] )
                           || ( DP[ len ][ i ][ j + k - len ] && DP[ k - len ][ i + len ][ j ] );
                        if ( DP[ k ][ i ][ j ] ) break;
                    }
                }
            }
        }
        
        return DP[ s1.length() ][ 0 ][ 0 ];
    }
};
