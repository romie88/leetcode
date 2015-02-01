//171 Excel Sheet Column Number [ Easy ]
//
//Related to question 168 Excel Sheet Column Title
//
//Given a column title as appear in an Excel sheet, return its corresponding
//column number.
//
//For example:
//
//    A -> 1
//    B -> 2
//    C -> 3
//    ...
//    Z -> 26
//    AA -> 27
//    AB -> 28 
//Credits:
//Special thanks to @ts for adding this problem and creating all test cases.
//
//Tags: Math

#include <string>
#include <cctype>

class Solution {
public:
    int titleToNumber( const std::string & s ) {
        if ( s.empty() )
            throw std::invalid_argument( "empty title" );
        
        int result = 0;
        int factor = 1;
        for ( const auto c : s ) {
            if ( ! std::isalpha( c ) )
                throw std::invalid_argument( "title character is not in [A-Z]" );

            //assume ASCII
            result = result * 26 + ( std::toupper( c ) - 'A' + 1 );
        }

        return result;
    }
};
