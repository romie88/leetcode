/**
 * Algorithms 4 Median of Two Sorted Arrays                               Hard
 *
 * There are two sorted arrays nums1 and nums2 of size m and n respectively.
 * Find the median of the two sorted arrays. The overall run time complexity
 * should be O(log (m+n)).
 *
 * Tags: Divide and Conquer, Array, Binary Search
 */

#include <vector>

class Solution {
public:
    double findMedianSortedArrays( const std::vector< int > & nums1,
                                   const std::vector< int > & nums2 ) {
        return find_median_of_two_sorted_arrays_impl_1( nums1, nums2 );
    }
public:
    /**
     * To find the median we need to consider two cases:
     * 
     * Case I
     * m + n is odd, image that we merge the two sorted arrays and get
     * a new array, ( m + n ) / 2 is the index pointing to the median
     * 
     * Case II
     * m + n is even, the median is the average of the two middle elements.
     * ( m + n ) / 2 - 1 and ( m + n ) / 2 are the index pointing to the
     * two middle elements.
     *
     * This problem asks for the median and in order to find the median
     * we actually need an algorithm to find the k-th smallest element
     * of two sorted arrays.
     *
     * If we have such an algorithm, our problem to find the median
     * immediately reduces to
     * Case I find the ( ( m + n ) / 2 + 1 )-th smallest element.
     * Case II find the ( ( m + n ) / 2 )-th smallest element and
     *              the ( ( m + n ) / 2 + 1 )-th smallest element
     *              and return the average of these two elements.
     *
     * So the problem is now how to find the k-th smallest element
     * from two sorted arrays where k = 1, ..., m + n.
     */
    double find_median_of_two_sorted_arrays_impl_1(
            const std::vector< int > & nums1,
            const std::vector< int > & nums2 ) {

        const int m = nums1.size();
        const int n = nums2.size();
        if ( ( m + n ) % 2 )
            return find_kth_smallest_of_two_sorted_arrays_helper_1(
                        nums1, 0, m - 1,
                        nums2, 0, n - 1,
                        ( m + n ) / 2 + 1 );
        else
            return ( find_kth_smallest_of_two_sorted_arrays_helper_1(
                        nums1, 0, m - 1,
                        nums2, 0, n - 1,
                        ( m + n ) / 2 )
                   + find_kth_smallest_of_two_sorted_arrays_helper_1(
                        nums1, 0, m - 1,
                        nums2, 0, n - 1,
                        ( m + n ) / 2 + 1 ) ) / 2.0;
    }
    
