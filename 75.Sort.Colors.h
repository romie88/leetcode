/**
 * Algorithms 75 Sort Colors                                             Medium
 * 
 * Given an array with n objects colored red, white or blue, sort them so that
 * objects of the same color are adjacent, with the colors in the order red,
 * white and blue.
 * 
 * Here, we will use the integers 0, 1, and 2 to represent the color red,
 * white, and blue respectively.
 * 
 * Note:
 * You are not suppose to use the library's sort function for this problem.
 * 
 * click to show follow up.
 * 
 * Follow up:
 * A rather straight forward solution is a two-pass algorithm using counting
 * sort.
 * First, iterate the array counting number of 0's, 1's, and 2's, then
 * overwrite array with total number of 0's, then 1's and followed by 2's.
 * 
 * Could you come up with an one-pass algorithm using only constant space?
 * 
 * Tags: Array, Two Pointers, Sort
 * Similar Problems: (M) Sort List
 */

#include <vector>

class Solution {
public:
    /**
     * This is the classic "Dutch National Flag Problem", i.e., the three-way
     * partition problem.
     * 
     * L = 0
     * M = 0
     * H = n - 1
     * [ 0, L - 1 ]     x = 0
     * [ L, M - 1 ]     x = 1
     * [ M, H ]         x unknown
     * [ H + 1, n - 1 ] x = 2
     */
    void sortColors( std::vector< int > & nums ) {
        int L = 0;
        int M = 0;
        int H = nums.size() - 1;
        while ( M <= H ) {
            switch( nums[ M ] ) {
                case 0:
                    std::swap( nums[ L++ ], nums[ M++ ] );
                    break;
                case 1:
                    ++M;
                    break;
                case 2:
                    std::swap( nums[ H-- ], nums[ M ] );
            }
        }
    }
};
