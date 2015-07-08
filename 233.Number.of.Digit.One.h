/**
 * Algorithms 233 Number of Digit One                                    Medium
 * 
 * Given an integer n, count the total number of digit 1 appearing in all
 * non-negative integers less than or equal to n.
 * 
 * For example:
 * Given n = 13,
 * Return 6, because digit 1 occurred in the following numbers: 1, 10, 11, 12,
 * 13.
 * 
 * Show Hint
 * 
 * 1. Beware of overflow
 * 
 * Tags: Math
 */

#include <algorithm>
#include <limits>

class Solution {
public:
    int countDigitOne( const int n ) {
        return count_digit_one_by_position2( n );
    }
private:
    /**
     * O( log n ) runtime - my implementation which suffered from overflow
     * 
     * There is a better implementation below does not need to explicitly
     * handle overflow.
     */
    int count_digit_one_by_position( const int n ) {
        int p = 1;
        int c = 0;
        bool overflowed = false;
        do {
            if ( p > std::numeric_limits< int >::max() / 10 ) {
                overflowed = true;
                break;
            }
            c += ( n / ( p * 10 ) * p
               + std::min( std::max( n % ( p * 10 ) - p + 1, 0 ), p ) );
            p *= 10;
        } while ( n / p );
        if ( overflowed )
            c += std::min( std::max( n - p + 1, 0 ), p );
        return c;
    }
    /**
     * O( n log n ) runtime - brute force
     */
    int count_digit_one_brute_force( const int n ) {
        int c = 0;
        for ( int i = 1; i <= n; ++i )
            c += count_digit_one_in_an_integer( i );
        return c;
    }
    int count_digit_one_in_an_integer( const int n ) {
        int c = 0;
        while ( n ) {
            c += n % 10 == 1;
        }
    }
    /**
     * O( lg n ) runtime
     * 
     * A solution from 'Beauty of Programming' 2.4
     * 
     * Let's say n = abcde where a, b, c, d, e are the five digits.
     * Now we need to calculate the number of times 1 appears on c.
     * 
     * If c == 0, then the number of times 1 appears on c is decided by
     * the higher digits. For example, 12013, these are 100 - 199, 1100 - 1199,
     * 2100 - 2199, ..., 11100 - 11199, totally 1200, i.e., ab * 100.
     * 
     * If c == 1, then the number of times 1 appears on c is decided by
     * the higher digits ab and also lower digits de. For example, 12113,
     * these are 100 - 199, 1100 - 1199, 2100 - 2199, ..., 11100 - 11199,
     * totally 1200, i.e., ab * 100. Impacted by the lower digits de,
     * 12100 - 12113, totally 114, i.e., 113 + 1.
     * 
     * If c > 1, then the number of times 1 appears on c is decided by
     * the higher digits. For example, 12213, these are 100 - 199, 1100 - 1199,
     * 2100 - 2199, ..., 11100 - 11199, 12100 - 12199, totally 1300, i.e.,
     * ( ab + 1 ) * 100.
     * 
     * Note that this idea is general and can be used to count digits 1 - 9.
     * Essential three cases, digit < c, digit == c, digit > c.
     * 
     * 0 is very similar to all the other digits.
     */
    int count_digit_one_by_position2( const int n ) {
        int c = 0;
        int p = 1;
        int x = n;
        while ( x ) {
            int d = n / p % 10;
            int higher = n / p / 10;//avoid overflow instead of n / ( p * 10 );
            int lower  = n % p;//equivalently n - ( n / p ) * p;
            if ( d < 1 ) {
                c += higher * p;
            } else if ( d == 1 ) {
                c += higher * p + lower + 1;
            } else {
                c += ( higher + 1 ) * p;
            }
            p *= 10;
            x /= 10;
        }
        return c;
    }
};
