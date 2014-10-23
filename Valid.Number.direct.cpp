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
		
		bool is_valid = true;
		
		//skip spaces
		while ( std::isspace( *s ) ) ++s;
		
		//sign
		if ( *s == '+' || *s == '-' ) ++s;
		
		bool has_exponent   = false;
		bool has_dot        = false;
		bool has_space      = false;
		bool first_part     = false;
		bool second_part    = false;
		bool trailing_space = false;
		while ( *s != '\0' )
		{
			if ( *s == '.' )
			{
				if ( has_dot || has_exponent )
				{
					is_valid = false;
					break;
				}
				else
				{
					has_dot = true;
				}
			}
			else if ( *s == 'e' || *s == 'E' )
			{
				if ( has_exponent || ! first_part )
				{
					is_valid = false;
					break;
				}
				else
				{
					has_exponent = true;
				}
			}
			else if ( std::isdigit( *s ) )
			{
				if ( ! has_exponent )
					first_part = true;
				else
					second_part = true;
			}
			else if ( *s == '+' | *s == '-' )
			{
				if ( ! has_exponent || ( *( s - 1 ) != 'e' && *( s - 1 ) != 'E' ) )
				{
					is_valid = false;
					break;
				}
			}
			else if ( std::isspace( *s ) )
			{
				trailing_space = true;
				break;
			}
			else
			{
				is_valid = false;
				break;
			}

			++s;
		}
	
		if ( ! is_valid )
		{
			return false;
		}
		else if ( trailing_space )
		{
			while ( std::isspace( *s ) ) ++s;
			if ( *s != '\0' )
				return false;
			
			if ( ! first_part )
				return false;
			else if ( has_exponent && ! second_part )
				return false;
			else
				return true;
		}
		else
		{
			if ( ! first_part )
				return false;
			else if ( has_exponent && ! second_part )
				return false;
			else
				return true;
		}
	}
};
