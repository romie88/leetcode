/**
 * Algorithms 24 Swap Nodes in Pairs                                    Medium
 * 
 * Given a linked list, swap every two adjacent nodes and return its head.
 * 
 * For example,
 * Given 1->2->3->4, you should return the list as 2->1->4->3.
 * 
 * Your algorithm should use only constant space. You may not modify the
 * values in the list, only nodes itself can be changed.
 *
 * Tags: Linked List
 * Similar Problems: (H) Reverse Nodes in k-Group
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
    ListNode * swapPairs( ListNode * head ) {
        ListNode dummy_head( 0 );
        dummy_head.next = head;
        ListNode * p = &dummy_head;
        ListNode * q = p->next;
        while ( q && q->next ) {
            ListNode * tmp = q->next->next;
            p->next = q->next;
            q->next->next = q;
            q->next = tmp;
            p = q;
            q = tmp;
        }
        return dummy_head.next;
    }
};
