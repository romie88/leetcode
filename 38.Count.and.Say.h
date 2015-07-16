/**
 * Algorithms 38 Count and Say                                            Easy
 * 
 * The count-and-say sequence is the sequence of integers beginning as follows:
 * 1, 11, 21, 1211, 111221, ...
 * 
 * 1 is read off as "one 1" or 11.
 * 11 is read off as "two 1s" or 21.
 * 21 is read off as "one 2, then one 1" or 1211.
 * Given an integer n, generate the nth sequence.
 * 
 * Note: The sequence of integers will be represented as a string.
 *
 * Tags: String
 */

#include <string>
#include <stdexcept>

class Solution {
public:
    /**
     * O( n * w ) runtime, w is the length of the string
     */
    std::string countAndSay( const int n ) {
        if ( n <= 0 ) throw std::invalid_argument( "n is not positive" );
        
        std::string s( "1" );
        for ( int k = 1; k < n; ++k ) {
            int count = 1;
            std::string s2;//new result from s
            for ( int i = 1; i < s.length(); ++i ) {
                if ( s[ i - 1 ] == s[ i ] ) {
                    ++count;
                } else {
                    s2 += std::to_string( count );
                    s2 += s[ i - 1 ];
                    count = 1;
                }
            }
            s2 += std::to_string( count );
            s2 += s[ s.length() - 1 ];
            s2.swap( s );
        }
        return s;
    }
    /**
     * In fact we can prove that its impossible number 4 will ever appear
     * in any sequence.
     * Assume that in a certain step there is a x1111y. Considering what the
     * previous sequence. There are only two ways:
     * 
     * I. certain number of x (not 1), 1, 1, y of a number (not 1)
     *    which actually should be said as
     *    number of x, 2 of 1, y of a number (not 1)
     *    i.e., x21y instead of x1111y
     * II. x number of 1, 1 of 1, 1 of y
     *     which actually should be said as (x + 1) of 1, 1 of y
     *     i.e., (x+1)11y instead of x1111y
     */
};
