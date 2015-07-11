/**
 * Algorithms 12 Integer to Roman                                        Medium
 * 
 * Given an integer, convert it to a roman numeral.
 * 
 * Input is guaranteed to be within the range from 1 to 3999.
 * 
 * Tags: Math, String
 * Similar Problems: (E) Roman to Integer
 */

#include <string>

class Solution {
public:
    std::string intToRoman( int num ) {
        return int_to_roman_impl_2( num );
    }
private:
    /**
     * http://en.wikipedia.org/wiki/Roman_numerals
     * I 1
	 * V 5
     * X 10
     * L 50
	 * C 100
	 * D 500
     * M 1000
     */
    std::string int_to_roman_impl_1( int num ) {
        std::string result;
        
        int num_of_thousands = num / 1000;
        num %= 1000;
        result.append( num_of_thousands, 'M' );
        
        int num_of_hundreds = num / 100;
        num %= 100;
        append_roman_letter( num_of_hundreds, 'M', 'D', 'C', result );
        
        int num_of_tens = num / 10;
        num %= 10;
        append_roman_letter( num_of_tens, 'C', 'L', 'X', result );
        
        append_roman_letter( num, 'X', 'V', 'I', result );
        
        return result;
    }
    void append_roman_letter( const int     n,
                              const char    ten,
                              const char    five,
                              const char    one,
                              std::string & result ) {
        if ( n == 9 ) {
            result.append( 1, one ).append( 1, ten );
        } else if ( n > 5 ) {
            result.append( 1, five ).append( n - 5, one );
        } else if ( n == 5 ) {
            result.append( 1, five );
        } else if ( n == 4 ) {
            result.append( 1, one ).append( 1, five );
        } else {
            result.append( n, one );
        }
    }
    
    std::string int_to_roman_impl_2( int num ) {
        static const char * roman_digit_letters[] = {
            "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"
        };
        static const int roman_digit_values[] = {
            1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
        };
        std::string result;
        for ( int i = 0;
              i < sizeof( roman_digit_values ) / sizeof( roman_digit_values[ 0 ] );
              ++i ) {
            int n = num / roman_digit_values[ i ];
            for ( int k = 0; k < n; ++k )
                result.append( roman_digit_letters[ i ] );
            
            num %= roman_digit_values[ i ];
        }
        return result;
    }
};

