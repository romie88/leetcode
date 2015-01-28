//106 Construct Binary Tree from Inorder and Postorder Traversal [ Medium ]
//2012-09-30 Medium
//
//Given inorder and postorder traversal of a tree, construct the binary tree.
//
//Note:
//You may assume that duplicates do not exist in the tree.

//Tags: Tree, Array, Depth-first Search

#include <vector>
#include <stdexcept>

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
    TreeNode * buildTree( const std::vector< int > & inorder, 
                          const std::vector< int > & postorder ) {
        
        if ( inorder.size() != postorder.size() )
            throw std::out_of_range( "inorder and postorder have different size!" );

        return build_tree_impl( inorder,   0, inorder.size(),
                                postorder, 0, postorder.size() );
    }
private:
    TreeNode * build_tree_impl( const std::vector< int > & inorder,   int s1, int e1,
                                const std::vector< int > & postorder, int s2, int e2 ) {
        
        if ( s1 >= e1 ) return nullptr;

        TreeNode * root = new TreeNode( postorder[ e2 - 1 ] );
        int i = s1;
        for ( i = s1; i < e1; ++i )
            if ( inorder[ i ] == postorder[ e2 - 1 ] )
                break;
        
        root->left  = build_tree_impl( inorder,   s1, i,
                                       postorder, s2, s2 + i - s1 );
        root->right = build_tree_impl( inorder,   i + 1, e1,
                                       postorder, e2 - ( e1 - i ), e2 - 1 );
        
        return root;
    }
};

