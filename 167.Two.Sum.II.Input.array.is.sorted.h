/**
 * Algorithms 167 Two Sum II - Input array is sorted                     Medium
 * 
 * Given an array of integers that is already sorted in ascending order, find
 * two numbers such that they add up to a specific target number.
 * 
 * The function twoSum should return indices of the two numbers such that they
 * add up to the target, where index1 must be less than index2. Please note
 * that your returned answers (both index1 and index2) are not zero-based.
 * 
 * You may assume that each input would have exactly one solution.
 * 
 * Input: numbers={2, 7, 11, 15}, target=9
 * Output: index1=1, index2=2
 * 
 * Tags: Array, Two Pointers, Binary Search
 */

#include <vector>

class Solution {
public:
    std::vector< int > twoSum(
            const std::vector< int > & numbers,
            const int                  target ) {
        return two_sum_two_pointers( numbers, target );
    }
private:
    /**
     * We can still use the same method from 1 Two Sum
     * O( n ) runtime, O( n ) space - Hash table
     */
    
    /**
     * O( n log n ) runtime, O( 1 ) space - Binary search 
     */
    
    /**
     * O( n ) runtime, O( 1 ) space - Two pointers
     */
    std::vector< int > two_sum_two_pointers(
            const std::vector< int > & numbers,
            const int                  target ) {
        std::vector< int > result;
        int i = 0, j = numbers.size() - 1;
        while ( i < j ) {
            int sum = numbers[ i ] + numbers[ j ];
            if ( sum < target )
                ++i;
            else if ( sum > target )
                --j;
            else {
                result.push_back( i + 1 );
                result.push_back( j + 1 );
                break;
            }
        }
        return result;
    }
};
