//Insertion Sort List
//
//Sort a linked list using insertion sort.

//Tags: Linked List, Sort

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
    ListNode * insertionSortList( ListNode * head ) {
		
		if ( ! head )
			return head;
		
		ListNode * p = head->next;
		head->next = 0;
		while ( p )
		{
			//save p->next
			ListNode * p_next = p->next;
			
			//traverse the sorted part to find a place to insert
			ListNode * q = head;
			ListNode * prev_q = 0;
			while ( q && q->val <= p->val )
			{
				prev_q = q;
				q = q->next;
			}
			
			if ( ! prev_q )
			{
				head = p;
				p->next = q;
			}
			else
			{
				prev_q->next = p;
				p->next = q;
			}
			
			//move to the next node
			p = p_next;
		}

		return head;
    }
};

