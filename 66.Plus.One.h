/**
 * Algorithms 66 Plus One                                                  Easy
 * 
 * Given a non-negative number represented as an array of digits, plus one to
 * the number.
 * 
 * The digits are stored such that the most significant digit is at the head of
 * the list.
 * 
 * Tags: Array, Math
 * Similar Problems: (M) Multiply Strings, (E) Add Binary
 */

#include <vector>

class Solution {
public:
    std::vector< int > plusOne( const std::vector< int > & digits ) {
        if ( digits.empty() ) return digits;
        int carry = 0;
        std::vector< int > results( digits );
        ++results.back();
        for ( int i = results.size() - 1; i >= 0; --i ) {
            results[ i ] += carry;
            if ( results[ i ] > 9 ) {
                results[ i ] -= 10;
                carry = 1;
            } else {
                carry = 0;
                break;
            }
        }
        if ( carry > 0 )
            results.insert( results.begin(), carry );
            
        return results;
    }
};
