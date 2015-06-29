/**
 * 169 Majority Element                                                    Easy
 * 
 * Given an array of size n, find the majority element. The majority element is
 * the element that appears more than [ n/2 ] (floor) times.
 * 
 * You may assume that the array is non-empty and the majority element always
 * exist in the array.
 * 
 * Credits:
 * 
 * Special thanks to @ts for adding this problem and creating all test cases.
 * 
 * Tags: Divide and Conquer, Array, Bit Manipulation
 */

#include <vector>

class Solution {
public:
    int majorityElement( const std::vector< int > & nums ) {
        return majority_element_Moore_voting( nums );
    }
private:
    int majority_element_Moore_voting( const std::vector< int > & nums ) {
        int majority_num = nums[ 0 ];
        int freq = 1;
        for ( int i = 1; i < nums.size(); ++i ) {
            if ( nums[ i ] == majority_num )
                ++freq;
            else if ( freq == 0 )
                majority_num = nums[ i ];
            else
                --freq;
        }
        return majority_num;
    }
};

/**
 * Solution
 * 
 * 1. Runtime: O(n2) — Brute force solution: Check each element if it is the
 *    majority element.
 * 2. Runtime: O(n), Space: O(n) — Hash table: Maintain a hash table of the
 *    counts of each element, then find the most common one.
 * 3. Runtime: O(n log n) — Sorting: As we know more than half of the array are
 *    elements of the same value, we can sort the array and all majority
 *    elements will be grouped into one contiguous chunk. Therefore, the middle
 *    (n/2th) element must also be the majority element.
 * 4. Average runtime: O(n), Worst case runtime: Infinity — Randomization:
 *    Randomly pick an element and check if it is the majority element. If it
 *    is not, do the random pick again until you find the majority element. As
 *    the probability to pick the majority element is greater than 1/2, the
 *    expected number of attempts is < 2.
 * 5. Runtime: O(n log n) — Divide and conquer: Divide the array into two
 *    halves, then find the majority element A in the first half and the
 *    majority element B in the second half. The global majority element must
 *    either be A or B. If A == B, then it automatically becomes the global
 *    majority element. If not, then both A and B are the candidates for the
 *    majority element, and it is suffice to check the count of occurrences for
 *    at most two candidates. The runtime complexity,
 *    T(n) = T(n/2) + 2n = O(n log n).
 * 6. Runtime: O(n) — Moore voting algorithm: We maintain a current candidate
 *    and a counter initialized to 0. As we iterate the array, we look at the
 *    current element x:
 *    1. If the counter is 0, we set the current candidate to x and the counter
 *       to 1.
 *    2. If the counter is not 0, we increment or decrement the counter based
 *       on whether x is the current candidate.
 *    After one pass, the current candidate is the majority element. Runtime
 *    complexity = O(n).
 * 7. Runtime: O(n) — Bit manipulation: We would need 32 iterations, each
 *    calculating the number of 1's for the ith bit of all n numbers. Since a
 *    majority must exist, therefore, either count of 1's > count of 0's or
 *    vice versa (but can never be equal). The majority number’s ith bit must
 *    be the one bit that has the greater count.
 * 
 * Update (2014/12/24): Improve algorithm on the O(n log n) sorting solution:
 * We do not need to 'Find the longest contiguous identical element' after
 * sorting, the n/2th element is always the majority.
 * 
 * Analysis written by @ts and @1337c0d3r.
 */
