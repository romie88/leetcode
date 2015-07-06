/**
 * Algorithms 7 Reverse Integer                                            Easy
 * 
 * Reverse digits of an integer.
 * 
 * Example1: x = 123, return 321
 * Example2: x = -123, return -321
 * 
 * click to show spoilers
 * 
 * Have you thought about this?
 * Here are some good questions to ask before coding. Bonus points for you if
 * you have already thought through this!
 * 
 * If the integer's last digit is 0, what should the output be? ie, cases such
 * as 10, 100.
 * 
 * Did you notice that the reversed integer might overflow? Assume the input
 * is a 32-bit integer, then the reverse of 1000000003 overflows. How should
 * you handle such cases?
 * 
 * For the purpose of this problem, assume that your function returns 0 when
 * the reversed integer overflows.
 * 
 * Update (2014-11-10):
 * 
 * Test cases had been added to test the overflow behavior.
 * 
 * Tags: Math
 */

#include <limits>

class Solution {
public:
    int reverse( int x ) {
        bool negative = x < 0;
        int y = 0;
        while ( x ) {
            int d = x % 10;
            if ( ! negative ) {
                if ( y > ( ( std::numeric_limits< int >::max() - d ) / 10 ) )
                    return 0;
            } else {
                if ( y < ( ( std::numeric_limits< int >::min() - d ) / 10 ) )
                    return 0;
            }
            y = y * 10 + d;
            x /= 10;
        }
        return y;
    }
};

/**
 * Solution
 *
 * To check for overflow/underflow, we could check if ret > 214748364 or
 * ret < –214748364 before multiplying by 10. On the other hand, we do not need
 * to check if ret == 214748364, why?
 */
