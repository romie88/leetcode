//168 Excel Sheet Column Title [ Easy ]
//
//Given a positive integer, return its corresponding column title as appear in
//an Excel sheet.
//
//For example:
//
//    1 -> A
//    2 -> B
//    3 -> C
//    ...
//    26 -> Z
//    27 -> AA
//    28 -> AB 
//
//Credits:
//Special thanks to @ifanchu for adding this problem and creating all test
//cases.
//
//Tags: Math

#include <string>
#include <algorithm>

class Solution {
public:
    std::string convertToTitle( int n ) {
        if ( n <= 0 )
            throw std::invalid_argument(
                    "Nonpositive Excel Sheet Column Number Found" );

        std::string s;
        while ( n ) {
            int m = n % 26;
            if ( m > 0 )
                s.append( 1, ( 'A' + m - 1 ) );
            else {
                s.append( 1, 'Z' );
                n -= 26;
            }
            n /= 26;
        }

        std::reverse( s.begin(), s.end() );

        return s;
    }
};
