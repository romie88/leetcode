/**
 * Algorithms 42 Trapping Rain Water                                       Hard
 * 
 * Given n non-negative integers representing an elevation map where the width
 * of each bar is 1, compute how much water it is able to trap after raining.
 * 
 * For example, 
 * Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
 * 
 * The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1].
 * In this case, 6 units of rain water (blue section) are being trapped.
 * Thanks Marcos for contributing this image!
 * 
 * Tags: Array, Stack, Two Pointers
 * Similar Problems: (M) Container With Most Water,
 *                   (M) Production Array Except Self
 */

#include <vector>
#include <stack>

class Solution {
public:
    int trap( std::vector< int > & height ) {
        return trap_impl_2( height );
    }
private:
    /**
     * O( n ) runtime, O( n ) space - maximum heights on both sides
     */
    int trap_impl_1( const std::vector< int > & height ) {
        /**
         * Consider every single bar, the water can be hold by a bar
         * is determined by the maximum heights on its left and right side.
         */
        const int n = height.size();
        std::vector< int > left_max_height( n, 0 );
        for ( int i = 1; i < n; ++i )
            left_max_height[ i ]
            = std::max( left_max_height[ i - 1 ], height[ i - 1 ] );
        
        int water = 0;
        int right_max = 0;
        for ( int i = n - 1; i >= 1; --i ) {
            int h = std::min( left_max_height[ i ], right_max );
            if ( h > height[ i ] )
                water += h - height[ i ];
            right_max = std::max( right_max, height[ i ] );
        }
        return water;
    }
    /**
     * O( n ) runtime, O( 1 ) space - two pointers scan from both ends
     */
    int trap_impl_2( const std::vector< int > & height ) {
        const int n = height.size();
        int bars = 0;
        int total = 0;
        int L = 0;
        int R = n - 1;
        int h = 0;
        while ( L <= R ) {
            if ( height[ L ] < height[ R ] ) {
                if ( height[ L ] > h ) {
                    total += ( R - L + 1 ) * ( height[ L ] - h );
                    h = height[ L ];
                }
                bars += height[ L ];
                ++L;
            } else {
                if ( height[ R ] > h ) {
                    total += ( R - L + 1 ) * ( height[ R ] - h );
                    h = height[ R ];
                }
                bars += height[ R ];
                --R;
            }
        }
        return total - bars;
    }
    /**
     * O( n ) runtime, O( n ) space - stack
     */
    int trap_impl_3( const std::vector< int > & height ) {
        const int n = height.size();
        std::stack< int > s;
        //Note that the stack holds the index not the height
        s.push( 0 );
        int water = 0;
        for ( int i = 1; i < n; ++i ) {
            if ( h[ i ] > h[ s.top() ] ) {
                int bottom = h[ s.top() ];
                s.pop();
                //need to verify if a few same heights are in the stack
                while ( ! s.empty() && h[ i ] >= h[ s.top() ] ) {
                    water += ( h[ s.top() ] - bottom ) * ( i - s.top() - 1 );
                    bottom = h[ s.top() ];
                    s.pop();
                }
                if ( ! s.empty() )
                    water += ( h[ i ] - bottom ) * ( i - s.top() - 1 );
            }
            s.push( i );
        }
        return water;
    }
};
