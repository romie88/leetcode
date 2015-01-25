//94 Binary Tree Inorder Traversal [ Medium ]
//
//Given a binary tree, return the inorder traversal of its nodes' values.
//
//For example:
//Given binary tree {1,#,2,3},
//   1
//    \
//     2
//    /
//   3
//return [1,3,2].
//
//Note: Recursive solution is trivial, could you do it iteratively?
//
//confused what "{1,#,2,3}" means? > read more on how binary tree is
//serialized on OJ.

//Tags: Tree, Hash Table, Stack

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
    
    std::vector< int > inorderTraversal( TreeNode * root ) {
        std::vector< int > v;
        inorder_traversal_threaded( root, v );
        return v;
    }
    
private:
    
    //straightforward recursive implementation
    void inorder_traversal_recursive(
            TreeNode * root,
            std::vector< int > & v ) {
        
        if ( ! root ) return;
        
        inorder_traversal_recursive( root->left, v );
        v.push_back( root->val );
        inorder_traversal_recursive( root->right, v );
    }
    
    //iterative implementation using a stack explicitly
    void inorder_traversal_stack(
            TreeNode * p,
            std::vector< int > & v ) {
        
        std::stack< TreeNode * > s;
        while ( p || ! s.empty() ) {
            if ( p ) {
                s.push( p );
                p = p->left;
            } else {
                p = s.top();
                s.pop();
                v.push_back( p->val );
                p = p->right;
            }
        }
    }
    
    //iterative implementation using Morris threaded binary tree
    //http://www.liacs.nl/~deutz/DS/september28.pdf
    void inorder_traversal_threaded(
            TreeNode * p,
            std::vector< int > & v ) {

        while ( p ) {
            //if the node pointed by p has NO left child
            //visit it and go to the right child
            //note the right child could point to the "parent"
            //the inorder successor node
            if ( ! p->left ) {
                v.push_back( p->val );
                p = p->right;
            } else {
                //make the node pointed by p the right child of the rightmost
                //node of its left child
                //then go to the left child
                TreeNode * tmp = p->left;
                while ( tmp->right && tmp->right != p )
                    tmp = tmp->right;
                
                if ( ! tmp->right ) {
                    tmp->right = p;
                    p = p->left;//keep going left
                } else {
                    v.push_back( p->val );
                    tmp->right = nullptr;
                    p = p->right;
                }
            }
        }
    }

};
