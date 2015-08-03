/**
 * Algorithms 77 Combinations                                            Medium
 *
 * Given two integers n and k, return all possible combinations of k numbers
 * out of 1 ... n.
 *
 * For example,
 * If n = 4 and k = 2, a solution is:
 *
 * [
 *   [2,4],
 *   [3,4],
 *   [2,3],
 *   [1,2],
 *   [1,3],
 *   [1,4],
 * ]
 *
 * Tags: Backtracking
 * Similar Problems: (M) Combination Sum, (M) Permutations
 */

#include <vector>

class Solution {
public:
    std::vector< std::vector< int > > combine( const int n, const int k ) {
        std::vector< std::vector< int > > results;
        combine_impl2_wrapper( n, k, results );
        return results;
    }
private:
    /**
     * Implemenation without loop
     */
    void combine_impl( const int                           n,
                       const int                           start,
                       const int                           k,
                       std::vector< int >                & one_comb,
                       std::vector< std::vector< int > > & results ) {
        if ( k == 0 ) {
            results.push_back( one_comb );
            return;
        }
        if ( n - start + 1 < k ) return;

        //pick start
        one_comb.push_back( start );
        combine_impl( n, start + 1, k - 1, one_comb, results );
        one_comb.pop_back();
        //ignore start
        combine_impl( n, start + 1, k, one_comb, results );
    }
    void combine_impl_wrapper( const int n, const int k,
                               std::vector< std::vector< int > > & results ) {
        if ( k == 0 ) return;
        std::vector< int > one_comb;
        combine_impl( n, 1, k, one_comb, results );
    }

    /**
     * Implementation using loop
     * The idea is that after picking i from 1 to n then solve the sub-problem
     * of combinations k - 1 from i + 1 to n.
     */
    void combine_impl2( const int                           n,
                        const int                           start,
                        const int                           k,
                        std::vector< int >                & one_comb,
                        std::vector< std::vector< int > > & results ) {
        if ( one_comb.size() == k ) {
            results.push_back( one_comb );
            return;
        }

        //no need to proceed if the number of remaining elements is not enough
        //note that N <= n as long as one_comb.size() < k
        const int N = n + 1 - k + one_comb.size();
        for ( int i = start; i <= N; ++i ) {
            one_comb.push_back( i );
            combine_impl2( n, i + 1, k, one_comb, results );
            one_comb.pop_back();
        }
    }
    void combine_impl2_wrapper( const int n, const int k,
                                std::vector< std::vector< int > > & results ) {
        if ( k == 0 ) return;
        std::vector< int > one_comb;
        combine_impl2( n, 1, k, one_comb, results );
    }
};