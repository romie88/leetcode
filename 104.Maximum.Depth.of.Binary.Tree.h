//104 Maximum Depth of Binary Tree [ Easy ]
//
//Given a binary tree, find its maximum depth.
//
//The maximum depth is the number of nodes along the longest path from the
//root node down to the farthest leaf node.

//Tags: Tree, Depth-first Search

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
    int maxDepth( TreeNode * root ) {
        if ( ! root ) return 0;

        return 1 + std::max( maxDepth( root->left ), maxDepth( root->right ) );
    }
};

