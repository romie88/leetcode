//110 Balanced Binary Tree [ Easy ]
//
//Given a binary tree, determine if it is height-balanced.
//
//For this problem, a height-balanced binary tree is defined as a binary tree
//in which the depth of the two subtrees of every node never differ by more
//than 1.

//Tags: Tree, Depth-first Search

#include <cmath>
#include <algorithm>

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
    bool isBalanced( TreeNode * root ) {
        int h;
        return is_balanced_impl( root, h );
    }
private:
    bool is_balanced_impl( TreeNode * p, int & h ) {
        if ( ! p ) {
            h = 0;
            return true;
        }

        int left_h;
        int right_h;
        bool left_balanced  = is_balanced_impl( p->left, left_h );
        bool right_balanced = is_balanced_impl( p->right, right_h );
        h = 1 + std::max( left_h, right_h );
        return left_balanced && right_balanced
            && std::abs( left_h - right_h ) <= 1;
    }
};
