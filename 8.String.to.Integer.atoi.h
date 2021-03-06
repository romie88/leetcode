/**
 * Algorithms 8 String to Integer (atoi)                                   Easy 
 * 
 * Implement atoi to convert a string to an integer.
 * 
 * Hint: Carefully consider all possible input cases. If you want a challenge,
 * please do not see below and ask yourself what are the possible input cases.
 * 
 * Notes: It is intended for this problem to be specified vaguely (ie, no given
 * input specs). You are responsible to gather all the input requirements up
 * front.
 * 
 * Update (2015-02-10):
 * The signature of the C++ function had been updated. If you still see your
 * function signature accepts a const char * argument, please click the reload
 * button to reset your code definition.
 * 
 * Requirements for atoi:
 * 
 * The function first discards as many whitespace characters as necessary until
 * the first non-whitespace character is found. Then, starting from this
 * character, takes an optional initial plus or minus sign followed by as many
 * numerical digits as possible, and interprets them as a numerical value.
 * 
 * The string can contain additional characters after those that form the
 * integral number, which are ignored and have no effect on the behavior of
 * this function.
 * 
 * If the first sequence of non-whitespace characters in str is not a valid 
 * integral number, or if no such sequence exists because either str is empty
 * or it contains only whitespace characters, no conversion is performed.
 * 
 * If no valid conversion could be performed, a zero value is returned.
 * If the correct value is out of the range of representable values,
 * INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.
 * 
 * Tags: Math, String
 * Similar Problems: (E) Reverse Integer, (H) Valid Number
 */

#include <string>
#include <cctype>
#include <limits>

class Solution {
public:
    int myAtoi( const std::string & str ) {
        const int n = str.length();
        int i = 0;
        while ( i < n && std::isspace( str[ i ] ) ) ++i;
        if ( i == n ) return 0;
        
        bool is_negative = false;
        if ( str[ i ] == '-' ) {
            is_negative = true;
            ++i;
        } else if ( str[ i ] == '+' )
            ++i;
        
        int result = 0;
        while ( i < n && std::isdigit( str[ i ] ) ) {
            int d = str[ i ] - '0';
            if ( ! is_negative ) {
                if ( result > ( ( std::numeric_limits< int >::max() - d ) / 10 ) )
                    return std::numeric_limits< int >::max();
                result = result * 10 + d;
            } else {
                if ( result < ( ( std::numeric_limits< int >::min() + d ) / 10 ) )
                    return std::numeric_limits< int >::min();
                result = result * 10 - d;
            }
            ++i;
        }
        return result;
    }
};

/**
 * Solution
 * 
 * To deal with overflow, inspect the current number before multiplication.
 * If the current number is greater than 214748364, we know it is going to
 * overflow. On the other hand, if the current number is equal to 214748364,
 * we know that it will overflow only when the current digit is greater than
 * or equal to 8.
 */
