//Add Binary
//
//Given two binary strings, return their sum (also a binary string).
//
//For example,
//a = "11"
//b = "1"
//Return "100".

//Tags: Math, String

#include <string>

class Solution {
public:
	std::string addBinary( std::string a, std::string b ) {
        
		std::string result;
		int carry = 0;
		for ( int i1 = a.length() - 1, i2 = b.length() - 1;
			  i1 >= 0 || i2 >= 0; )
		{
			int sum = carry;
			if ( i1 >= 0 )
			{
				sum += a[ i1 ] == '1' ? 1 : 0;
				--i1;
			}
			if ( i2 >= 0 )
			{
				sum += b[ i2 ] == '1' ? 1 : 0;
				--i2;
			}
			carry = sum / 2;
			result.append( 1, sum % 2 ? '1' : '0' );
		}
		if ( carry )
		{
			result.append( 1, '1' );
		}

		for ( int i = 0, j = result.length() - 1;
			  i < j; ++i, --j )
		{
			char temp = result[ i ];
			result[ i ] = result[ j ];
			result[ j ] = temp;
		}

		return result;
    }
};
