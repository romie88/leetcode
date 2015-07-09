/**
 * Algorithms 11 Container With Most Water                                 Hard
 * 
 * Given n non-negative integers a1, a2, ..., an, where each represents a point
 * at coordinate (i, ai). n vertical lines are drawn such that the two
 * endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together
 * with x-axis forms a container, such that the container contains the most
 * water.
 * 
 * Note: You may not slant the container.
 * 
 * Tags: Array, Two Pointers
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    int maxArea( const std::vector< int > & height ) {
        return max_area_sorting( height );
    }
private:
    /**
     * O( n ) runtime, O( 1 ) space - Two Pointers
     * 
     * Using two pointers to scan from the left and right end.
     * Starts with L = 0 and R = n - 1. So the area( L, R )
     * = std::min( h[ L ], h[ R ] ) * ( R - L ).
     * Without loss of generality assume h[ L ] < h[ R ].
     * Then we already find out the max area formed by taking L = 0 as the
     * left boundary. Thus we can move L from 0 to 1.
     * Let's assume h[ 1 ] < h[ n - 1 ]. Then we immediately know that
     * we find out that the max area formed by taking 1 as the left boundary.
     * And we notice that the area formed by taking 1 as the right boundary
     * is not enumerated and calculated and compared. It is not necessary in
     * this case because the possible left boundary is 0 and area( 0, 1 )
     * < area( 0, n - 1 ) which we calculate before we move from 0 to 1.
     * With this reasoning when our algorithm arrives at L and R we do not
     * need to worry about the areas formed by taking L as the right boundary
     * neither the areas formed by taking R as the left boundary.
     * Now following the above assumption we move from 1 to 2 and let's say
     * h[ 2 ] > h[ n - 1 ] we calculate area( 2, n - 1 ) and move n - 1 to
     * n - 2.
     * Let's say after some iterations we are at L and R and h[ L ] < h[ R ]
     * we calculated area( L, R ) and update max area if it is larger.
     * A quesiton arises here: how about area( L, R' ) where R < R'?
     * Is it possible that area( L, R' ) is max area and we missed it?
     * Let's answer this question. Let L' <= L be the left pointer right before
     * we move from R' to R' - 1. If L' == L then area( L, R' ) is calculated
     * and update max_area if it is larger. If L' < L, h[ L' ] > h[ R' ] and
     * area( L', R' ) has been calculated and update max_area if it is larger.
     * And area( L', R' ) > area( L, R' ).
     * 
     * So far we prove that the algorithm will actually find the max area.
     */
    int max_area_two_pointers( const std::vector< int > & h ) {
        const int n = h.size();
        int L = 0;
        int R = n - 1;
        int max_A = 0;
        while ( L < R ) {
            int A = 0;
            if ( h[ L ] < h[ R ] ) {
                A = h[ L ] * ( R - L );
                ++L;
            } else if ( h[ L ] > h[ R ] ){
                A = h[ R ] * ( R - L );
                --R;
            } else {
                A = h[ L ] * ( R - L );
                ++L;
                --R;
            }
            max_A = std::max( A, max_A );
        }
        return max_A;
    }
    
    /**
     * O( n log n ) runtime, O( n ) space - Sorting and linear scan
     */
    int max_area_sorting( const std::vector< int > & h ) {
        struct Line {
            Line( int h, int i ) : height( h ), index( i ) {}
            bool operator < ( const Line & rhs ) const {
                return height < rhs.height;
            }
            int height;
            int index;
        };
        const int n = h.size();
        if ( n <= 1 ) return 0;
        
        //sort by height
        std::vector< Line > v;
        for ( int i = 0; i < n; ++i )
            v.push_back( Line( h[ i ], i ) );
        std::sort( v.begin(), v.end() );
        
        int max_A = 0;
        int min_i = v[ n - 1 ].index;
        int max_i = v[ n - 1 ].index;
        for ( int i = n - 2; i >= 0; --i ) {
            //max area formed by taking v[ i ].height as the shorter boundary
            min_i = std::min( min_i, v[ i ].index );
            max_i = std::max( max_i, v[ i ].index );
            max_A = std::max( max_A,
                              v[ i ].height * std::max( v[ i ].index - min_i,
                                                        max_i - v[ i ].index ) );
        }
        return max_A;
    }
};
