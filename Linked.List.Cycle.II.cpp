//Linked List Cycle II
//
//Given a linked list, return the node where the cycle begins.
//If there is no cycle, return null.
//
//Follow up:
//Can you solve it without using extra space?

//Tags: Linked List, Two Pointers

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
    ListNode * detectCycle( ListNode * head ) {
        
		ListNode * slow = head;
		ListNode * fast = head;
		while ( fast )
		{
			slow = slow->next;
			fast = fast->next;
			if ( fast )
				fast = fast->next;
			
			if ( slow == fast )
				break;
		}

		if ( ! fast )
			return 0;

		ListNode * p = head;
		while ( p != slow )
		{
			p = p->next;
			slow = slow->next;
		}
		
		return p;
    }
};
