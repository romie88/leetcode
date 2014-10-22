//Sqrt(x)
//
//Implement int sqrt(int x).
//
//Compute and return the square root of x.

class Solution {
public:
    int sqrt( int x ) {
        if ( x < 0 )
			return 0;
		
		//Note: for any integer x >= 0, ( x/2 + 1 )^2 > x
		//a tiny optimization can be high = x / 2 + 1;
		int low = 0;
		int high = x;
		int mid = ( low + high ) / 2;
		while ( 1 )
		{
			//check mid > x / mid to handle the potential overflow
			//by mid * mid > INT_MAX
			if ( ( mid != 0 && mid > x / mid )
		      || ( mid == 0 && mid * mid > x ) )
			{
				high = mid - 1;
			}
			else if ( ( mid != 0 && mid == x / mid && x % mid == 0 )
				   || ( mid == 0 && mid * mid == x ) )
			{
				break;
			}
			else
			{
				if ( ( mid + 1 ) > x / ( mid + 1 ) )
					break;
				else
					low = mid + 1;
			}
			mid = ( low + high ) / 2;
		}

		return mid;
    }
};
