/**
 * Algorithms 113 Path Sum II                                            Medium
 * 
 * Given a binary tree and a sum, find all root-to-leaf paths where each path's
 * sum equals the given sum.
 * 
 * For example:
 * Given the below binary tree and sum = 22,
 *               5
 *              / \
 *             4   8
 *            /   / \
 *           11  13  4
 *          /  \    / \
 *         7    2  5   1
 * return
 * [
 *    [5,4,11,2],
 *    [5,8,4,5]
 * ]
 * 
 * Tags: Tree, Depth-first Search
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
    std::vector< std::vector< int > > pathSum( TreeNode * root, int sum ) {
        std::vector< std::vector< int > > all_paths;
        std::vector< int > path;
        path_sum_impl( root, sum, path, all_paths );
        return all_paths;
    }
private:
    void path_sum_impl( const TreeNode                    * p,
                        const int                           sum,
                        std::vector< int >                & path,
                        std::vector< std::vector< int > > & all_paths ) {
        if ( p == nullptr ) return;
        
        path.push_back( p->val );
        
        if ( p->left == nullptr && p->right == nullptr && p->val == sum ) {
            all_paths.push_back( path );
        } else {
            path_sum_impl( p->left, sum - p->val, path, all_paths );
            path_sum_impl( p->right, sum - p->val, path, all_paths );
        }
        
        path.pop_back();
    }
};
