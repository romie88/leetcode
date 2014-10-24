//Integer to Roman
//
//Given an integer, convert it to a roman numeral.
//
//Input is guaranteed to be within the range from 1 to 3999.

#include <string>

//Check out
//http://en.wikipedia.org/wiki/Roman_numerals
class Solution {
public:
	std::string intToRoman( int num ) {
		
		//I 1
		//V 5
		//X 10
		//L 50
		//C 100
		//D 500
		//M 1000

		std::string roman;
		
		//M
		int num_of_thousand = num / 1000;
		roman.append( num_of_thousand, 'M' );

		//D, C
		int num_of_hundred = num % 1000 / 100;
		if ( num_of_hundred == 9 )
			roman.append( "CM" );//CM = 900
		else if ( num_of_hundred == 4 )
			roman.append( "CD" );//CD = 400
		else if ( num_of_hundred >= 5 )
			roman.append( "D" ).append( num_of_hundred - 5, 'C' );
		else
			roman.append( num_of_hundred, 'C' );

		//L, X
		int num_of_ten = num % 100 / 10;
		if ( num_of_ten == 9 )
			roman.append( "XC" );//XC = 90
		else if ( num_of_ten == 4 )
			roman.append( "XL" );//XL = 40
		else if ( num_of_ten >= 5 )
			roman.append( "L" ).append( num_of_ten - 5, 'X' );
		else
			roman.append( num_of_ten, 'X' );

		//V, I
		int num_of_one = num % 10;
		if ( num_of_one == 9 )
			roman.append( "IX" );//IX = 9
		else if ( num_of_one == 4 )
			roman.append( "IV" );//IV = 4
		else if ( num_of_one >= 5 )
			roman.append( "V" ).append( num_of_one - 5, 'I' );
		else
			roman.append( num_of_one, 'I' );

		return roman;
	}
};
