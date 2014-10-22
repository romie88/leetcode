//Sqrt(x)
//
//Implement int sqrt(int x).
//
//Compute and return the square root of x.

//YOU MUST CHECKOUT THIS:
//http://www.2cto.com/kf/201206/137256.html
//http://en.wikipedia.org/wiki/Newton's_method#Square_root_of_a_number

#include <cmath>

class Solution {
public:
    int sqrt( int x ) {

        if ( x <= 0 )
			return 0;
		
		const double eps = 1.0e-6;
		double d = x;
		double d2 = d;
		do {
			d2 = d;
			d = ( d + x / d ) / 2.0;
		} while ( std::fabs( d - d2 ) > eps );
		
		//round downwards
		int result = static_cast< int >( d );
		if ( result * result > x )
			--result;
		
		return result;
    }
};
