/**
 * Algorithms 83 Remove Duplicates from Sorted List                        Easy
 *
 * Given a sorted linked list, delete all duplicates such that each element
 * appear only once.
 *
 * For example,
 * Given 1->1->2, return 1->2.
 * Given 1->1->2->3->3, return 1->2->3.
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
        return delete_duplicates_imp4( head );
    }
private:
    ListNode * delete_duplicates_impl1( ListNode * head ) {
        ListNode * p = head;
        while ( p ) {
            while ( p->next && p->next->val == p->val ) {
                ListNode * tmp = p->next;
                p->next = p->next->next;
                delete tmp;
            }
            p = p->next;
        }
        return head;
    }
    ListNode * delete_duplicates_impl2( ListNode * head ) {
        if ( head == nullptr ) return head;
        ListNode * prev = head;
        ListNode * curr = head->next;
        while ( curr ) {
            if ( curr->val == prev->val ) {
                ListNode * tmp = curr;
                curr = curr->next;
                prev->next = curr;
                delete tmp;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
        return head;
    }
    ListNode * delete_duplicates_impl3( ListNode * head ) {
        if ( head == nullptr ) return head;
        ListNode * curr = head;
        while ( curr->next ) {
            if ( curr->next->val == curr->val ) {
                ListNode * tmp = curr->next;
                curr->next = tmp->next;
                delete tmp;
            } else {
                curr = curr->next;
            }
        }
        return head;
    }
    ListNode * delete_duplicates_imp4( ListNode * head ) {
        ListNode * p = head;
        while ( p ) {
            if ( p->next != nullptr && p->val == p->next->val ) {
                ListNode * tmp = p->next;
                p->next = p->next->next;
                delete tmp;
            } else {
                p = p->next;
            }
        }
        return head;
    }
};