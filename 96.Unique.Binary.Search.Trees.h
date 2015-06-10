/**
 * Algorithms 96 Unique Binary Search Trees                              Medium
 * 
 * Given n, how many structurally unique BST's (binary search trees) that store
 * values 1...n?
 * 
 * For example,
 * Given n = 3, there are a total of 5 unique BST's.
 * 
 *    1         3     3      2      1
 *     \       /     /      / \      \
 *      3     2     1      1   3      2
 *     /     /       \                 \
 *    2     1         2                 3
 * 
 * Tags: Tree, Dynamic Programming
 */

class Solution {
public:
    int numTrees( int n ) {
        return num_trees( n );
    }
private:
    /**
     * O( n^2 ) runtime, O( n ) space
     * C_0 = 1, C_(n+1) = C_0 * C_n + C_1 * C_(n-1) + ... + C_n * C_0
     * This is one of the definitions of Catalan Number.
     * If we use the formula of Catalan Number to calculate it directly
     * O( n ) runtime, O( 1 ) space
     */
    int num_trees( int n ) {
        std::vector< int > n_trees( n + 1 , 0 );
        n_trees[ 0 ] = 1;
        n_trees[ 1 ] = 1;
        for ( int i = 2; i <= n; ++i ) {
            for ( int j = 0; j < i; ++j )
                n_trees[ i ] += n_trees[ j ] * n_trees[ i - 1 - j ];
        }
        return n_trees[ n ];
    }
};
