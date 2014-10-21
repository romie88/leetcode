//Valid Number
//
//Validate if a given string is numeric.
//
//Some examples:
//"0" => true
//" 0.1 " => true
//"abc" => false
//"1 a" => false
//"2e10" => true
//Note: It is intended for the problem statement to be ambiguous.
//You should gather all requirements up front before implementing one.

#include <cctype>

class Solution {
public:
    bool isNumber( const char * s ) {
		
		enum InputType {
			INVALID,   //0
			SPACE,     //1
			SIGN,      //2
			DIGIT,     //3
			DOT,       //4
			EXPONENT,  //5
			NUM_INPUTS //6
		};
		
		//transition_table: state by input
		int transition_table[][ NUM_INPUTS ] = {
			{ -1,  0,  3,  1,  2, -1 },//0
			{ -1,  8, -1,  1,  4,  5 },//1
			{ -1, -1, -1,  4, -1, -1 },//2
			{ -1, -1, -1,  1,  2, -1 },//3
			{ -1,  8, -1,  4, -1,  5 },//4
			{ -1, -1,  6,  7, -1, -1 },//5
			{ -1, -1, -1,  7, -1, -1 },//6
			{ -1,  8, -1,  7, -1, -1 },//7
			{ -1,  8, -1, -1, -1, -1 },//8
		};
		
		int state = 0;
		while ( *s != '\0' )
		{
			InputType input_type = INVALID;
			if ( std::isspace( *s ) )
			{
				input_type = SPACE;
			}
			else if ( *s == '+' || *s == '-' )
			{
				input_type = SIGN;
			}
			else if ( std::isdigit( *s ) )
			{
				input_type = DIGIT;
			}
			else if ( *s == '.' )
			{
				input_type = DOT;
			}
			else if ( *s == 'e' || *s == 'E' )
			{
				input_type = EXPONENT;
			}
			else
			{
				input_type = INVALID;
			}

			state = transition_table[ state ][ input_type ];

			if ( state == -1 )
			{
				return false;
			}

			++s;
		}

		return state == 1 || state == 4 || state == 7 || state == 8;
	}
};