    /**
     * Here I illustrate the idea of divide-and-conquer to
     * find the k-th smallest element of two sorted arrays
     * where k = 1, ..., m + n.
     *
     * Let's say we have the following two arrays:
     * A_0, ... , A_(n_1)
     * B_0, ... , B_(m_1)
     * 
     * Take the middle index n / 2 and m / 2.
     *
     * If A_(n/2) >= B_(m/2) then A_(n/2) >= B_(m/2) >= B_(m/2 - 1) >= ... >= B_0
     * and A_(n/2) >= A_(n/2 - 1 ) >= ... >= A_0.
     * 
     * A_(n/2) >= totally m/2 + 1 + n/2 numbers.
     *
     * if k <= m/2 + 1 + n/2 then the k-th smallest element cannot be
     * in A_(n/2), A_(n/2 + 1), ... , A_(n-1).
     * Hence we can discard these elements.
     *
     * if k > m/2 + 1 + n/2 then the k-th smallest element cannot be
     * in B_(m/2), B_(m/2 - 1), ..., B_0.
     * Hence we can discard these elements and now we are finding
     * the ( k - ( m/2 + 1 ) )-th smallest element instead of the
     * k-th smallest element.
     *
     * The same analysis can be carried out for the case where
     * A_(n/2) < B_(m/2).
     */
    double find_kth_smallest_of_two_sorted_arrays_helper_1(
        const std::vector< int > & nums1, int s1, int e1,
        const std::vector< int > & nums2, int s2, int e2,
        int k ) {
        
        if ( s1 > e1 ) {
            return nums2[ s2 + k - 1 ];
        } else if ( s2 > e2 ) {
            return nums1[ s1 + k - 1 ];
        } else {
            int m1 = ( s1 + e1 ) / 2;
            int m2 = ( s2 + e2 ) / 2;
            if ( nums1[ m1 ] >= nums2[ m2 ] ) {
                if ( k <= ( m1 - s1 ) + ( m2 - s2 + 1 ) )
                    return find_kth_smallest_of_two_sorted_arrays_helper_1(
                                nums1, s1, m1 - 1,
                                nums2, s2, e2,
                                k );
                else
                    return find_kth_smallest_of_two_sorted_arrays_helper_1(
                                nums1, s1, e1,
                                nums2, m2 + 1, e2,
                                k - ( m2 - s2 + 1 ) );
            } else {
                if ( k <= ( m2 - s2 ) + ( m1 - s1 + 1 ) )
                    return find_kth_smallest_of_two_sorted_arrays_helper_1(
                                nums1, s1, e1,
                                nums2, s2, m2 - 1,
                                k );
                else
                    return find_kth_smallest_of_two_sorted_arrays_helper_1(
                                nums1, m1 + 1, e1,
                                nums2, s2, e2,
                                k - ( m1 - s1 + 1 ) );
            }
        }
    }
    
    /**
     * Here is another implemenation with similar discarding logic
     */
    double find_median_of_two_sorted_arrays_impl_2(
            const std::vector< int > & nums1,
            const std::vector< int > & nums2 ) {
        
        const int m = nums1.size();
        const int n = nums2.size();
        if ( ( m + n ) & 0x1 )
            return find_kth_smallest_of_two_sorted_arrays_helper_2(
                        nums1, 0, m - 1,
                        nums2, 0, n - 1,
                        ( m + n ) / 2 + 1 );
        else
            return ( find_kth_smallest_of_two_sorted_arrays_helper_2(
                        nums1, 0, m - 1,
                        nums2, 0, n - 1,
                        ( m + n ) / 2 )
                   + find_kth_smallest_of_two_sorted_arrays_helper_2(
                        nums1, 0, m - 1,
                        nums2, 0, n - 1,
                        ( m + n ) / 2 + 1 ) ) / 2.0;
    }
    
    double find_kth_smallest_of_two_sorted_arrays_helper_2(
        const std::vector< int > & nums1, int s1, int e1,
        const std::vector< int > & nums2, int s2, int e2,
        int k ) {
        
        //with this we can always assume that
        //the length of nums1 <= the length of nums2
        if ( e1 - s1 + 1 > e2 - s2 + 1 ) {
            return find_kth_smallest_of_two_sorted_arrays_helper_2(
                    nums2, s2, e2, nums1, s1, e1, k );
        }

        if ( e1 - s1 + 1 == 0 )
            return nums2[ s2 + k - 1 ];

        if ( k == 1 )
            return std::min( nums1[ s1 ], nums2[ s2 ] );

        //divide k into two parts
        int ka = std::min( k/2, e1 - s1 + 1 );
        int kb = k - ka;
        if ( nums1[ s1 + ka - 1 ] < nums2[ s2 + kb - 1 ] )
            return find_kth_smallest_of_two_sorted_arrays_helper_2(
                    nums1, s1 + ka, e1, nums2, s2, e2, k - ka );
        else if ( nums1[ s1 + ka - 1 ] > nums2[ s2 + kb - 1 ] )
            return find_kth_smallest_of_two_sorted_arrays_helper_2(
                    nums1, s1, e1, nums2, s2 + kb, e2, k - kb );
        else
            return nums1[ s1 + ka - 1 ];
    }
};

