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
        
		ListNode * p = head;
		while ( p )
		{
			//save p->enxt
			ListNode * p_next = p->next;
			
			//start from p->next and traverse to the last node
			ListNode * q = p->next;
			ListNode * prev_q = p;
			while ( q && q->next )
			{
				prev_q = q;
				q = q->next;
			}

			if ( q != p->next )
			{
				prev_q->next = q->next;
				p->next = q;
				q->next = p_next;
			}

			p = p_next;
		}
    }
};
