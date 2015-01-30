//108 Convert Sorted Array to Binary Search Tree [ Medium ]
//
//Given an array where elements are sorted in ascending order, convert it to
//a height balanced BST.

//Tags: Tree, Depth-first Search

#include <vector>

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode * sortedArrayToBST( std::vector< int > & num ) {
        return sorted_array_to_bst_impl( num, 0, num.size() - 1 );
    }

private:

    TreeNode * sorted_array_to_bst_impl( std::vector< int > & num,
                                         int s, int e ) {
        if ( s > e ) return nullptr;

        int m = s + ( e - s ) / 2;//avoid overflowing of s + e
        TreeNode * p = new TreeNode( num[ m ] );
        p->left  = sorted_array_to_bst_impl( num, s, m - 1 );
        p->right = sorted_array_to_bst_impl( num, m + 1, e );

        return p;
    }

};
