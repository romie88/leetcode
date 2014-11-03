//Sort List
//
//Sort a linked list in O(n log n) time using constant space complexity.

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
    ListNode * sortList( ListNode * head ) {
		return mergeSort( head );
    }
private:

	ListNode * splitList( ListNode * head )
	{
		ListNode * prev_mid = 0;
		ListNode * mid  = head;
		ListNode * fast = head;
		while ( fast && fast->next )
		{
			prev_mid = mid;
			mid = mid->next;
			fast = fast->next;
			fast = fast->next;
		}
		if ( mid == head )
		{
			mid = 0;
		}
		else
		{
			prev_mid->next = 0;
		}

		return mid;
	}

	ListNode * merge( ListNode * h1, ListNode * h2 )
	{
		ListNode * head = 0;
		ListNode * current = 0;
		while ( h1 && h2 )
		{
			if ( h1->val <= h2->val )
			{
				if ( ! head )
				{
					head = h1;
					current = h1;
				}
				else
				{
					current->next = h1;
					current = current->next;
				}
				h1 = h1->next;
			}
			else
			{
				if ( ! head )
				{
					head = h2;
					current = h2;
				}
				else
				{
					current->next = h2;
					current = current->next;
				}
				h2 = h2->next;
			}
		}
		if ( h1 )
		{
			current->next = h1;
		}
		if ( h2 )
		{
			current->next = h2;
		}

		return head;
	}

	ListNode * mergeSort( ListNode * head )
	{
		if ( ! head || ! head->next )
			return head;
		
		ListNode * mid = splitList( head );
		ListNode * h1 = mergeSort( head );
		ListNode * h2 = mergeSort( mid );
		return merge( h1, h2 );
	}
};
