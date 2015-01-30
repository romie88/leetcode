//109 Convert Sorted List to Binary Search Tree [ Medium ]
//
//Given a singly linked list where elements are sorted in ascending order,
//convert it to a height balanced BST.

//Tags: Depth-first Search, Linked List

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *leftr;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode * sortedListToBST( ListNode * head ) {
     
        int n = 0;
        ListNode * p = head;
        while ( p ) {
            ++n;
            p = p->next;
        }
        return sorted_list_to_bst_impl( head, n );
    }
private:
    TreeNode * sorted_list_to_bst_impl( ListNode * & head, int n ) {
        if ( n <= 0 || ! head ) return nullptr;
        
        TreeNode * left = sorted_list_to_bst_impl( head, n / 2 );
        TreeNode * p    = new TreeNode( head->val );
        head = head->next;
        TreeNode * right = sorted_list_to_bst_impl( head, n - n / 2 - 1 );
        p->left  = left;
        p->right = right;
        
        return p;
    }
};
