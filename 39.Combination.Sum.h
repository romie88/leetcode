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
 * * Elements in a combination (a1, a2, ... , ak) must be in non-descending order.
 *   (ie, a1 <= a2 <= ... <= ak).
 * * The solution set must not contain duplicate combinations.
 * 
 * For example, given candidate set 2,3,6,7 and target 7, 
 * A solution set is: 
 * [7] 
 * [2, 2, 3] 
 * 
 * Tags: Array, Backtracking
 * Similar Problems: (M) Letter Combinations of a Phone Number
 *                   (M) Combination Sum II
 *                   (M) Combinations
 *                   (M) Combination Sum III
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector< std::vector< int > >
    combinationSum( std::vector< int > & candidates, const int target ) {
        return combination_sum_impl1( candidates, target );
    }
private:
    /**
     * My pure recursive implementation
     */
    std::vector< std::vector< int > >
    combination_sum_impl2( std::vector< int > & candidates, const int target ) {
        std::vector< int >                one_result;
        std::vector< std::vector< int > > results;
        std::sort( candidates.begin(), candidates.end() );
        combination_sum_impl2_helper( candidates, target, 0, 0, one_result, results );
        return results;
    }
    void combination_sum_impl2_helper(
            const std::vector< int >          & candidates,
            const int                           target,
            int                                 sum,
            int                                 i,
            std::vector< int >                & one_result,
            std::vector< std::vector< int > > & results ) {
        if ( i >= candidates.size() ) {
            if ( sum == target ) {
                results.push_back( one_result );
            }
            return;
        }
        if ( sum == target ) {
            results.push_back( one_result );
            return;
        } else if ( sum > target )
            return;
        
        //pick candidates[ i ]
        if ( sum + candidates[ i ] <= target ) {
            one_result.push_back( candidates[ i ] );
            combination_sum_impl2_helper( candidates,
                                          target,
                                          sum + candidates[ i ],
                                          i,//allow repeated selection
                                          one_result,
                                          results );
            one_result.pop_back();
        } else
            return;
        
        ++i;
        while ( i < candidates.size() && candidates[ i - 1 ] == candidates[ i ] )
            ++i;
        combination_sum_impl2_helper( candidates,
                                      target, sum, i, one_result, results );
    }
    /**
     * Another implementation using loop
     */
    std::vector< std::vector< int > >
    combination_sum_impl1( std::vector< int > & candidates, const int target ) {
        std::vector< int >                one_result;
        std::vector< std::vector< int > > results;
        std::sort( candidates.begin(), candidates.end() );
        combination_sum_impl1_helper( candidates, target, 0, 0, one_result, results );
        return results;
    }
    void combination_sum_impl1_helper(
            const std::vector< int >          & candidates,
            const int                           target,
            const int                           start,
            int                                 sum,
            std::vector< int >                & one_result,
            std::vector< std::vector< int > > & results ) {
        if ( sum == target ) {
            results.push_back( one_result );
            return;
        } else if ( sum > target )
            return;
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
                one_result.push_back( candidates[ i ] );
                combination_sum_impl1_helper( candidates,
                                              target,
                                              i,//allow repeated selection
                                              sum + candidates[ i ],
                                              one_result,
                                              results );
                one_result.pop_back();
            } else
                break;
        }
    }
};
