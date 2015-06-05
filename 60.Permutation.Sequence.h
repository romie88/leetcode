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
 * Given n and k, return the kth permutation sequence.
 * 
 * Note: Given n will be between 1 and 9 inclusive.
 * 
 * Tags: Backtracking, Math
 */

#include <string>

class Solution {
public:
    /**
     * O(n^2) runtime, O(n) space
     */
    std::string getPermutation(int n, int k) {
        std::string s;
        --k;//make k to be in range [ 0, n - 1 ]
        int nfactor = 1;
        for ( int i = 2; i <= n; ++i )
            nfactor *= i;
        
        std::vector< bool > flag( n, false );
        for ( int i = 0; i < n; ++i ) {
            nfactor /= ( n - i );
            int j = k / nfactor;
            
            /**
             * Here I use a vector of flags.
             * As an alternative we can use vector< char >
             * and keep erasing the char in index j.
             */
            int p = 0;
            int unused = 0;
            for ( p = 0; p < n; ++p ) {
                if ( ! flag[ p ] ) {
                    if ( j == unused ) break;
                    else ++unused;
                }
            }
            
            s.push_back( '0' + p + 1 );
            flag[ p ] = true;
            k %= nfactor;
        }
        return s;
    }
};
