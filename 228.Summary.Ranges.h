/**
 * Algorithms 228 Summary Ranges                                           Easy
 * 
 * Given a sorted integer array without duplicates, return the summary of its
 * ranges.
 * 
 * For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].
 * 
 * Credits:
 * 
 * Special thanks to @jianchao.li.fighter for adding this problem and creating
 * all test cases.
 * 
 * Tags: Array
 */

#include <string>
#include <vector>

class Solution {
public:
    std::vector< std::string > summaryRanges( const std::vector< int > & nums ) {
        std::vector< std::string > result;
        if ( nums.empty() ) return result;
        
        int start = nums[ 0 ];
        int end   = nums[ 0 ];
        for ( int i = 0; i < nums.size() - 1; ++i ) {
            if ( nums[ i ] + 1 == nums[ i + 1 ] ) {
                end = nums[ i + 1 ];
            } else {
                result.push_back( get_range( start, end ) );
                start = nums[ i + 1 ];
                end   = nums[ i + 1 ];
            }
        }
        result.push_back( get_range( start, end ) );
    }
private:
    std::string get_range( int start, int end ) {
        std::string s = std::to_string( start );
        if ( start != end ) {
            s += "->";
            s += std::to_string( end );
        }
        return s;
    }
};

