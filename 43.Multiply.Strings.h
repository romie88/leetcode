/**
 * Algorithms 43 Multiply Strings                                        Medium
 * 
 * Given two numbers represented as strings, return multiplication of the
 * numbers as a string.
 * 
 * Note: The numbers can be arbitrarily large and are non-negative.
 * 
 * Tags: Math, String
 * Similar Problems: (M) Add Two Numbers, (E) Plus One, (E) Add Binary
 */

#include <string>
#include <algorithm>

class Solution {
public:
    std::string multiply( const std::string & num1, const std::string & num2 ) {
        if ( num1.empty() || num2.empty() )
            throw std::invalid_argument( "empty num1 or num2" );
        
        const int n1 = num1.length();
        const int n2 = num2.length();
        std::string result( n1 + n2, '0' );
        int c = 0;
        for ( int i = n2 - 1; i >= 0; --i ) {
            c = 0;
            for ( int j = n1 - 1; j >= 0; --j ) {
                int k = ( num2[ i ] - '0' ) * ( num1[ j ] - '0' ) + c;
                int index = n2 - 1 - i + n1 - 1 - j;
                k += ( result[ index ] - '0' );
                result[ index ] = k % 10 + '0';
                c = k / 10;
            }
            if ( c > 0 )
                result[ n2 - 1 - i + n1 ] += c;
        }
        //discard all the zeros
        int i2 = n2 + n1 - 1;
        while ( i2 > 0 && result[ i2 ] == '0' ) --i2;
        result.resize( i2 + 1 );
        //reverse result
        int i1 = 0;
        while ( i1 < i2 ) std::swap( result[ i1++ ], result[ i2-- ] );
        return result;
    }
};
