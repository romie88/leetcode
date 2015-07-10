/**
 * Algorithms 19 Remove Nth Node From End of List                          Easy
 * 
 * Given a linked list, remove the n-th node from the end of list and return
 * its head.
 * 
 * For example,
 * 
 *    Given linked list: 1->2->3->4->5, and n = 2.
 * 
 *    After removing the second node from the end, the linked list becomes
 *    1->2->3->5.
 * 
 * Note:
 * 
 * Given n will always be valid.
 * Try to do this in one pass.
 * 
 * Tags: Linked List, Two Pointers
 */

#include <stdexcept>

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
    ListNode * removeNthFromEnd( ListNode * head, int n ) {
        
        if ( n <= 0 ) throw std::out_of_range( "n is not positive" );
        
        ListNode dummy_head( 0 );
        dummy_head.next = head;
        
        //move p1 forward n steps first
        ListNode * p1 = &dummy_head;
        while ( p1->next && n ) {
            p1 = p1->next;
            --n;
        }
        if ( n > 0 )
            throw std::out_of_range( "n is larger than the number of nodes" );
        
        ListNode * p2 = &dummy_head;
        while ( p1->next ) {
            p2 = p2->next;
            p1 = p1->next;
        }
        
        ListNode * p_deleted = p2->next;
        if ( p_deleted ) {
            p2->next = p_deleted->next;
            delete p_deleted;
        }
        
        return dummy_head.next;
    }
};

