/**
 * Algorithms 69 Sqrt(x)                                                 Medium
 * 
 * Implement int sqrt(int x).
 * 
 * Compute and return the square root of x.
 * 
 * Tags: Math, Binary Search
 * Similar Problems: (M) Pow(x,n)
 */

#include <stdexcept>
#include <limits>

class Solution {
public:
    int mySqrt( int x ) {
        return my_sqrt_newton( x );
    }
private:
    /**
     * O( log x ) runtime
     *
     * note we have to handle the overflow of M * M
     * in my earlier code I check if ( M != 0 && M > x / M )
     */
    int my_sqrt_binary_search( int x ) {
        if ( x < 0 ) throw std::invalid_argument( "sqrt() input is negative" );
        int L = 0, R = x;
        while ( L <= R ) {
            int M = ( L + R ) / 2;
            if ( M > std::numeric_limits< int >::max() / M ) {
                R = M - 1;
                continue;
            }
            int xx = M * M;
            if ( xx == x )
                return M;
            else if ( xx < x )
                L = M + 1;
            else
                R = M - 1;
        }
        return R;
    }
    /**
     * Newton's method
     * 
     * http://www.2cto.com/kf/201206/137256.html
     * http://en.wikipedia.org/wiki/Newton's_method#Square_root_of_a_number
     * 
     * In numerical analysis we try to find the root of f(x) = 0.
     * y = f( x_0 ) + f'( x_0 ) * ( x - x_0 )
     * let y = 0 then x = x_0 - f( x_0 ) / f'( x_0 ).
     * 
     * Given a C try to find x^2 = C. Let f( x ) = x^2 - C.
     * x = x_0 - ( ( x_0 )^2 - C ) / ( 2 * x_0 )
     */
    int my_sqrt_newton( int x ) {
        if ( x < 0 ) throw std::invalid_argument( "sqrt() input is negative" );
        if ( x == 0 ) return 0;
        const double eps = 1.0e-6;
        double d  = x;
        double d2 = d;
        do {
            d2 = d;
            d  = ( d + x / d ) / 2.0;
        } while ( std::fabs( d - d2 ) > eps );
        
        return static_cast< int >( d );
    }
};
