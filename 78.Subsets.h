/**
 * Algorithms 78 Subsets                                                 Medium
 * 
 * Given a set of distinct integers, nums, return all possible subsets.
 * 
 * Note:
 * Elements in a subset must be in non-descending order.
 * The solution set must not contain duplicate subsets.
 * For example,
 * If nums = [1,2,3], a solution is:
 * 
 * [
 *   [3],
 *   [1],
 *   [2],
 *   [1,2,3],
 *   [1,3],
 *   [2,3],
 *   [1,2],
 *   []
 * ]
 * 
 * Tags: Array, Backtracking, Bit Manipulation
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector< std::vector< int > > subsets( std::vector< int > & nums ) {
        std::sort( nums.begin(), nums.end() );
        std::vector< std::vector< int > > results;
        subset_bit( nums, results );
        return results;
    }
private:
    /**
     * Recursive and backtracking implementation
     */
    void subset_recursive(
            const std::vector< int >          & nums,
            const int                           start,
            std::vector< int >                & one_comb,
            std::vector< std::vector< int > > & results ) {
        for ( int i = start; i < nums.size(); ++i ) {
            one_comb.push_back( nums[ i ] );
            results.push_back( one_comb );
            //this check will save one recursive call
            if ( i < nums.size() - 1 )
                subset_recursive( nums, i + 1, one_comb, results );
            one_comb.pop_back();
        }
    }
    void subset_recursive_wrapper(
            const std::vector< int >          & nums,
            std::vector< std::vector< int > > & results ) {
        std::vector< int > one_comb;
        subset_recursive( nums, 0, one_comb, results );
        if ( nums.size() > 0 )
            results.push_back( one_comb );
    }
    /**
     * Bit Manipulation base solution
     */
    void subset_bit(
            const std::vector< int >          & nums,
            std::vector< std::vector< int > > & results ) {
        std::vector< int > one_comb;
        std::vector< bool > flag( nums.size(), false );
        flag.back() = true;
        while ( true ) {
            for ( int i = 0; i < flag.size(); ++i ) {
                if ( flag[ i ] ) {
                    one_comb.push_back( nums[ i ] );
                }
            }
            
            results.push_back( one_comb );
            one_comb.clear();
            int i = flag.size() - 1;
            for ( i = flag.size() - 1; i >= 0; --i ) {
                if ( ! flag[ i ] ) {
                    flag[ i ] = true;
                    break;
                } else {
                    flag[ i ] = false;
                }
            }
            
            if ( i < 0 ) break;
        }
        results.push_back( one_comb );
    }
};
