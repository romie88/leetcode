//Multiply Strings
//
//Given two numbers represented as strings,
//return multiplication of the numbers as a string.
//
//Note: The numbers can be arbitrarily large and are non-negative.

#include <string>

class Solution {
public:
	std::string multiply( std::string num1, std::string num2 ) {
		
		std::string result;
		
		int pos1 = 0;
		for ( int i1 = num1.size() - 1; i1 >= 0; --i1 )
		{
			int carry = 0;
			int d1 = num1[ i1 ] - '0';
			pos1 = num1.size() - 1 - i1;
			int pos2 = 0;
			for ( int i2 = num2.size() - 1; i2 >= 0; --i2 )
			{
				int d2 = num2[ i2 ] - '0';
				pos2 = num2.size() - 1 - i2;
				int prod = d1 * d2 + carry;
				if ( pos1 + pos2 >= result.size() )
				{
					//if prod == 0, like 9335 * 0, the code should not produce
					//0000 as the result
					if ( prod )
					{
						//to handle 6 * 501 need to append extra zero
						if ( pos1 + pos2 > result.size() )
							result.append( pos1 + pos2 - result.size(), '0' );
						result.append( 1, prod % 10 + '0' );
					}
					else if ( result.size() == 0 )//but still want one zero
					{
						result.append( 1, prod % 10 + '0' );
					}
					carry = prod / 10;
				}
				else
				{
					int temp = ( result[ pos1 + pos2 ] - '0' ) + prod;
					result[ pos1 + pos2 ] = temp % 10 + '0';
					carry = temp / 10;
				}
			}
			//process the remaining carry
			for ( int i = 1; carry; ++i )
			{
				if ( pos1 + pos2 + i >= result.size() )
				{
					result.append( 1, carry % 10 + '0' );
					carry /= 10;
				}
				else
				{
					int temp = ( result[ pos1 + pos2 + i ] - '0' ) + carry;
					result[ pos1 + pos2 + i ] = temp % 10 + '0';
					carry = temp / 10;
				}
			}
		}

		for ( int i = 0, j = result.size() - 1; i < j; ++i, --j )
		{
			char temp = result[ j ];
			result[ j ] = result[ i ];
			result[ i ] = temp;
		}
		return result;

    }
};
