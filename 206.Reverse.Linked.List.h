/**
 * Algorithms 206 Reverse Linked List                                      Easy
 *
 * Reverse a singly linked list.
 *
 * click to show more hints.
 *
 * Hint:
 *
 * A linked list can be reversed either iteratively or recursively. Could you
 * implement both?
 *
 * Tags: Linked List
 * Similar Problems: (M) Reverse Linked List II, (M) Binary Tree Upside Down
 *                   (E) Palindrome Linked List
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode * reverseList( ListNode * head ) {
        return reverse_list_iterative( head );
    }
private:
    ListNode * reverse_list_iterative( ListNode * head ) {
        ListNode * prev = nullptr;
        ListNode * curr = head;
        while ( curr ) {
            ListNode * next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    ListNode * reverse_list_recursive( ListNode * head ) {
        if ( head == nullptr ) return nullptr;

        ListNode * new_head = reverse_list_recursive( head->next );
        ListNode * tail = head->next;
        if ( tail != nullptr ) {
            tail->next = head;
            head->next = nullptr;
        }
        return new_head != nullptr ? new_head : head;
    }
};