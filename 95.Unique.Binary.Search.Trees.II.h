/**
 * Algorithms 95 Unique Binary Search Trees II                           Medium
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
 * confused what "{1,#,2,3}" means? > read more on how binary tree is
 * serialized on OJ.
 *
 * OJ's Binary Tree Serialization:
 * The serialization of a binary tree follows a level order traversal, where
 * '#' signifies a path terminator where no node exists below.
 *
 * Here's an example:
 *    1
 *   / \
 *  2   3
 *     /
 *    4
 *     \
 *     5
 * The above binary tree is serialized as "{1,2,3,#,#,4,#,#,5}".
 *
 * Tags: Tree, Dynamic Programming
 * Similar Problems: (M) Unique Binary Search Trees,
 *                   (M) Different Ways to Add Parentheses
 */

#include <vector>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    std::vector< TreeNode * > generateTrees( const int n ) {
        return generate_trees( n );
    }
private:
    std::vector< TreeNode * > generate_trees( const int start, const int end ) {
        std::vector< TreeNode * > trees;
        if ( start > end ) {
            trees.push_back( nullptr );
            return trees;
        }

        for ( int i = start; i <= end; ++i ) {
            //change std::vector< TreeNode * > to const std::vector< TreeNode * > &
            //greatly enhanced the running time
            const std::vector< TreeNode * > & left_subtrees
                = generate_trees( start, i - 1 );
            const std::vector< TreeNode * > & right_subtrees
                = generate_trees( i + 1, end );
            for ( int k = 0; k < left_subtrees.size(); ++k ) {
                for ( int j = 0; j < right_subtrees.size(); ++j ) {
                    TreeNode * p = new TreeNode( i );
                    p->left  = left_subtrees[ k ];
                    p->right = right_subtrees[ j ];
                    trees.push_back( p );
                }
            }
        }
        return trees;
    }
    std::vector< TreeNode * > generate_trees( const int n ) {
        return generate_trees( 1, n );
    }
};
