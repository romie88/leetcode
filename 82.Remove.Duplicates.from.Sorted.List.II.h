/**
 * Algorithms 82 Remove Duplicates from Sorted List II                   Medium
 *
 * Given a sorted linked list, delete all nodes that have duplicate numbers,
 * leaving only distinct numbers from the original list.
 *
 * For example,
 * Given 1->2->3->3->4->4->5, return 1->2->5.
 * Given 1->1->1->2->3, return 2->3.
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
    ListNode * deleteDuplicates( ListNode * head ) {
        return delete_duplicates_impl3( head );
    }
private:
    ListNode * delete_duplicates_impl1( ListNode * head ) {
        ListNode dummy_head( 0 );
        dummy_head.next = head;
        ListNode * prev = &dummy_head;
        ListNode * curr = head;
        while ( curr ) {
            bool any_duplicates = false;
            while ( curr->next && curr->val == curr->next->val ) {
                any_duplicates = true;
                ListNode * tmp = curr;
                curr = curr->next;
                delete tmp;
            }
            if ( any_duplicates ) {
                prev->next = curr->next;
                delete curr;
                curr = prev->next;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
        return dummy_head.next;
    }
    ListNode * delete_duplicates_impl2( ListNode * head ) {
        ListNode dummy_head( 0 );
        dummy_head.next = head;
        ListNode * prev = &dummy_head;
        ListNode * curr = head;
        bool any_duplicates = false;
        while ( curr ) {
            if ( curr->next && curr->val == curr->next->val ) {
                any_duplicates = true;
                ListNode * tmp = curr;
                curr = curr->next;
                delete tmp;
            } else if ( any_duplicates ) {
                any_duplicates = false;
                prev->next = curr->next;
                delete curr;
                curr = prev->next;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
        return dummy_head.next;
    }
    ListNode * delete_duplicates_impl3( ListNode * head ) {
        ListNode dummy_head( 0 );
        dummy_head.next = head;
        ListNode * p = &dummy_head;
        while ( p->next ) {
            ListNode * q = p->next;
            while ( q->next && q->next->val == q->val ) {
                ListNode * tmp = q;
                q = q->next;
                delete tmp;
            }
            if ( q != p->next ) {
                p->next = q->next;
                delete q;
            } else {
                p = p->next;
            }
        }
        return dummy_head.next;
    }
};