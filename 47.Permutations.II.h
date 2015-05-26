/**
 * Algorithms 47 Permutations II                                           Hard
 *
 * Given a collection of numbers that might contain duplicates, return all
 * possible unique permutations.
 *
 * For example,
 * [1,1,2] have the following unique permutations:
 * [1,1,2], [1,2,1], and [2,1,1].
 *
 * Tags: Backtracking
 */

#include <vector>
#include <algorithm>
#include <set>

class Solution {
public:
    std::vector< std::vector< int > > permuteUnique( std::vector< int > & nums ) {
        std::vector< std::vector< int > > result;
        permute_unique_recursive( nums, result );
        return result;
    }
private:
    /**
     * The idea is from 46 Permutations. But we use a set to mark the used
     * element to avoid the duplicated element from entering the current
     * position.
     */
    void permute_unique_recursive( std::vector< int >                & nums,
                                   std::vector< std::vector< int > > & result ) {
        permute_unique_recursive_impl( nums, 0, result );
    }
    void permute_unique_recursive_impl(
            std::vector< int >                & nums,
            int                                 start,
            std::vector< std::vector< int > > & result ) {
        if ( start == nums.size() ) {
            result.push_back( nums );
            return;
        }
        
        std::set< int > s;
        for ( int i = start; i < nums.size(); ++i ) {
            if ( s.find( nums[ i ] ) != s.end() )
                continue;
            std::swap( nums[ start ], nums[ i ] );
            permute_unique_recursive_impl( nums, start + 1, result );
            std::swap( nums[ start ], nums[ i ] );
            s.insert( nums[ i ] );
        }
    }
    
    /**
     * O(n^n) runtime, O(n) space
     * This implementation uses an std::vector< bool > to flag if an element
     * is already used.
     * 
     * To handle the duplication we first sort the input nums.
     * For example [  1 1 2 ] is the sorted input, the for loop first takes
     * 1 as the first element then recurse to the subproblem [ 1 2 ] and so on.
     * However when the loop starts the second iteration, 1 appears again,
     * we need to skip the recursion function for this second 1.
     */
     void permute_unique_recursive_flag(
            std::vector< int >                & nums,
            std::vector< std::vector< int > > & result ) {
         if ( nums.size() == 0 ) return;
         std::vector< int > one_permutation;
         std::vector< bool > flag( nums.size(), false );
         std::sort( nums.begin(), nums.end() );
         permute_unique_recursive_flag_impl(
            nums, one_permutation, flag, result );
     }
     void permute_unique_recursive_flag_impl(
            std::vector< int >                & nums,
            std::vector< int >                & one_permutation,
            std::vector< bool >               & flag,
            std::vector< std::vector< int > > & result ) {
        
        //because of the following if condition
        //the caller permute_recursive_flag() needs to check
        //nums.size() == 0 otherwise result will have one empty
        //vector.
        if ( one_permutation.size() == nums.size() ) {
            result.push_back( one_permutation );
            return;
        }
        
        for ( int i = 0; i < nums.size(); ++i ) {
            if ( i > 0 && ! flag[ i - 1 ] && nums[ i ] == nums[ i - 1 ] )
                continue;
            if ( ! flag[ i ] ) {
                flag[ i ] = true;
                one_permutation.push_back( nums[ i ] );
                permute_unique_recursive_flag_impl(
                    nums, one_permutation, flag, result );
                one_permutation.pop_back();
                flag[ i ] = false;
            }
        }
    }
};
