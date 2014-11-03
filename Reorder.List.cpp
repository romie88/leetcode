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
    	
		ListNode * mid = 0;
		splitList( head, mid );
		mid = reverseList( mid );
		merge( head, mid );
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
		            ListNode * & mid )
	{
		ListNode * prev_mid = 0;
		mid = head;
		if ( mid )
		{
			prev_mid = mid;
			mid = mid->next;
		}
		
		ListNode * fast = mid;
		while ( fast )
		{
			prev_mid = mid;
			mid = mid->next;
			fast = fast->next;
			if ( fast )
				fast = fast->next;
		}

		if ( prev_mid )
			prev_mid->next = 0;
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
