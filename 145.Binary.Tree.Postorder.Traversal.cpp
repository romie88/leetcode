//145 Binary Tree Postorder Traversal [ Hard ]
//
//Given a binary tree, return the postorder traversal of its nodes' values.
//
//For example:
//Given binary tree {1,#,2,3},
//   1
//    \
//     2
//    /
//   3
//return [3,2,1].
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

    std::vector< int > postorderTraversal( TreeNode * root ) {
        std::vector< int > v;
        postorder_traversal_recursive( root, v );
        return v;
    }

private:
    
    //straightforward recursive implementation
    void postorder_traversal_recursive(
            TreeNode * p,
            std::vector< int > & v ) {
        
        if ( ! p ) return;
        
        postorder_traversal_recursive( p->left,  v );
        postorder_traversal_recursive( p->right, v );
        v.push_back( p->val );
    }
    
    //iterative implementation using two stacks explicitly
    //http://www.geeksforgeeks.org/iterative-postorder-traversal/
    //The idea is that let's observe the output of a postorder traversal
    //for example
    //        1
    //       / \
    //      2   3
    //     / \ / \
    //    4  5 6  7
    //4 5 2 6 7 3 1
    //look at the reverse order of it
    //1 3 7 6 2 5 4
    //this looks very similar to the preorder traversal output
    //except it visits right subtree ahead of left subtree
    void postorder_traversal_two_stacks(
            TreeNode * p,
            std::vector< int > & v ) {
        
        std::stack< TreeNode * > s1;
        std::stack< TreeNode * > s2;//used for the VRL preorder traversal
        while ( p || ! s2.empty() ) {
            if ( p ) {
                s1.push( p );
                s2.push( p );
                p = p->right;
            } else {
                p = s2.top();
                s2.pop();
                p = p->left;
            }
        }

        //finally pop everything out of s1
        while ( ! s1.empty() ) {
            v.push_back( s1.top()->val );
            s1.pop();
        }
    }
    
    //iterative implementation using a stack explicitly
    void postorder_traversal_one_stack(
            TreeNode * p,
            std::vector< int > & v ) {
        
        std::stack< TreeNode * > s;
        TreeNode * prev = nullptr;
        while ( p || ! s.empty() ) {
            if ( p ) {
                s.push( p );
                p = p->left;
            } else {
                p = s.top();
                //the key trick here is when to pop the pointer
                //to the node of the stack
                //if the right child is nullptr or it has previously
                //been visited then it is right to visit the node
                //pointed by p
                //otherwise proceed to the right subtree
                if ( ! p->right || prev == p->right ) {
                    s.pop();
                    v.push_back( p->val );
                    prev = p;
                    p = nullptr;
                } else {
                    p = p->right;
                }
            }
        }
    }

    //iterative implementation using Morris threaded binary tree
    //http://www.cnblogs.com/AnnieKim/archive/2013/06/15/morristraversal.html
    void postorder_traversal_threaded(
            TreeNode * p,
            std::vector< int > & v ) {
        
        TreeNode dump( 0 );
        dump.left = p;
        p = &dump;
        while ( p ) {
            if ( ! p->left ) {
                p = p->right;
            } else {
                TreeNode * tmp = p->left;
                while ( tmp->right && tmp->right != p )
                    tmp = tmp->right;
                
                if ( ! tmp->right ) {
                    tmp->right = p;
                    p = p->left;
                } else {
                    //output the nodes starting from the left child
                    //of the current node pointed by p to this tmp
                    //(predecessor) in reverse order
                    reverse( p->left, tmp );
                    TreeNode * tmp2 = tmp;
                    while ( tmp2 != p->left ) {
                        v.push_back( tmp2->val );
                        tmp2 = tmp2->right;
                    }
                    v.push_back( tmp2->val );
                    reverse( tmp, p->left );
                    //note this must happen after the reverse output
                    tmp->right = nullptr;
                    
                    p = p->right;
                }
            }
        }
    }
    
    void reverse( TreeNode * p1, TreeNode * p2 ) {

        if ( p1 == p2 ) return;

        TreeNode * tmp = p1->right;
        while ( tmp != p2 ) {
            TreeNode * tmp2 = tmp->right;
            tmp->right = p1;
            p1 = tmp;
            tmp = tmp2;
        }
        tmp->right = p1;
    }
};
