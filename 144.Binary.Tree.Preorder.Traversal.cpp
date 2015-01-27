//144 Binary Tree Preorder Traversal [ Medium ]
//
//Given a binary tree, return the preorder traversal of its nodes' values.
//
//For example:
//Given binary tree {1,#,2,3},
//   1
//    \
//     2
//    /
//   3
//return [1,2,3].
//
//Note: Recursive solution is trivial, could you do it iteratively?

//Tags: Tree, Stack

#include <vector>
#include <stack>

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

    std::vector< int > preorderTraversal( TreeNode * root ) {
        std::vector< int > v;
        preorder_traversal_threaded( root, v );
        return v;
    }

private:
    
    //straightforward recursive implementation
    void preorder_traversal_recursive(
            TreeNode * p,
            std::vector< int > & v ) {
        
        if ( ! p ) return;
        
        v.push_back( p->val );
        preorder_traversal_recursive( p->left,  v );
        preorder_traversal_recursive( p->right, v );
    }
    
    //iterative implementation using a stack explicitly
    void preorder_traversal_stack(
            TreeNode * p,
            std::vector< int > & v ) {

        std::stack< TreeNode * > s;
        while ( p || ! s.empty() ) {
            if ( p ) {
                v.push_back( p->val );
                s.push( p );
                p = p->left;
            } else {
                p = s.top();
                s.pop();
                p = p->right;
            }
        }
    }
    
    //iterative implementation using a stack explicitly
    //http://www.geeksforgeeks.org/iterative-preorder-traversal/
    void preorder_traversal_stack2(
            TreeNode * p,
            std::vector< int > & v ) {
        
        if ( ! p ) return;

        std::stack< TreeNode * > s;
        s.push( p );
        while ( ! s.empty() ) {

            p = s.top();
            s.pop();
            v.push_back( p->val );
            
            if ( p->right )
                s.push( p->right );
            if ( p->left )
                s.push( p->left );
        }
    }

    //iterative implementation using Morris threaded binary tree
    //http://www.cnblogs.com/AnnieKim/archive/2013/06/15/morristraversal.html
    void preorder_traversal_threaded(
            TreeNode * p,
            std::vector< int > & v ) {

        while ( p ) {
            if ( ! p->left ) {
                v.push_back( p->val );
                p = p->right;
            } else {
                TreeNode * tmp = p->left;
                while ( tmp->right && tmp->right != p )
                    tmp = tmp->right;
                
                if ( ! tmp->right ) {
                    tmp->right = p;
                    //different from inorder
                    v.push_back( p->val );
                    p = p->left;
                } else {
                    tmp->right = nullptr;
                    p = p->right;
                }
            }
        }
    }
    
};
