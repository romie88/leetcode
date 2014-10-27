//Add Two Numbers
//
//You are given two linked lists representing two non-negative numbers.
//The digits are stored in reverse order and each of their nodes contain
//a single digit. Add the two numbers and return it as a linked list.
//
//Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
//Output: 7 -> 0 -> 8

//Tags: Linked List, Math

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
    ListNode *addTwoNumbers( ListNode * l1, ListNode * l2 ) {
		
		ListNode * result = 0;
		ListNode * current = 0;
		int carry = 0;
		while ( l1 || l2 )
		{
			int sum = carry;
			if ( l1 )
			{
				sum += l1->val;
				l1 = l1->next;
			}
			if ( l2 )
			{
				sum += l2->val;
				l2 = l2->next;
			}
			carry = sum / 10;
			ListNode * p = new ListNode( sum % 10 );
			if ( ! result )
			{
				result = p;
				current = p;
			}
			else
			{
				current->next = p;
				current = p;
			}
		}
		if ( carry )
		{
			current->next = new ListNode( carry );
		}
       	
		return result;
    }
};
