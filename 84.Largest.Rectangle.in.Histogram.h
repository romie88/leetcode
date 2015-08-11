/**
 * Algorithms 84 Largest Rectangle in Histogram                            Hard
 *
 * Given n non-negative integers representing the histogram's bar height where
 * the width of each bar is 1, find the area of largest rectangle in the
 * histogram.
 *
 *        6
 *     5  _
 *      _| |
 *     | | |  3
 *  2  | | |2 _
 *  _ 1| | |_| |
 * | |_| | | | |
 * |_|_|_|_|_|_|
 *
 * Above is a histogram where width of each bar is 1, given height =
 * [ 2, 1, 5, 6, 2, 3 ].
 *
 *        6
 *     5  _
 *      _| |
 *     |/|/|  3
 *  2  |/|/|2 _
 *  _ 1|/|/|_| |
 * | |_|/|/| | |
 * |_|_|/|/|_|_|
 *
 * The largest rectangle is shown in the shaded area, which has area = 10 unit.
 *
 * For example,
 * Given height = [2,1,5,6,2,3],
 * return 10.
 *
 * Tags: Array, Stack
 * Similar problems: (H) Maximal Rectangle
 */

#include <vector>
#include <stack>
#include <algorithm>

class Solution {
public:
    int largestRectangleArea( const std::vector< int > & height ) {
        return largest_rectangle_area_impl_DnC( height );
    }
private:
    /**
     * O(n) runtime, O(n) space - implementation using stack
     */
    int largest_rectangle_area_stack_impl_1(
            const std::vector< int > & height ) {
        struct IndexHeight {
            int index;
            int height;
            IndexHeight( int i = -1, int h  = 0 ) : index( i ), height( h ) {}
        };
        std::stack< IndexHeight > s;
        const int N = height.size();
        int max_area = 0;
        for ( int i = 0; i < N; ++i ) {
            if ( s.empty() || s.top().height <= height[ i ] )
                s.push( IndexHeight( i, height[ i ] ) );
            else {
                int last_index = -1;
                while ( ! s.empty() && s.top().height > height[ i ] ) {
                    max_area = std::max( max_area,
                                         s.top().height * ( i - s.top().index ) );
                    last_index = s.top().index;
                    s.pop();
                }
                s.push( IndexHeight( last_index, height[ i ] ) );
            }
        }
        while ( ! s.empty() ) {
            max_area = std::max( max_area,
                                 s.top().height * ( N - s.top().index ) );
            s.pop();
        }
        return max_area;
    }

    /**
     * O(n) runtime, O(n) space - implementation using stack, a better one
     */
    int largest_rectangle_area_stack_impl_2(
            const std::vector< int > & height ) {
        std::stack< int > s;
        const int N = height.size();
        int max_area = 0;
        int i = 0;
        while ( i < N ) {
            if ( s.empty() || height[ s.top() ] < height[ i ] )
                s.push( i++ );
            else {
                int j = s.top();
                s.pop();
                max_area = std::max(
                    max_area,
                    height[ j ] * ( i -  ( s.empty() ? 0 : s.top() + 1 ) ) );
            }
        }
        while ( ! s.empty() ) {
            int j = s.top();
            s.pop();
            max_area = std::max(
                max_area,
                height[ j ] * ( i -  ( s.empty() ? 0 : s.top() + 1 ) ) );
        }
        return max_area;
    }

    /**
     * O( n log n ) runtime - Divide and Conquer
     */
    int largest_rectangle_area_impl_DnC(
            const std::vector< int > & height ) {
        return largest_rectangle_area_impl_DnC_helper(
                    height, 0, height.size() - 1 );
    }
    int largest_rectangle_area_impl_DnC_helper(
            const std::vector< int > & height, int start, int end ) {
        if ( start > end ) return 0;
        if ( start == end ) return height[ start ];

        int mid = ( start + end ) / 2;
        int left_max_area = largest_rectangle_area_impl_DnC_helper(
                height, start, mid );
        int right_max_area = largest_rectangle_area_impl_DnC_helper(
                height, mid + 1, end );

        int i = mid;
        int j = mid + 1;
        int min_height = std::min( height[ i ], height[ j ] );
        int cross_max_area = min_height * ( j - i + 1 );
        while ( i >= start && j <= end ) {
            min_height = std::min( min_height,
                                   std::min( height[ i ], height[ j ] ) );
            cross_max_area = std::max( cross_max_area,
                                       min_height * ( j - i + 1 ) );
            if ( i == start ) ++j;
            else if ( j == end ) --i;
            else {
                if ( height[ i - 1 ] >= height[ j + 1 ] )
                    --i;
                else
                    ++j;
            }
        }
        return std::max( cross_max_area,
                         std::max( left_max_area, right_max_area ) );
    }
};
