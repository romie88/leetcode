/**
 * Algorithms 39 Combination Sum                                         Medium
 * 
 * Given a set of candidate numbers (C) and a target number (T), find all
 * unique combinations in C where the candidate numbers sums to T.
 *
 * The same repeated number may be chosen from C unlimited number of times.
 *
 * Note:
 * * All numbers (including target) will be positive integers.
 * * Elements in a combination (a1, a2, … , ak) must be in non-descending order.
 *   (ie, a1 ≤ a2 ≤ … ≤ ak).
 * * The solution set must not contain duplicate combinations.
 * 
 * For example, given candidate set 2,3,6,7 and target 7, 
 * A solution set is: 
 * [7] 
 * [2, 2, 3] 
 * 
 * Tags: Array, Backtracking
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector< std::vector< int > >
        combinationSum( std::vector< int > & candidates, const int target ) {
        
        std::sort( candidates.begin(), candidates.end() );
        int sum = 0;
        std::vector< int > v;
        std::vector< std::vector< int > > results;
        combination_sum_helper( candidates, target, 0, sum, v, results );
        return results;
    }
private:
    void combination_sum_helper(
            const std::vector< int >          & candidates,
            const int                           target,
            const int                           start,
            int                                 sum,
            std::vector< int >                & v,
            std::vector< std::vector< int > > & results ) {
        if ( sum == target ) {
            results.push_back( v );
            return;
        }
        //the recursive call into this condition is saved by
        //the following if check in the for loop
        //else if ( sum > target ) return;
        
        for ( int i = start;
              i < candidates.size() && candidates[ i ] <= target; ++i ) {
            //skip the same element so results won't have duplicates
            if ( i > start && candidates[ i ] == candidates[ i - 1 ] )
                continue;
            //the following if check can save the last recursive call
            //to check sum > target
            if ( sum + candidates[ i ] <= target ) {
                sum += candidates[ i ];
                v.push_back( candidates[ i ] );
                //still put in i since the same number can be picked unlimited
                //times
                combination_sum_helper( candidates, target, i, sum, v, results );
                sum -= candidates[ i ];
                v.pop_back();
            }
        }
    }
};