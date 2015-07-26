/**
 * Algorithms 60 Permutation Sequence                                    Medium
 * 
 * The set [1,2,3, ... ,n] contains a total of n! unique permutations.
 * 
 * By listing and labeling all of the permutations in order,
 * We get the following sequence (ie, for n = 3):
 * 
 * "123"
 * "132"
 * "213"
 * "231"
 * "312"
 * "321"
 *
 * Given n and k, return the k-th permutation sequence.
 * 
 * Note: Given n will be between 1 and 9 inclusive.
 * 
 * Tags: Backtracking, Math
 * Similar Problems: (M) Next Permutation, (M) Permutations
 */

#include <string>

class Solution {
public:
    /**
     * O( n ^ 2 ) runtime, O( n ) space
     */
    std::string getPermutation( int n, int k ) {
        std::string s;
        int nf = 1;
        for ( int i = 1; i <= n - 1; ++i ) {
            nf *= i;
            s += ( '0' + i );
        }
        s += ( '0' + n );
        //nf == ( n - 1 )! and s == "123 ... n"
        if ( k <= 0 || k > nf * n )
            throw std::out_of_range( "k is out of range" );
        --k;//to make k in the range of [ 0 ... n - 1 ]
        for ( int i = 0; i < n - 1; ++i ) {
            int index = k / nf + i;
            char c = s[ index ];
            while ( index >= i + 1 ) {
                s[ index ] = s[ index - 1 ];
                --index;
            }
            s[ i ] = c;
            k %= nf;
            nf /= ( n - 1 - i );
        }
        return s;
    }
};
