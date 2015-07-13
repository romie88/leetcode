/**
 * Algorithms 35  Search Insert Position                                Medium
 *
 * Given a sorted array and a target value, return the index if the target is
 * found. If not, return the index where it would be if it were inserted in
 * order.
 *
 * You may assume no duplicates in the array.
 *
 * Here are few examples.
 * [1,3,5,6], 5 -> 2
 * [1,3,5,6], 2 -> 1
 * [1,3,5,6], 7 -> 4
 * [1,3,5,6], 0 -> 0
 *
 * Tags: Array, Binary Search
 * Similar Problems: (M) Search for a Range
 */

#include <vector>

class Solution {
public:
    int searchInsert( const std::vector< int > & nums, const int target ) {
        return search_leftmost_insert_index( nums, target );
    }
private:
    /**
     * The problem in a general form:
     *
     * Find the insert position for the given target in the
     * given array. The array can have duplicates. And the
     * insert position i must have the following property:
     * 
     * A[ i ] >= target && A[ i - 1 ] < target   if i >  0
     * A[ i ] >= target                          if i == 0
     * A[ k ] <  target for all k = 0, ..., A.size() - 1
     *                                           if i == A.size()
     * 
     * That is to find the left-most insert position i and
     * the target is inserted before the index i.
     * 
     * The implementation is as following. Now we need to
     * analyze this implementation and prove it correctly
     * find the insert index i.
     * 
     * When the loop terminates, L > R.
     * Here there is a very important observation about the
     * following implementation: L = R + 1 when the loop
     * terminates. Consider the last iteration.
     * If in the last iteration L == R, then M == L == R.
     * After the loop body will update either R or L and
     * result L = R + 1.
     * If in the last iteration L < R, let's consider
     * the details:
     * If L + 1 = R, then L == M < R. If L gets updated,
     * L will be the same as R. If R gets updated, R will
     * be L - 1.
     * If L + 1 < R, then no matter what the loop cannot
     * terminate by this iteration.
     * 
     * Hence when the loop terminates L = R + 1.
     * Let L_old and R_old to be the value of L and R in
     * the last iteration.
     * 
     * M_old = L_old + ( L_old + R_old ) / 2;
     * Thus L_old <= M_old <= R_old.
     * 
     * If A[ M_old ] >= target, R is updated to be M_old - 1.
     * L = L_old <= M_old and L > R = M_old - 1.
     * Hence L = M_old and A[ L ] = A[ M_old ] >= target.
     * If L = 0 then we are done.
     * If L > 0 then we need to verify A[ L - 1 ] < target.
     * Since L > 0 and L starts with 0, there is at least
     * one iteration in which L gets updated. Let's consider
     * the last iteration in which L gets updated.
     * In that iteration, L = L' = M' + 1 and A[ M' ] < target.
     * Hence A[ L - 1 ] < target.
     *
     * If A[ M_old ] < target, L is updated to be M_old + 1.
     * L = L_old = M_old + 1 and A[ L - 1 ] < target.
     * We still need to verify that A[ L ] >= target.
     * Let's check R. If R is never updated in the loop.
     * Now L > R = A.size() - 1. And actually L = R + 1 when
     * loop terminates. This is the case that target is larger
     * than all the elements in the array.
     * If R is updated at least once, let's consider the last
     * iteration in which R gets update.
     * In that iteration, R = R' = M' - 1 and A[ M' ] >= target.
     * Hence A[ R + 1 ] >= target.
     * And actually L = R + 1 when loop terminates.
     * That is A[ L ] >= target.
     *
     * From the above, L is the correct insert index.
     */
    int search_leftmost_insert_index( const std::vector< int > & A,
                                      const int                  target ) {
        int L = 0;
        int R = A.size() - 1;
        while ( L <= R ) {
            int M = L + ( R - L ) / 2;//avoid potential overflow
            if ( A[ M ] >= target )
                R = M - 1;
            else
                L = M + 1;
        }
        return L;
    }
    
    /**
     * The problem in a general form:
     *
     * Find the insert position for the given target in the
     * given array. The array can have duplicates. And the
     * insert position i must have the following property:
     *
     * A[ i ] >  target && A[ i - 1 ] <= target   if i >  0
     * A[ i ] >  target                           if i == 0
     * A[ k ] <= target for all k = 0, ..., A.size() - 1
     *                                            if i == A.size()
     *
     * That is to find the right-most insert position i and
     * the target is inserted before the index i.
     *
     * The implementation is as following. Now we need to
     * analyze this implementation and prove it correctly
     * find the insert index i.
     *
     * When the loop terminates, L = R + 1.
     * Consider the last iteration, let L_old and R_old to
     * be the value of L and R in the last iteration.
     * 
     * M_old = L_old + ( L_old + R_old ) / 2;
     * Thus L_old <= M_old <= R_old.
     * 
     * If A[ M_old ] > target, R is updated to be M_old - 1.
     * L = L_old <= M_old and L > R = M_old - 1.
     * Hence L = M_old and A[ L ] = A[ M_old ] > target.
     * If L = 0 then we are done.
     * If L > 0 then we need to verify A[ L - 1 ] <= target.
     * Since L > 0 and L starts with 0, there is at least
     * one iteration in which L gets updated. Let's consider
     * the the last iteration in which L gets updated.
     * In that iteration, L = L' = M' + 1 and A[ M' ] <= target.
     * Hence A[ L - 1 ] <= target. Thus L is truly the index
     * we are looking for.
     * 
     * If A[ M_old ] <= target, L is updated to be M_old + 1.
     * L = L_old = M_old + 1 and A[ L - 1 ] <= target.
     * We still need to verify that A[ L ] > target.
     * Let's check R. If R is never updated in the loop.
     * Now L > R = A.size() - 1. And actually L = R + 1 when
     * loop terminates. This is the case that target is larger
     * than all the elements in the array.
     * If R is updated at least once, let's consider the last
     * iteration in which R gets update.
     * In that iteration, R = R' = M' - 1 and A[ M' ] > target.
     * Hence A[ R + 1 ] > target.
     * And actually L = R + 1 when loop terminates.
     * That is A[ L ] > target.
     *
     * From the above, L is the correct insert index.
     */
    int search_rightmost_insert_index( const std::vector< int > & A,
                                       const int                  target ) {
        int L = 0;
        int R = A.size() - 1;
        while ( L <= R ) {
            int M = L + ( R - L ) / 2;
            if ( A[ M ] > target )
                R = M - 1;
            else
                L = M + 1;
        }
        return L;
    }
};

