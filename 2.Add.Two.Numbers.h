/**
 * Algorithms 2 Add Two Numbers                                         Medium
 * 
 * You are given two linked lists representing two non-negative numbers.
 * The digits are stored in reverse order and each of their nodes contain
 * a single digit. Add the two numbers and return it as a linked list.
 * 
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 * 
 * Tags: Linked List, Math
 * Similar Problems: (M) Multiply Strings, (E) Add Binary
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
    ListNode * addTwoNumbers( ListNode * l1, ListNode * l2 ) {
		
		ListNode dummy_head( 0 );
		ListNode * p = &dummy_head;
		int carry = 0;
		while ( l1 || l2 ) {
			int sum = carry
                    + ( l1 ? l1->val : 0 )
                    + ( l2 ? l2->val : 0 );
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
            carry = sum / 10;
            p->next = new ListNode( sum % 10 );
            p = p->next;
		}
		if ( carry )
			p->next = new ListNode( carry );
       	
		return dummy_head.next;
    }
};
