/**
 * Algorithms 92 Reverse Linked List II                                  Medium
 * 
 * Reverse a linked list from position m to n. Do it in-place and in one-pass.
 * 
 * For example:
 * Given 1->2->3->4->5->NULL, m = 2 and n = 4,
 * 
 * return 1->4->3->2->5->NULL.
 * 
 * Note:
 * Given m, n satisfy the following condition:
 * 1 ≤ m ≤ n ≤ length of list.
 * 
 * Tags: Linked List
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
    ListNode * reverseBetween( ListNode * head, int m, int n ) {
        ListNode dummy_head( 0 );
        dummy_head.next = head;
        ListNode * prev = &dummy_head;
        ListNode * curr = head;
        int m_copy = m;
        while ( curr && --m ) {
            prev = curr;
            curr = curr->next;
        }
        
        ListNode * prev2 = nullptr;
        ListNode * saved_curr = curr;
        while ( curr && n >= m_copy ) {
            ListNode * curr_next = curr->next;
            curr->next = prev2;
            prev2 = curr;
            curr = curr_next;
            --n;
        }
        
        prev->next = prev2;
        saved_curr->next = curr;
        
        return dummy_head.next;
    }
};
