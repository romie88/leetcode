//Binary Tree Maximum Path Sum 2012-11-07
//
//Given a binary tree, find the maximum path sum.
//
//The path may start and end at any node in the tree.
//
//For example:
//Given the below binary tree,
//
//       1
//      / \
//     2   3
//
//Return 6.

//Tags: Tree, Depth-first Search

#include <algorithm>
#include <limits>

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
    int maxPathSum( TreeNode * root ) {
        
        int max_sum = 0; 
        int max_sum_end_at_root = 0;
        max_path_sum_imp( root,
                          max_sum,
                          max_sum_end_at_root );

        return max_sum;
    }
private:
    void max_path_sum_imp( TreeNode * p,
                           int & max_sum,
                           int & max_sum_end_at_p )
    {
        if ( ! p->left && ! p->right )
        {
            max_sum = max_sum_end_at_p = p->val;
            return;
        }
        
        if ( p->left )
        {
            int left_max_sum = 0;
            int left_max_sum_end_at_p = 0; 
            max_path_sum_imp( p->left,
                              left_max_sum,
                              left_max_sum_end_at_p );
            
            if ( p->right )
            {
                int right_max_sum = 0;
                int right_max_sum_end_at_p = 0;
                if ( p->right )
                max_path_sum_imp( p->right,
                                  right_max_sum,
                                  right_max_sum_end_at_p );
                
                int isolated_max_sum = std::max( left_max_sum, right_max_sum );
                int left_right_max_sum = left_max_sum_end_at_p
                                       + p->val
                                       + right_max_sum_end_at_p;
                max_sum = std::max( isolated_max_sum, left_right_max_sum );
        
                left_max_sum_end_at_p += p->val;
                right_max_sum_end_at_p += p->val;
                
                max_sum_end_at_p = std::max( left_max_sum_end_at_p, right_max_sum_end_at_p );
                max_sum_end_at_p = std::max( max_sum_end_at_p, p->val );
        
                max_sum = std::max( max_sum_end_at_p, max_sum );
            }
            else
            {
                left_max_sum_end_at_p += p->val;
                max_sum_end_at_p = std::max( left_max_sum_end_at_p, p->val );
                max_sum = std::max( left_max_sum, max_sum_end_at_p );
            }
        }
        else//p->right must not be 0
        {
            int right_max_sum = 0;
            int right_max_sum_end_at_p = 0;
            max_path_sum_imp( p->right,
                              right_max_sum,
                              right_max_sum_end_at_p );
            
            right_max_sum_end_at_p += p->val;
            max_sum_end_at_p = std::max( right_max_sum_end_at_p, p->val );
            max_sum = std::max( right_max_sum, max_sum_end_at_p );
        }
    }
};

