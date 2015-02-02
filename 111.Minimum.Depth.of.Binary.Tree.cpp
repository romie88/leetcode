//111 Minimum Depth of Binary Tree [ Easy ]
//
//Given a binary tree, find its minimum depth.
//
//The minimum depth is the number of nodes along the shortest path from the
//root node down to the nearest leaf node.
//
//Tags: Tree, Depth-first Search

#include <algorithm>
#include <queue>

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
    int minDepth( TreeNode * root ) {
        return min_depth_impl_bfs( root );
    }
private:

    int min_depth_impl_1( TreeNode * root ) {
        if ( ! root ) return 0;
        
        int left_min_depth = -1;
        if ( root->left )
            left_min_depth = min_depth_impl_1( root->left );
        
        int right_min_depth = -1;
        if ( root->right )
            right_min_depth = min_depth_impl_1( root->right );

        if ( left_min_depth > -1 ) {
            if ( right_min_depth > -1 ) {
                return 1 + std::min( left_min_depth, right_min_depth );
            } else {
                return 1 + left_min_depth;
            }
        } else {
            if ( right_min_depth > -1 ) {
                return 1 + right_min_depth;
            } else {
                return 1;
            }
        }
    }

    int min_depth_impl_2( TreeNode * root ) {
        if ( ! root ) return 0;

        if ( ! root->left ) return 1 + min_depth_impl_2( root->right );
        if ( ! root->right ) return 1 + min_depth_impl_2( root->left );
        
        return 1 + std::min( min_depth_impl_2( root->left ),
                             min_depth_impl_2( root->right ) );
    }

    int min_depth_impl_bfs( TreeNode * root ) {
        
        if ( ! root ) return 0;
        
        std::queue< TreeNode * > q;
        q.push( root );
        int depth = 1;
        TreeNode * right_most = root;
        while ( ! q.empty() ) {
            TreeNode * p = q.front();
            q.pop();
            if ( ! p->left && ! p->right )
                break;
            if ( p->left  ) q.push( p->left  );
            if ( p->right ) q.push( p->right );
            if ( p == right_most ) {
                ++depth;
                right_most = p->right ? p->right : p->left;
            }
        }

        return depth;
    }
};
