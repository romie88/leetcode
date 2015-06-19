/**
 * Algorithms 215 Kth Largest Element in an Array                        Medium
 * 
 * Find the kth largest element in an unsorted array. Note that it is the kth
 * largest element in the sorted order, not the kth distinct element.
 * 
 * For example,
 * Given [3,2,1,5,6,4] and k = 2, return 5.
 * 
 * Note: 
 * You may assume k is always valid, 1 <= k <= array's length.
 * 
 * Credits:
 * Special thanks to @mithmatt for adding this problem and creating all test
 * cases.
 * 
 * Tags: Divide and Conquer, Heap
 */

#include <vector>
#include <stdexcept>
#include <iostream>

class Solution {
public:
    int findKthLargest( std::vector< int > & nums, int k ) {
        return find_kth_largest( nums, k );
    }
private:
    int partition( std::vector< int > & nums, int p, int r ) {
        int i = p - 1;
        for ( int j = p; j < r; ++j ) {
            if ( nums[ j ] < nums[ r ] ) {
                std::swap( nums[ j ], nums[ ++i ] );
            }
        }
        std::swap( nums[ r ], nums[ ++i ] );
        return i;
    }
    
    int find_kth_largest( std::vector< int > & nums, int k ) {
        int p = 0;
        int r = nums.size() - 1;
        if ( k < p + 1 || k > r + 1 ) throw std::out_of_range( "k is out of range" );
        while ( p < r ) {
            int i = partition( nums, p, r );
            if ( i == r + 1 - k ) return nums[ i ];
            else if ( i < r + 1 - k ) {
                p = i + 1;
            } else {
                k = k - r + i - 1;
                r = i - 1;
            }
        }
        return nums[ p ];
    }
};
