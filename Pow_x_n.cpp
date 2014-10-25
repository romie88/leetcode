//Pow(x, n)
//
//Implement pow(x, n).

class Solution {
public:
    double pow( double x, int n ) {

		if ( n < 0 )
		{
			n = -n;//overflow if n == INT_MIN
			x = 1.0 / x;
		}

        if ( n == 0 )
		{
			return 1.0;
		}
		else if ( n == 1 )
		{
			return x;
		}
		else if ( n % 2 == 0 )
		{
			return pow( x * x, n / 2 );
		}
		else
		{
			return pow( x * x, n / 2 ) * x;
		}
    }
};
