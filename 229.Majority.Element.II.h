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
        return majority_element_2( nums );
    }
private:
    /**
     * Moore voting implementation 1
     */
    std::vector< int > majority_element_1( const std::vector< int > & nums ) {
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
        
        verify_result( nums, n1, n2, result );
        return result;
    }
    
    /**
     * Moore voting implementation 2
     */
    std::vector< int > majority_element_2( const std::vector< int > & nums ) {
        std::vector< int > result;
        int n1 = 0, n2 = 0;
        int c1 = 0, c2 = 0;
        for ( int i = 0; i < nums.size(); ++i ) {
            int n3 = nums[ i ];
            if ( c1 > 0 && c2 > 0 ) {
                if ( n3 != n1 && n3 != n2 ) {
                    --c1;
                    --c2;
                } else if ( n3 == n1 ) {
                    ++c1;
                } else {
                    ++c2;
                }
            } else if ( c1 > 0 ) {
                if ( n3 == n1 ) {
                    ++c1;
                } else {
                    n2 = n3;
                    ++c2;
                }
            } else if ( c2 > 0 ) {
                if ( n3 == n2 ) {
                    ++c2;
                } else {
                    n1 = n3;
                    ++c1;
                }
            } else {
                n1 = n3;
                ++c1;
            }
        }
        
        verify_result( nums, n1, n2, result );
        return result;
    }
    
    void verify_result( const std::vector< int > & nums,
                        const int candidate1,
                        const int candidate2,
                        std::vector< int > & result ) {
        int c1 = 0;
        int c2 = 0;
        for ( int i = 0; i < nums.size(); ++i ) {
            if ( nums[ i ] == candidate1 )
                ++c1;
            else if ( nums[ i ] == candidate2 )
                ++c2;
        }
        
        if ( c1 > nums.size() / 3 )
            result.push_back( candidate1 );
        if ( c2 > nums.size() / 3 )
            result.push_back( candidate2 );
    }
};
