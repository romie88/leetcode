/**
 * Algorithms 50 Pow(x,n)                                                Medium
 * 
 * Implement pow(x, n).
 * 
 * Tags: Math, Binary Search
 * Similar Problems: (M) Sqrt(x)
 */

#include <stdexcept>
#include <limits>

class Solution {
public:
    double myPow( double x, int n ) {
#if 0
        if ( x == 0.0 && n == 0 )
            throw std::invalid_argument( "zero pows to zero" );
#endif
        //standard library function pow( 0.0, 0 ) returns 1.0
        return my_pow_impl_4( x, n );
    }
private:
    /**
     * All the solution here is O( log n ) runtime
     * O( log n ) space for recursive solution
     * O( 1 ) space for iterative solution
     */
    double my_pow_impl_1( double x, int n ) {
        double tmp = my_pow_impl_1_helper( x, n < 0 ? -n : n );
        return n < 0 ? ( 1.0 / tmp ) : tmp;
    }
    double my_pow_impl_1_helper( double x, int n ) {
        if ( n == 0 ) return 1.0;
        if ( n == 1 ) return x;
        double tmp = my_pow_impl_1_helper( x, n / 2 );
        return tmp * tmp * ( n % 2 ? x : 1.0 );
    }
    double my_pow_impl_2( double x, int n ) {

		if ( n < 0 ) {
			n = -n;//overflow if n == INT_MIN
			x = 1.0 / x;
		}
        
        if ( n == 0 ) {
			return 1.0;
		} else if ( n == 1 ) {
			return x;
		} else if ( n % 2 == 0 ) {
			return pow( x * x, n / 2 );
		} else {
			return pow( x * x, n / 2 ) * x;
		}
    }
    /**
     * Consider an exmaple 3^10.
     * 10 in binary is 1010 and 3^10 with expansion on the binary 1010
     * 3^10 = 3^( 2^3 * 1 ) * 3^( 2^2 * 0 ) * 3^( 2^1 * 1 ) + 3^( 2^0 * 0 )
     * Now how to calculate 3^(2^i) where i >= 0?
     * start with 3^1 = 3^( 2^0 * 1 )
     *            3^2 = 3^( 2^1 * 1 ) = 3^1 * 3^1
     *            3^4 = 3^( 2^2 * 1 ) = 3^2 * 3^2
     * res = 1
     * res = res^2 * 3^1 = 3^(1)b
     * res = res^2 * 3^0 = 3^(10)b
     * res = res^2 * 3^1 = 3^(101)b
     * res = res^2 * 3^0 = 3^(1010)b
     */
    double my_pow_impl_3( double x, int n ) {
        bool is_negative = n < 0;
        if ( is_negative ) n = -n;
        double result = 1.0;
        for ( int i = 31; i >= 0; --i ) {
            result *= result;
            if ( n & ( 1 << i ) )
                result *= x;
        }
        if ( is_negative ) result = 1.0 / result;
        return result;
    }
    /**
     * Yet another implementation similar to the above one.
     */
    double my_pow_impl_4( double x, int n ) {
        if ( n == 0 ) return 1.0;//even if x == 0.0 we still return 1.0
                                 //to be consistent with the standard library
                                 //function pow()
        double result = 1.0;
        if ( n < 0 ) {
            if ( x >= 1.0 / std::numeric_limits< double >::max()
              || x <= 1.0 / std::numeric_limits< double >::min() )
                x = 1.0 / x;
            else
                return std::numeric_limits< double >::max();
            if ( n == std::numeric_limits< int >::min() ) {
                result *= x;
                ++n;
            }
        }
        n = n < 0 ? -n : n;
        bool is_negative = n % 2 && x < 0;
        x = x < 0 ? -x : x;
        while ( n > 0 ) {
            if ( n & 1 ) {
                if ( result > std::numeric_limits< double >::max() / x )
                    return std::numeric_limits< double >::max();
                result *= x;
            }
            x *= x;
            n >>= 1;
        }
        return is_negative ? -result : result;             
    }
};
