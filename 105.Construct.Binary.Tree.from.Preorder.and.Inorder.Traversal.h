/**
 * Algorithms 105 Construct Binary Tree from Preorder and Inorder Traversal   Medium
 *
 * Given preorder and inorder traversal of a tree, construct the binary tree.
 *
 * Note:
 * You may assume that duplicates do not exist in the tree.
 *
 * Tags: Tree, Array, Depth-first Search
 * Similar Problems: (M) Construct Binary Tree from Inorder and Postorder Traversal
 */

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
    TreeNode * buildTree( const std::vector< int > & preorder,
                          const std::vector< int > & inorder ) {

        if ( preorder.size() != inorder.size() )
            throw std::out_of_range( "preorder and inorder have different sizes" );

        TreeNode * root = build_tree_impl( preorder, 0, preorder.size(),
                                           inorder,  0, inorder.size() );

        return root;
    }
private:
    TreeNode * build_tree_impl( const std::vector< int > & preorder, int s1, int e1,
                                const std::vector< int > & inorder,  int s2, int e2 ) {

        if ( s1 >= e1 ) return nullptr;

        TreeNode * root = new TreeNode( preorder[ s1 ] );

        int i = s2;
        for ( i = s2; i < e2; ++i )
            if ( inorder[ i ] == preorder[ s1 ] )
                break;

        root->left  = build_tree_impl( preorder, s1 + 1, s1 + 1 + ( i - s2 ),
                                       inorder, s2, i );
        root->right = build_tree_impl( preorder, e1 - ( e2 - i - 1 ), e1,
                                       inorder, i + 1, e2 );

        return root;
    }
};

