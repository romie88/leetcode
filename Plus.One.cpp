//Plus One
//
//Given a non-negative number represented as an array of digits, plus one to the number.
//
//The digits are stored such that the most significant digit is at the head of the list.

#include <vecctor>

class Solution {
public:
	std::vector< int > plusOne( std::vector< int > & digits ) {
        
		if ( digits.size() == 0 )
			return digits;
		
		std::vector< int > result( digits );
		++result[ result.size() - 1 ];
		int carry = 0;
		for ( int i = result.size() - 1; i >= 0; --i )
		{
			result[ i ] += carry;
			carry = result[ i ] / 10;
			result[ i ] %= 10;
			if ( carry == 0 )
				break;
		}
		
		if ( carry )
		{
			result.insert( result.begin(), carry );
		}

		return result;
    }
};
