/**
 * Algorithms 61 Rotate List                                             Medium
 * 
 * Given a list, rotate the list to the right by k places, where k is
 * non-negative.
 * 
 * For example:
 * Given 1->2->3->4->5->NULL and k = 2,
 * return 4->5->1->2->3->NULL.
 * 
 * Tags: Linked List, Two Pointers
 * Similar Problems: (E) Rotate Array
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
    ListNode * rotateRight( ListNode * head, int k ) {
        if ( head == nullptr || k == 0 ) return head;
        
        ListNode * p1 = head;
        ListNode * p2 = head;
        int len = 0;
        while ( p2 && len < k ) {
            p2 = p2->next;
            ++len;
        }
        if ( p2 == nullptr ) {
            k %= len;
            if ( k == 0 ) return head;
            p2 = head;
            while ( p2 && k > 0 ) {
                p2 = p2->next;
                --k;
            }
        }
        while ( p2->next ) {
            p1 = p1->next;
            p2 = p2->next;
        }
        ListNode * old_head = head;
        head = p1->next;
        p2->next = old_head;
        p1->next = nullptr;
        
        return head;
    }
};
