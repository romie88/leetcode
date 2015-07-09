/**
 * Algorithms 13 Roman to Integer                                          Easy
 * 
 * Given a roman numeral, convert it to an integer.
 * 
 * Input is guaranteed to be within the range from 1 to 3999.
 * 
 * Tags: Math, String
 */

#include <string>

class Solution {
public:
    int romanToInt( const std::string & s ) {
        return roman_to_int2( s );
    }
private:
    int roman_to_int( const std::string & s ) {
        int result = 0;
        for ( int i = 0; i < s.length(); ++i ) {
            if ( s[ i ] == 'C' ) {
                if ( i < s.length() && ( s[ i + 1 ] == 'M' || s[ i + 1 ] == 'D' ) ) {
                    result += get_roman_digit_value( s[ i ], s[ i + 1 ] );
                    ++i;
                } else {
                    result += get_roman_digit_value( s[ i ] );
                }
            } else if ( s[ i ] == 'X' ) {
                if ( i < s.length() && ( s[ i + 1 ] == 'C' || s[ i + 1 ] == 'L' ) ) {
                    result += get_roman_digit_value( s[ i ], s[ i + 1 ] );
                    ++i;
                } else {
                    result += get_roman_digit_value( s[ i ] );
                }
            } else if ( s[ i ] == 'I' ) {
                if ( i < s.length() && ( s[ i + 1 ] == 'X' || s[ i + 1 ] ==  'V' ) ) {
                    result += get_roman_digit_value( s[ i ], s[ i + 1 ] );
                    ++i;
                } else {
                    result += get_roman_digit_value( s[ i ] );
                }
            } else {
                result += get_roman_digit_value( s[ i ] );
            }
        }
        return result;
    }
    int get_roman_digit_value( const char c ) {
        switch ( c ) {
            case 'M': return 1000;
            case 'D': return 500;
            case 'C': return 100;
            case 'L': return 50;
            case 'X': return 10;
            case 'V': return 5;
            case 'I': return 1;
        }
    }
    int get_roman_digit_value( const char c1, const char c2 ) {
        if ( c1 == 'C' && c2 == 'M' ) return 900;
        if ( c1 == 'C' && c2 == 'D' ) return 400;
        if ( c1 == 'X' && c2 == 'C' ) return 90;
        if ( c1 == 'X' && c2 == 'L' ) return 40;
        if ( c1 == 'I' && c2 == 'X' ) return 9;
        if ( c1 == 'I' && c2 == 'V' ) return 4;
    }
    
    /**
     * Solution from CleanCodeHandbook
     */
    int roman_to_int2( const std::string & s ) {
        int result = 0;
        int prev = 0;
        int curr = 0;
        for ( int i = 0; i < s.length(); ++i ) {
            curr = get_roman_digit_value( s[ i ] );
            result += ( curr > prev ) ? ( curr - 2 * prev ) : curr;
            prev = curr;
        }
        return result;
    }
};
