/**
 * Algorithms 6 ZigZag Conversion                                          Easy
 * 
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number
 * of rows like this: (you may want to display this pattern in a fixed font for
 * better legibility)
 * 
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * 
 * And then read line by line: "PAHNAPLSIIGYIR"
 * 
 * Write the code that will take a string and make this conversion given a
 * number of rows:
 * 
 * string convert(string text, int nRows);
 * convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
 * 
 * Tags: String
 */

#include <string>

class Solution {
public:
    std::string convert( const std::string & s, const int numRows ) {
        return convert_impl( s, numRows );
    }
private:
    std::string convert_impl( const std::string & s, const int numRows ) {
        if ( numRows <= 0 ) throw std::invalid_argument( "numRows <= 0" );
        
        std::string t;
        const int n = s.length();
        int step = numRows == 1 ? 1 : 2 * ( numRows - 1 );
        for ( int j = 0; j < n; j += step )
            t += s[ j ];
        for ( int i = 1; i < numRows - 1; ++i ) {
            for ( int j = i; j < n; j += step ) {
                t += s[ j ];
                int j2 =  j + ( numRows - ( i + 1 ) ) * 2;
                if ( j2 < n )
                    t += s[ j2 ];
            }
        }
        if ( numRows > 1 ) {
            for ( int j = numRows - 1; j < n; j += step )
                t += s[ j ];
        }
        
        return t;
    }
};
