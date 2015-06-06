/**
 * Algorithms 90 Subsets II                                              Medium
 * 
 * Given a collection of integers that might contain duplicates, nums, return
 * all possible subsets.
 * 
 * Note:
 * 
 * * Elements in a subset must be in non-descending order.
 * * The solution set must not contain duplicate subsets.
 * 
 * For example,
 * 
 * If nums = [1,2,2], a solution is:
 * 
 * [
 *   [2],
 *   [1],
 *   [1,2,2],
 *   [2,2],
 *   [1,2],
 *   []
 * ]
 * 
 * Tags: Array, Backtracking
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector< std::vector< int > >
            subsetsWithDup( std::vector< int > & nums ) {
        std::sort( nums.begin(), nums.end() );
        std::vector< int > one_comb;
        std::vector< std::vector< int > > results;
        subsets_with_dup_impl( nums, 0, one_comb, results );
        if ( nums.size() > 0 ) results.push_back( one_comb );
        return results;
    }
private:
    void subsets_with_dup_impl( const std::vector< int > & nums,
                                int                        start,
                                std::vector< int >       & one_comb,
                                std::vector< std::vector< int > > & results ) {
        for ( int i = start; i < nums.size(); ++i ) {
            if ( i > start && nums[ i ] == nums[ i - 1 ] ) continue;
            one_comb.push_back( nums[ i ] );
            results.push_back( one_comb );
            if ( i < nums.size() - 1 )
                subsets_with_dup_impl( nums, i + 1, one_comb, results );
            one_comb.pop_back();
        }
    }
};
