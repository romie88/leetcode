/**
 * Algorithms 67 Add Binary                                                Easy
 * 
 * Given two binary strings, return their sum (also a binary string).
 * 
 * For example,
 * a = "11"
 * b = "1"
 * Return "100".
 * 
 * Tags: Math, String
 * Similar Problems: (M) Add Two Numbers, (M) Multiply Strings, (E) Plus One
 *                   (E) Add Binary
 */

#include <string>

class Solution {
public:
    std::string addBinary( const std::string & a, const std::string & b ) {
        const int a_len = a.length();
        const int b_len = b.length();
        std::string result( std::max( a_len, b_len ), '0' );
        int carry = 0;
        int i = a_len - 1;
        int j = b_len - 1;
        for ( ; i >= 0 || j >= 0; --i, --j ) {
            int a_val = i >= 0 ? a[ i ] - '0' : 0;
            int b_val = j >= 0 ? b[ j ] - '0' : 0;
            int sum = a_val + b_val + carry;
            if ( sum > 1 ) {
                sum -= 2;
                carry = 1;
            } else {
                carry = 0;
            }
            result[ std::max( i, j ) ] = sum + '0';
        }
        if ( carry > 0 )
            result.insert( 0, 1, '0' + carry );
        
        return result;
    }
};
