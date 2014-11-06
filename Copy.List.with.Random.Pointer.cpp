//Copy List with Random Pointer
//
//A linked list is given such that each node contains an additional random
//pointer which could point to any node in the list or null.
//
//Return a deep copy of the list.

//Tags:

/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
#include <unordered_map>
#include <utility>

class Solution {
public:
    RandomListNode * copyRandomList( RandomListNode * head ) {
		
		//a map from each origin node pointer to the copied node pointer
		unordered_map< RandomListNode *, RandomListNode * >
			origin_to_copy_map;

		RandomListNode * p1 = head;
		RandomListNode * prev_p = 0;
		RandomListNode * head2 = 0;//head to the deep copy
		while ( p1 )
		{
			RandomListNode * p
				= new RandomListNode( p1->label );
			if ( ! head2 )
			{
				head2 = p;
				prev_p = head2; 
			}
			else
			{
				prev_p->next = p;
			}
			
			origin_to_copy_map.insert(
					std::make_pair( p1, p ) );

			prev_p = p;
			p1 = p1->next;
		}
		//dont forget
		if ( prev_p )
		{
			prev_p->next = 0;
		}
		
		//process random pointer
		p1 = head;
		RandomListNode * p2 = head2;
		while ( p1 )
		{
			if ( p1->random )
			{
				p2->random = origin_to_copy_map[ p1->random ];
			}
			
			p1 = p1->next;
			p2 = p2->next;
		}

		return head2;
    }
};
