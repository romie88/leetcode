/**
 * Algorithms 223 Rectangle Area                                           Easy
 * 
 * Find the total area covered by two rectilinear rectangles in a 2D plane.
 * 
 * Each rectangle is defined by its bottom left corner and top right corner as
 * shown in the figure.
 *                 ^ y
 *                 |     (C,D):(3,4)
 *      -----------------------
 *      |          |          |
 *      |          |          |
 *      |          |          |                   (G,H):(9,2)
 *      |          |----------|-------------------------
 *      |          |          |                        |
 *      |   O(0,0) |          |                        |
 *      -------------------------------------------------------> x
 * (A,B):(-3,0)    |                                   |
 *                 |                                   |
 *                 -------------------------------------
 *            (E,F):(0,-1)
 *
 * Assume that the total area is never beyond the maximum possible value of int.
 * 
 * Credits:
 * Special thanks to @mithmatt for adding this problem, creating the above image and all test cases.
 *
 * Tags: Math
 */

class Solution {
public:
    int computeArea( int A, int B, int C, int D, int E, int F, int G, int H ) {
        return ( C - A ) * ( D - B )
             - overlapping_area( A, B, C, D, E, F, G, H )
             + ( G - E ) * ( H - F );
    }
private:
    int overlapping_area( int A, int B, int C, int D, int E, int F, int G, int H ) {
        int X1 = std::max( A, E );
        int X2 = std::min( C, G );
        int Y1 = std::max( B, F );
        int Y2 = std::min( D, H );
        if ( X1 >= X2 || Y1 >= Y2 ) return 0;
        else return ( X2 - X1 ) * ( Y2 - Y1 );
    }
};
