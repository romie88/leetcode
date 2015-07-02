/**
 * Algorithms 230 Kth Smallest Element in a BST                          Medium
 * 
 * Given a binary search tree, write a function kthSmallest to find the kth
 * smallest element in it.
 * 
 * Note: 
 * You may assume k is always valid, 1 <= k <= BST's total elements.
 * 
 * Follow up:
 * 
 * What if the BST is modified (insert/delete operations) often and you need to
 * find the kth smallest frequently? How would you optimize the kthSmallest
 * routine?
 * 
 * Show Hint
 * 
 * 1. Try to utilize the property of a BST.
 * 2. What if you could modify the BST node's structure?
 * 3. The optimal runtime complexity is O(height of BST).
 * 
 * Credits:
 * 
 * Special thanks to @ts for adding this problem and creating all test cases.
 * 
 * Tags: 
 */

#include <stdexcept>
#include <stack>

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
    int kthSmallest( TreeNode * root, int k ) {
        return kth_smallest_iterative( root, k );
    }
private:
    int kth_smallest_recursive( TreeNode * root, int k ) {
        if ( k <= 0 ) throw std::out_of_range( "k <= 0" );
        
        TreeNode * p   = nullptr;
        int        num = 0;
        inorder_traversal( root, k, num, p );
        
        if ( p == nullptr )
            throw std::out_of_range( "k > total number of nodes" );
        
        return p->val;
    }
    void inorder_traversal( TreeNode * p, int k,
                            int & num, TreeNode * & result ) {
        if ( p == nullptr ) {
            num = 0;
            result = nullptr;
            return;
        }
        
        int left_n;
        inorder_traversal( p->left, k, left_n, result );
        if ( result != nullptr ) {
            return;
        } else if ( left_n + 1 == k ) {
            result = p;
        } else {
            int right_n;
            inorder_traversal( p->right, k - left_n - 1, right_n, result );
            num = left_n + 1 + right_n;
        }
    }
    
    /**
     * Another recursive implementation
     */
    int kth_smallest_recursive_2( TreeNode * root, int k ) {
        int count = k;
        TreeNode * result = nullptr;
        inorder_traversal_2( root, count, result );
        if ( result == nullptr ) throw std::out_of_range( "k is out of range" );
        return result->val;
    }
    void inorder_traversal_2( TreeNode * p, int & count, TreeNode * & result ) {
        if ( p == nullptr ) return;
        inorder_traversal_2( p->left, count, result );
        if ( count < 1 ) return;
        else if ( count == 1 ) {
            --count;
            result = p;
        } else {
            --count;
            inorder_traversal_2( p->right, count, result );
        }
    }
    
    /**
     * Iterative implementation
     */
    int kth_smallest_iterative( TreeNode * root, int k ) {
        if ( root == nullptr || k <= 0 )
            throw std::out_of_range( "root is nullptr or k <= 0" );
        
        std::stack< TreeNode * > s;
        TreeNode * p = root;
        int count = 0;
        while ( p || ! s.empty() ) {
            if ( p == nullptr ) {
                p = s.top();
                s.pop();
                ++count;
                if ( count == k )
                    break;
                
                p = p->right;
            } else {
                s.push( p );
                p = p->left;
            }
        }
        
        if ( count == k ) return p->val;
        else throw std::out_of_range( "k is out of range" );
    }
};
