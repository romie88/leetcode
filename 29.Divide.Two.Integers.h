/**
 * Algorithms 29 Divide Two Integers                                     Medium
 * 
 * Divide two integers without using multiplication, division and mod operator.
 * 
 * If it is overflow, return MAX_INT.
 * 
 * Tags: Math, Binary Search
 */

#include <stdexcept>
#include <limits>

class Solution {
public:
    int divide( const int dividend, const int divisor ) {
        if ( divisor == 0 ) throw std::invalid_argument( "divisor is zero" );
        //hanlde the only overflow case
        if ( dividend == std::numeric_limits< int >::min() && divisor == -1 )
            return std::numeric_limits< int >::max();
        
        long long a = dividend;
		long long b = divisor;
		a = a < 0 ? -a : a;
		b = b < 0 ? -b : b;
        
        int i = 0;
        while ( a >= ( b << i ) ) ++i;
        if ( i > 0 ) --i;
        
        int result = 0;
        while ( a >= b ) {
            if ( a >= ( b << i ) ) {
                a -= ( b << i );
                result += ( 1 << i );
            }
            --i;
        }
        
		if ( ( dividend < 0 && divisor > 0 )
		  || ( dividend > 0 && divisor < 0 ) )
			result = -result;
        
		return result;
    }
};
