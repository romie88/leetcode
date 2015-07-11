/**
 * Algorithms 21 Merge Two Sorted Lists                                   Easy
 *
 * Merge two sorted linked lists and return it as a new list. The new list
 * should be made by splicing together the nodes of the first two lists.
 *
 * Tags: Linked List
 * Similar Problems: (H) Merge k Sorted Lists, (E) Merge Sorted Array
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
    ListNode * mergeTwoLists( ListNode * l1, ListNode * l2 ) {
        ListNode dummy_head( 0 );
        ListNode * p = &dummy_head;
        while ( l1 && l2 ) {
            if ( l1->val <= l2->val ) {
                p->next = l1;
                l1 = l1->next;
            } else {
                p->next = l2;
                l2 = l2->next;
            }
            p = p->next;
        }
        if ( l1 ) p->next = l1;
        if ( l2 ) p->next = l2;
        return dummy_head.next;
    }
};
