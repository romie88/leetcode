/**
 * Algorithms 154 Find Minimum in Rotated Sorted Array II                  Hard
 * 
 * Follow up for "Find Minimum in Rotated Sorted Array":
 * What if duplicates are allowed?
 * Would this affect the run-time complexity? How and why?
 *
 * Suppose a sorted array is rotated at some pivot unknown to you beforehand.
 * 
 * (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
 * 
 * Find the minimum element.
 * 
 * The array may contain duplicates.
 * 
 * Tags: Array, Binary Search
 * Similar Problems: (M) Find Minimum in Rotated Sorted Array
 */

#include <vector>

class Solution {
public:
	/**
	 * Exactly like Algorithms 81 Search in Rotated Sorted Array II
	 * 3 1 2 3 3 3 3
	 *       |
	 * 3 3 3 3 1 2 3
	 * When nums[ M ] == nums[ R ], we don't know which half the minimum
	 * resides in. But we can rule out nums[ R ] since even if nums[ R ] is
	 * the minimum we have nums[ M ] == nums[ R ].
	 */
    int findMin( std::vector< int > & nums ) {
        int L = 0;
		int R = nums.size() - 1;
		while ( L < R ) {
			int M = ( L + R ) / 2;
			if ( nums[ M ] < nums[ R ] )
				R = M;
			else if ( nums[ M ] > nums[ R ] )
				L = M + 1;
			else
				--R;
		}
		return nums[ L ];
    }
};

/**
 * Solution
 * 
 * For case where AL == AM == AR, the minimum could be on AM’s left or right
 * side (eg, [1, 1, 1, 0, 1] or [1, 0, 1, 1, 1]). In this case, we could not
 * discard either subarrays and therefore such worst case degenerates to the
 * order of O(n).
 */
