/**
 * 229 Majority Element II                                               Medium
 * 
 * Given an integer array of size n, find all elements that appear more than
 * [ n/3 ] (floor) times. The algorithm should run in linear time and in O(1)
 * space.
 * 
 * Show Hint
 * 
 * 1. How many majority elements could it possibly have?
 * 2. Do you have a better hint? Suggest it!
 *  
 * Tags: 
 */

#include <vector>

class Solution {
public:
    std::vector< int > majorityElement( const std::vector< int > & nums ) {
        std::vector< int > result;
        if ( nums.empty() ) return result;
        else if ( nums.size() == 1 ) {
            result.push_back( nums[ 0 ] );
            return result;
        }
        
        int n1 = nums[ 0 ];
        int c1 = 1;
        int i = 1;
        for ( i = 1; i < nums.size() && nums[ i ] == n1; ++i )
            ++c1;
        if ( i == nums.size() ) {
            result.push_back( nums[ 0 ] );
            return result;
        }
        int n2 = nums[ i ];
        int c2 = 1;
        for ( ++i; i < nums.size(); ++i ) {
            if ( nums[ i ] == n1 )
                ++c1;
            else if ( nums[ i ] == n2 )
                ++c2;
            else {
                --c1;
                --c2;
                if ( c1 < 0 ) {
                    n1 = nums[ i ];
                    c1 = 0;
                } else if ( c2 < 0 ) {
                    n2 = nums[ i ];
                    c2 = 0;
                }
            }
        }
        
        c1 = 0;
        c2 = 0;
        for ( i = 0; i < nums.size(); ++i ) {
            if ( nums[ i ] == n1 )
                ++c1;
            else if ( nums[ i ] == n2 )
                ++c2;
        }
        
        if ( c1 > nums.size() / 3 )
            result.push_back( n1 );
        if ( c2 > nums.size() / 3 )
            result.push_back( n2 );
        
        return result;
    }
};
