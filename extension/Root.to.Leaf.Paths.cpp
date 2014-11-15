//Root to Leaf Paths
//
//Derived from leetcode Sum Root to Leaf Numbers problem.

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
    void rootToLeafPaths( TreeNode * root,
                         std::vector< std::vector< int > > & paths ) {
        if ( ! root )
            return;
        
        std::vector< int > one_path;
        root_to_leaf_paths( root, paths, one_path );
    }
private:
    void root_to_leaf_paths( TreeNode * p,
                             std::vector< std::vector< int > > & paths,
                             std::vector< int > & one_path )
    {
        one_path.push_back( p->val );
        
        //p is a leaf
        if ( ! p->left && ! p->right )
        {
            paths.push_back( one_path );
            return;
        }
        
        if ( p->left )
        {
            root_to_leaf_paths( p->left, paths, one_path );
            one_path.pop_back();
        }

        if ( p->right )
        {
            root_to_leaf_paths( p->right, paths, one_path );
            one_path.pop_back();
        }
    }
};
