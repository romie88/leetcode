/**
 * 86 Partition List                                                     Medium
 *
 * Given a linked list and a value x, partition it such that all nodes less
 * than x come before nodes greater than or equal to x.
 *
 * You should preserve the original relative order of the nodes in each of the
 * two partitions.
 *
 * For example,
 * Given 1->4->3->2->5->2 and x = 3,
 * return 1->2->2->4->3->5.
 *
 * Tags: Linked List, Two Pointers
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
    ListNode * partition( ListNode * head, int x ) {
        ListNode dummy1( 0 );
        ListNode dummy2( 0 );
        ListNode * p1 = &dummy1;
        ListNode * p2 = &dummy2;
        ListNode * p = head;
        while ( p ) {
            if ( p->val < x ) {
                p1->next = p;
                p1 = p;
            } else {
                p2->next = p;
                p2 = p;
            }
            p = p->next;
        }
        p2->next = nullptr;
        p1->next = dummy2.next;
        return dummy1.next;
    }
};
