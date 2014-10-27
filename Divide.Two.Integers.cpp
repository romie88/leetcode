//Divide Two Integers
//
//Divide two integers without using multiplication, division and mod operator.

class Solution {
public:
    int divide(int dividend, int divisor) {
        long long a = dividend;
		long long b = divisor;
		
		a = a < 0 ? -a : a;
		b = b < 0 ? -b : b;

		long long c = 1;
		while ( a > b )
		{
			b <<= 1;
			c <<= 1;
		}
		if ( c > 1 )
		{
			b >>= 1;//make a > b again but still a <= (b << 1)
			c >>= 1;
		}

		long result = 0;
		while ( a >= b )
		{
			a -= b;
			result += c;
			while ( c > 1 && a <= b )
			{
				b >>= 1;
				c >>= 1;
			}
		}
		
		if ( dividend < 0 && divisor > 0
		  || dividend > 0 && divisor < 0 )
			result = -result;

		return result;
    }
};
