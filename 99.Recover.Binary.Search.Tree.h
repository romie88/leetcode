/**
 * Algorithms 99 Recover Binary Search Tree                                Hard
 * 
 * Two elements of a binary search tree (BST) are swapped by mistake.
 * 
 * Recover the tree without changing its structure.
 * 
 * Note:
 * A solution using O(n) space is pretty straight forward. Could you devise a
 * constant space solution?
 *
 * confused what "{1,#,2,3}" means? > read more on how binary tree is
 * serialized on OJ.
 * 
 * OJ's Binary Tree Serialization:
 * The serialization of a binary tree follows a level order traversal, where
 * '#' signifies a path terminator where no node exists below.
 * 
 * Here's an example:
 *    1
 *   / \
 *  2   3
 *     /
 *    4
 *     \
 *     5
 * The above binary tree is serialized as "{1,2,3,#,#,4,#,#,5}".
 * 
 * Tags:
 */

#include <algorithm>

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
    void recoverTree( TreeNode * root ) {
        recover_tree_threaded( root );
    }
private:
    /**
     * O( n log n ) runtime, O( n ) space
     * Inorder traverse the whole BST and record all the node pointers and all their
     * corresponding values.
     * The values are out of order. Sort the values and re-assign them to the
     * corresponding nodes.
     * This can solve the general problem with many elements are out of order.
     * For this problem we might not involve sort but only linear scan to find
     * the reversed value pairs.
     *
     * Implementation is omitted.
     */
    
    /**
     * O( n ) runtime, O( log n ) stack space
     * Inorder traversal by recursion and prev TreeNode *.
     */
    void recover_tree_recursive_impl( TreeNode *   p,
                                      TreeNode * & prev,
                                      TreeNode * & p1,
                                      TreeNode * & p2 ) {
        if ( p == nullptr ) return;
        
        recover_tree_recursive_impl( p->left, prev, p1, p2 );
        if ( prev != nullptr && prev->val > p->val ) {
            if ( p1 == nullptr ) {
                p1 = prev;
                p2 = p;
            } else {
                p2 = p;
                return;//found two reversed pairs
            }
        }
        prev = p;
        recover_tree_recursive_impl( p->right, prev, p1, p2 );
    }
    void recover_tree_recursive( TreeNode * p ) {
        TreeNode * prev = nullptr;
        TreeNode * p1   = nullptr;
        TreeNode * p2   = nullptr;
        recover_tree_recursive_impl( p, prev, p1, p2 );
        std::swap( p1->val, p2->val );
    }
    
    /**
     * O( n ) runtime, O( 1 ) space
     * Morris threaded BST inorder traversal
     */
    void recover_tree_threaded_impl( TreeNode *   p,
                                     TreeNode * & p1,
                                     TreeNode * & p2 ) {
        TreeNode * prev = nullptr;
        while ( p ) {
            if ( p->left == nullptr ) {
                //process p
                check_reversed_pair( prev, p, p1, p2 );
                p = p->right;
            } else {
                TreeNode * tmp = p->left;
                while ( tmp->right && tmp->right != p )
                    tmp = tmp->right;
                
                if ( tmp->right == nullptr ) {
                    tmp->right = p;
                    p = p->left;
                } else {
                    tmp->right = nullptr;
                    //process p
                    check_reversed_pair( prev, p, p1, p2 );
                    p = p->right;
                }
            }
        }
    }
    void check_reversed_pair( TreeNode * & prev,
                              TreeNode *   p,
                              TreeNode * & p1,
                              TreeNode * & p2 ) {
        if ( prev != nullptr && prev->val > p->val ) {
            if ( p1 == nullptr ) {
                p1 = prev;
                p2 = p;
            } else {
                p2 = p;
                //cannot return here because the BST needs to be restored
            }
        }
        prev = p;
    }
    void recover_tree_threaded( TreeNode * p ) {
        TreeNode * p1 = nullptr;
        TreeNode * p2 = nullptr;
        recover_tree_threaded_impl( p, p1, p2 );
        std::swap( p1->val, p2->val );
    }
};

