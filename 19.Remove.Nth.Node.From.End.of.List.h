//19 Remove Nth Node From End of List [ Easy ]
//
//Given a linked list, remove the nth node from the end of list and return
//its head.
//
//For example,
//
//   Given linked list: 1->2->3->4->5, and n = 2.
//
//   After removing the second node from the end, the linked list becomes 1->2->3->5.
//
//Note:
//Given n will always be valid.
//Try to do this in one pass.
//
//Tags: Linked List, Two Pointers

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
        
        if ( n <= 0 ) throw std::invalid_argument( "n must be positive" );
        
        //need to find the node ahead of the Nth node from the end
        ListNode * p1 = head;
        ++n;
        while ( p1 && n ) {
            p1 = p1->next;
            --n;
        }

        if ( p1 == nullptr && n > 1 )
            throw std::invalid_argument( "k is longer than the list length" );

        //remove head
        if ( p1 == nullptr && n == 1 ) {
            ListNode * tmp = head;
            head = head->next;
            delete tmp;
            return head;
        }
        
        ListNode * p2 = head;
        while ( p1 ) {
            p1 = p1->next;
            p2 = p2->next;
        }

        ListNode * tmp = p2->next;
        p2->next = p2->next ? p2->next->next : nullptr;
        
        return head;
    }
};

