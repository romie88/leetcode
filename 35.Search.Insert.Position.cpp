//35 Search Insert Position [ Medium ]
//
//Given a sorted array and a target value, return the index if the target is
//found. If not, return the index where it would be if it were inserted in
//order.
//
//You may assume no duplicates in the array.
//
//Here are few examples.
//[1,3,5,6], 5 → 2
//[1,3,5,6], 2 → 1
//[1,3,5,6], 7 → 4
//[1,3,5,6], 0 → 0
//
//Tags: Array, Binary Search

/**
 * Analysis why the following binary search returning low is correct.
 *
 * There are a few cases to consider.
 *
 * Just before the while loop terminates, we can have the following:
 *
 * l < m < h and l + 1 == m and m + 1 == h
 *
 * l == h == m
 *
 * l == m < h and m + 1 == h
 *
 * the analysis of all these cases are very similar. I will take
 * l == h == m to illustrate the detailed reasoning.
 *
 * Case 1. t > a[ m ], l = m + 1 > h, while loop terminates
 * Case 2. t < a[ m ], h = m - 1 < l, while loop terminates
 * 
 * For Case 1, we want to show that a[ m ] = a[ l ] < t < a[ m + 1 ]
 * Note m + 1 is the value in l after the while loop terminates.
 * a[ m + 1 ] == a[ h + 1 ]
 * If during the whole process, h is never changed, which means
 * all the a[ m ] values are < t, and finally a[ h ] == a[ m ] < t so t is greater
 * than all the elements in a[]. So the insert position is n == h + 1 == m + 1
 * which means inserting at the end of the array a[].
 * If during the whole process, h is updated, then the latest update of h
 * is h = m - 1 with some m and we know a[ m ] > t. So we have a[ l ] < t < a[ h + 1 ]
 * and again when the while loop terminates the value of l is h + 1.
 * Hence we proved Case 1 the returned value of low is the index where
 * the target should be inserted right before.
 *
 * For Case 2, we want to show that a[ m - 1 ] < t < a[ m ] = a[ h ]
 * Note that m is the value in l after the while loop terminates.
 * a[ m - 1 ] == a[ h - 1 ]
 * If during the whole process, l is never changed, which means
 * all the a[ m ] values are > t, and finally a[ l ] == a[ m ] > t so t is smaller
 * than all the elements in a[]. So the insert position is 0 == l == m
 * which means inserting at the beginning of the array a[].
 * If during the whole process, l is updated, then the latest update of l
 * is l = m + 1 with some m and we know a[ m ] < t. So we have a[ l - 1 ] < t < a[ h ]
 * and again when the while loop terminates the value of l is m or h.
 * Hence we proved Case 2 the returned value of low is the index where
 * the target should be inserted right before.
 *
 * All the other cases are similarly proved and reduced to these cases.
 */
class Solution {
public:
    int searchInsert( int A[], int n, int target ) {
        int low  = 0;
        int high = n - 1;
        int mid  = low + ( ( high - low ) >> 1 );
        while ( low <= high ) {
            if ( target == A[ mid ] ) {
                return mid;
            } else if ( target < A[ mid ] ) {
                high = mid - 1;
            } else {
                low  = mid + 1;
            }
            mid = low + ( ( high - low ) >> 1 );
        }
        return low;
    }
};
