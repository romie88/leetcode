//String to Integer (atoi)
//
//Implement atoi to convert a string to an integer.
//
//Hint: Carefully consider all possible input cases.
//If you want a challenge, please do not see below and
//ask yourself what are the possible input cases.
//
//Notes: It is intended for this problem to be specified
//vaguely (ie, no given input specs). You are responsible
//to gather all the input requirements up front.
//
//Requirements for atoi:
//
//The function first discards as many whitespace characters
//as necessary until the first non-whitespace character is found.
//Then, starting from this character, takes an optional initial
//plus or minus sign followed by as many numerical digits as possible,
//and interprets them as a numerical value.
//
//The string can contain additional characters after those that form
//the integral number, which are ignored and have no effect on the
//behavior of this function.
//
//If the first sequence of non-whitespace characters in str is not
//a valid integral number, or if no such sequence exists because either
//str is empty or it contains only whitespace characters, no conversion
//is performed.
//
//If no valid conversion could be performed, a zero value is returned.
//If the correct value is out of the range of representable values,
//INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.

#include <cctype>
#include <limits>

class Solution {
public:
    int atoi( const char * str ) {
        
		const char * p = str;
		//skip spaces
		while ( std::isspace( *p ) )
			++p;
		
		//check sign
		int sign = 1;
		if ( *p == '+' )
		{
			++p;
			sign = 1;
		}
		else if ( *p == '-' )
		{
			++p;
			sign = -1;
		}
		
		int result = 0;
		while ( std::isdigit( *p ) )
		{
			int digit = *p - '0';

			if ( sign == 1 )
			{
				if ( result <= ( ( std::numeric_limits< int >::max() - sign * digit ) / 10 ) )
				{
					result = result * 10 + sign * digit;	
				}
				else
				{
					result = std::numeric_limits< int >::max();
					break;
				}
			}
			else
			{
				if ( result >= ( ( std::numeric_limits< int >::min() - sign * digit ) / 10 ) )
				{
					result = result * 10 + sign * digit;
				}
				else
				{
					result = std::numeric_limits< int >::min();
					break;
				}
			}
			
			++p;
		}
		
		return result;
    }
};
