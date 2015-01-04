//166 Fraction to Recurring Decimal [ Medium ]
//
//Given two integers representing the numerator and denominator of a fraction,
//return the fraction in string format.
//
//If the fractional part is repeating, enclose the repeating part in parentheses.
//
//For example,
//
//Given numerator = 1, denominator = 2, return "0.5".
//Given numerator = 2, denominator = 1, return "2".
//Given numerator = 2, denominator = 3, return "0.(6)".
//
//Credits:
//Special thanks to @Shangrila for adding this problem and creating all test cases.

//Tags: Hash Table, Math

#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>
#include <stdexcept>

class Solution {
public:
    std::string fractionToDecimal( int numerator, int denominator ) {
        
        std::string result;
        
        //denominator cannot be zero
        if ( denominator == 0 )
            throw std::invalid_argument( "denominator is zero" );
        
        //handle an overflow case
        if ( numerator == std::numeric_limits< int >::min()
          && std::abs( denominator ) == 1 ) {
            result = std::to_string( numerator );
            if ( denominator == -1 ) {
                result.erase( result.begin() );
            }
            return result;
        }
        
        //decide the sign of the result
        if ( ( numerator > 0 ) && ( denominator < 0 )
          || ( numerator < 0 ) && ( denominator > 0 ) )
            result += '-';

        //C++11 defines the integer division as following:
        //the quotient is truncated towards zero
        //now lets check a % b
        //if b == 0, then the result is undefined
        //if a == INT_MIN and b = -1, then a / b is not representible
        //in 2's complement systems. And a % b is undefined.
        //Except these special cases, we always have
        // ( a / b ) * b + a % b == a
        //Note that a % b has the same sign as a
        
        //get the integer part
        result += std::to_string( std::abs( numerator / denominator ) );

        int remainder = std::abs( numerator % denominator );
        if ( remainder == 0 )
            return result;

        //process the fraction part
        result += '.';
        
        //this hash map contains the remainder to the index of the quotient
        //in the result string
        std::unordered_map< int, int > m;
        while ( remainder != 0 ) {
            
            //found repeating remainder thus the quotient repeats accordingly
            //we need to stop
            const auto it = m.find( remainder );
            if ( it != m.end() ) {
                result.insert( it->second, 1, '(' );
                result += ')';
                break;
            }

            m[ remainder ] = result.size();
            
            //the logic here is to handle the input -1 and -2147483648
            if ( std::numeric_limits< int >::max() / 10 < remainder ) {
                int q;
                int r;
                get_quotient_and_remainder( remainder, denominator, q, r );
                result += std::to_string( q );
                remainder = r;
            } else {
                remainder *= 10;//potential overflow 
                result += std::to_string( std::abs( remainder / denominator ) );
                remainder %= denominator;
                remainder = std::abs( remainder );
            }
        }
        
        return result;
    }
    
    //this function calculate the quotient and remainder of a * 10 / b
    //why does we need this? considering -1 / -2147483648
    void get_quotient_and_remainder( int a, int b, int & q, int & r ) {
        a = std::abs( a );
        //b = 10 * m + n;
        int m = std::abs( b / 10 );
        int n = std::abs( b % 10 );
        //we estimate q as a / ( b / 10 ) first
        //obviously it is an over-estimate
        //we need to decrease the quotient until we get the the remainder
        //positive
        q = a / m;
        //we calculate the remainder as following
        //r = a * 10 - b * q
        //  = a * 10 - ( ( b / 10 ) * 10 + b % 10 ) * q
        //  = a * 10 - m * q * 10 - n * q
        //where n * q = ( n * q ) / 10 * 10 + ( n * q ) % 10
        //  = a * 10 - m * q * 10 - ( ( n * q ) / 10 * 10 + ( n * q ) % 10 )
        //  = a * 10 - m * q * 10 - ( n * q ) / 10 * 10 - ( n * q ) % 10
        //  = ( a - m * q - ( n * q ) / 10 ) * 10 - ( n * q ) % 10
        //Note that ( a - m * q - ( n * q ) / 10 ) * 10 will not overflow
        //but a * 10 very likely will overflow
        r = ( a - m * q - n * q / 10 ) * 10 - ( n * q ) % 10;
        while ( r < 0 ) {
            --q;
            r = ( a - m * q - n * q / 10 ) * 10 - ( n * q ) % 10;
        }
    }

};

