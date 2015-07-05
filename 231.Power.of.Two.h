/**
 * 231 Power of Two                                                        Easy
 * 
 * Given an integer, write a function to determine if it is a power of two.
 * 
 * Credits:
 * Special thanks to @jianchao.li.fighter for adding this problem and creating
 * all test cases.
 * 
 * Tags: Math, Bit Manipulation
 */

class Solution {
public:
    bool isPowerOfTwo( const int n ) {
        return ( n > 0 ) && !( n & ( n - 1 ) );
    }
};
