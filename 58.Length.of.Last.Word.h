/**
 * Algorithms 58 Length of Last Word                                       Easy
 * 
 * Given a string s consists of upper/lower-case alphabets and empty space
 * characters ' ', return the length of last word in the string.
 *
 * If the last word does not exist, return 0.
 * 
 * Note: A word is defined as a character sequence consists of non-space
 * characters only.
 * 
 * For example, 
 * Given s = "Hello World",
 * return 5.
 * 
 * Tags: String
 */

#include <string>

class Solution {
public:
    int lengthOfLastWord( const std::string & s ) {
        int i = s.length() - 1;
        while ( i >= 0 && std::isspace( s[ i ] ) )
            --i;
        if ( i < 0 ) return 0;
        int j = i;
        while ( j >= 0 && ! std::isspace( s[ j ] ) )
            --j;
        return i - j;
    }
};
