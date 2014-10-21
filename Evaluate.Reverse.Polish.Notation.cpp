//Evaluate Reverse Polish Notation
//
//Evaluate the value of an arithmetic expression in Reverse Polish Notation.
//
//Valid operators are +, -, *, /. Each operand may be an integer or another expression.
//
//Some examples:
//  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
//  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

#include <vector>
#include <string>
#include <stack>
#include <sstream>

class Solution {
public:
    int evalRPN( std::vector< std::string > & tokens ) {
		std::stack< int > s;
		for ( const auto & token : tokens )
		{
			int num;
			if ( isInt( token, num ) )
			{
				s.push( num );
			}
			else
			{
				int op1, op2;
				if ( token == "+" )
				{
					getTwoOps( s, op2, op1 );
					s.push( op1 + op2 );
				}
				else if ( token == "-" )
				{
					getTwoOps( s, op2, op1 );
					s.push( op1 - op2 );
				}
				else if ( token == "*" )
				{
					getTwoOps( s, op2, op1 );
					s.push( op1 * op2 );
				}
				else if ( token == "/" )
				{
					getTwoOps( s, op2, op1 );
					s.push( op1 / op2 );
				}
			}
		}
		return s.top();
    }
private:
	void getTwoOps( std::stack< int > & s, int & op1, int & op2 )
	{
		op1 = s.top();
		s.pop();
		op2 = s.top();
		s.pop();
	}

	bool isInt( const std::string & s, int & i )
	{
		std::istringstream iss( s );
		return iss >> i;
	}
};
