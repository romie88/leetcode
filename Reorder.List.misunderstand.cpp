//Reorder List
//
//Given a singly linked list L: L0→L1→…→Ln-1→Ln,
//reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
//
//You must do this in-place without altering the nodes' values.
//
//For example,
//Given {1,2,3,4}, reorder it to {1,4,2,3}.

//Tags: Linked List

/*
 * I misread the problem as
 * Reorder list: l0 -> l1 -> l2 -> ... -> ln
 * into l0 -> ln -> l2 -> ln-2 -> l4 -> ln-4 -> ...
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
    void reorderList( ListNode * head ) {
    	
		ListNode * h1 = 0;
		ListNode * h2 = 0;
		splitList( head, h1, h2 );
		h2 = reverseList( h2 );
		merge( h1, h2 );
	}
private:
	ListNode * reverseList( ListNode * head )
	{
		ListNode * p = head;
		ListNode * prev_p = 0;

		while ( p )
		{
			ListNode * p_next = p->next;
			p->next = prev_p;
			prev_p = p;
			p = p_next;
		}

		return prev_p;
	}

	void splitList( ListNode * head,
		            ListNode * & h1,
		            ListNode * & h2 )
	{
		h1 = head;
		h2 = head;
		if ( h1 )
			h2 = h1->next;
		
		ListNode * p = head;
		while ( p )
		{
			ListNode * p_next = p->next;
			if ( p_next )
			{
				p->next = p_next->next;
				if ( p->next )
				{
					p_next->next = p->next->next;
				}
			}

			p = p->next;
		}
	}

	void merge( ListNode * h1, ListNode * h2 )
	{
		while ( h1 && h2 )
		{
			ListNode * h1_next = h1->next;
			ListNode * h2_next = h2->next;

			h1->next = h2;
			h2->next = h1_next;

			h1 = h1_next;
			h2 = h2_next;
		}
	}
};
