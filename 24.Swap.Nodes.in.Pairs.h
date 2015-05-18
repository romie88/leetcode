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
        ListNode * p = &dummy_head;
        p->next = head;
        ListNode * q1 = head;
        while ( q1 && q1->next ) {
            ListNode * tmp = q1->next->next;
            p->next = q1->next;
            q1->next->next = q1;
            q1->next = tmp;
            p = q1;
            q1 = tmp;
        }
        return dummy_head.next;
    }
};
