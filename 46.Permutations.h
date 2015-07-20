/**
 * Algorithms 46 Permutations                                            Medium
 *
 * Given a collection of numbers, return all possible permutations.
 * 
 * For example,
 * [1,2,3] have the following permutations:
 * [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
 *
 * Tags: Backtracking
 * Similar Problems: (M) Next Permutation, (H) Permutations II
 *                   (M) Permutation Sequence, (M) Combinations
 */

#include <vector>

class Solution {
public:
    std::vector< std::vector< int > > permute( std::vector< int > & nums ) {
        std::vector< std::vector< int > > result;
        permute_recursive_swap( nums, result );
        return result;
    }
private:
    /**
     * O(n!) runtime, O(n) stack space
     * This implementation uses std::swap to avoid using a std::vector< bool >
     * and the input vector nums itself to store every generated permutation.
     */
    void permute_recursive_swap( std::vector< int >                & nums,
                                 std::vector< std::vector< int > > & result ) {
        permute_recursive_swap_impl( nums, 0, result );
    }
    void permute_recursive_swap_impl(
            std::vector< int >                & nums,
            int                                 start,
            std::vector< std::vector< int > > & result ) {
        if ( start == nums.size() ) {
            result.push_back( nums );
            return;
        }
        
        for ( int i = start; i < nums.size(); ++i ) {
            std::swap( nums[ start ], nums[ i ] );
            permute_recursive_swap_impl( nums, start + 1, result );
            std::swap( nums[ start ], nums[ i ] );
        }
    }
    
    /**
     * O(n^n) runtime, O(n) space
     * This implementation uses an std::vector< bool > to flag if an element
     * is already used.
     */
     void permute_recursive_flag( std::vector< int >                & nums,
                                  std::vector< std::vector< int > > & result ) {
         if ( nums.size() == 0 ) return;
         std::vector< int > one_permutation;
         std::vector< bool > flag( nums.size(), false );
         permute_recursive_flag_impl( nums, one_permutation, flag, result );
     }
     void permute_recursive_flag_impl(
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
            if ( ! flag[ i ] ) {
                flag[ i ] = true;
                one_permutation.push_back( nums[ i ] );
                permute_recursive_flag_impl( nums, one_permutation, flag, result );
                one_permutation.pop_back();
                flag[ i ] = false;
            }
        }
    }
    
    /**
     * This implementation is iterative. The idea is that given that we already
     * have all the permutation of i elements how to add the i + 1 th element.
     * For example, we starts with [ 1 ] then add 2 to [ 1 ],
     * we have [ 1, 2 ] and [ 2, 1 ]. Now add 3 to [ 1, 2 ] and [ 2, 1 ]
     * and so on.
     */
    void permute_iterative( std::vector< int >                & nums,
                            std::vector< std::vector< int > > & result ) {
        if ( nums.size() == 0 ) return;
        result.push_back( std::vector< int >( 1, nums[ 0 ] ) );
        for ( int i = 1; i < nums.size(); ++i ) {
            std::vector< std::vector< int > > tmp_result;
            for ( const auto & r : result ) {
                std::vector< int > r_copy( r );
                for ( int k = 0; k < r.size(); ++k ) {
                    r_copy.insert( r_copy.begin() + k, nums[ i ] );
                    tmp_result.push_back( r_copy );
                    r_copy.erase( r_copy.begin() + k );
                }
                //there is one more!!!
                r_copy.push_back( nums[ i ] );
                tmp_result.push_back( r_copy );
            }
            result.swap( tmp_result );
        }
    }
};
