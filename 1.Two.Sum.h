/**
 * Algorithms 1 Two Sum                                                  Medium
 * 
 * Given an array of integers, find two numbers such that they add up to a
 * specific target number.
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
 * Tags: Array, Hash Table
 */

#include <vector>
#include <unordered_map>
#include <utility>

class Solution {
public:
    std::vector< int > twoSum(
            const std::vector< int > & nums,
            const int                  target ) {
        return two_sum_by_hash_table( nums, target );
    }
private:
    /**
     * O( n^2 ) runtime, O( 1 ) space - Brute force
     */
    
    /**
     * O( n ) runtime, O( n ) space - Hash table
     */
    std::vector< int > two_sum_by_hash_table(
            const std::vector< int > & nums,
            const int                  target ) {
        std::vector< int > result;
        std::unordered_map< int, int > hash_table;
        for ( int i = 0; i < nums.size(); ++i ) {
            std::unordered_map< int, int >::iterator
                it = hash_table.find( target - nums[ i ] );
            if ( it != hash_table.end() ) {
                result.push_back( it->second + 1 );
                result.push_back( i + 1 );
                break;
            } else {
                hash_table.insert( std::make_pair( nums[ i ], i  ) );
            }
        }
        return result;
    }
};

/**
 * Solution
 * 
 * O(n^2) runtime, O(1) space – Brute force:
 * 
 * The brute force approach is simple. Loop through each element x and find if
 * there is another value that equals to target – x. As finding another value
 * requires looping through the rest of array, its runtime complexity is O(n^2).
 * 
 * O(n) runtime, O(n) space – Hash table:
 * 
 * We could reduce the runtime complexity of looking up a value to O(1) using
 * a hash map that maps a value to its index.
 */
