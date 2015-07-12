/**
 * Algorithms 25 Reverse Nodes in k-Group                                 Hard 
 * 
 * Given a linked list, reverse the nodes of a linked list k at a time and
 * return its modified list.
 * 
 * If the number of nodes is not a multiple of k then left-out nodes in the
 * end should remain as it is.
 * 
 * You may not alter the values in the nodes, only nodes itself may be changed.
 * 
 * Only constant memory is allowed.
 * 
 * For example,
 * Given this linked list: 1->2->3->4->5
 * 
 * For k = 2, you should return: 2->1->4->3->5
 * 
 * For k = 3, you should return: 3->2->1->4->5
 *
 * Tags: Linked List
 * Similar Problems: (M) Swap Nodes in Pairs
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
    ListNode * reverseKGroup( ListNode * head, int k ) {
        ListNode dummy_node( 0 );
        ListNode * p = &dummy_node;
        p->next = head;
        ListNode * start = nullptr;
        ListNode * end   = nullptr;
        traverse_k_nodes( p, k, start, end );
        while ( end ) {
            ListNode * end_next = end->next;
            end->next = nullptr;
            p->next = reverse( start );
            p = start;
            start->next = end_next;
            traverse( p, k, start, end );
        }
        return dummy_node.next;
    }
private:
    void traverse_k_nodes( ListNode * p, int k,
                           ListNode * & start, ListNode * & end ) {
        if ( p == nullptr ) {
            start = nullptr;
            end   = nullptr;
            return;
        }

        start = p->next;
        end   = start;
        while ( end && --k > 0 )
            end = end->next;
        if ( k > 0 ) end = nullptr;
    }
    ListNode * reverse( ListNode * p ) {
        ListNode * prev = nullptr;
        while ( p ) {
            ListNode * p_next = p->next;
            p->next = prev;
            prev = p;
            p = p_next;
        }
        return prev;
    }
};
//A simpler implementation
#if 0
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if ( k <= 0 ) throw std::out_of_range( "k is not positive" );
        if ( k == 1 ) return head;
        
        ListNode dummy_head( 0 );
        dummy_head.next = head;
        ListNode * p = &dummy_head;
        while ( p->next ) {
            ListNode * q = p;
            int k2 = k;
            //move q forward k steps to see if we have k nodes to reverse
            while ( q && k2 ) {
                q = q->next;
                --k2;
            }
            if ( q == nullptr ) break;
            
            ListNode * next_start = q->next;
            q->next = nullptr;
            ListNode * origin_head = p->next;
            reverse( p->next );
            p->next = q;//q points the last node before reverse which is the head now
            origin_head->next = next_start;
            p = origin_head;
        }
        return dummy_head.next;
    }
private:
    ListNode * reverse( ListNode * p ) {
        ListNode * prev = nullptr;
        while ( p ) {
            ListNode * p_next = p->next;
            p->next = prev;
            prev = p;
            p = p_next;
        }
        return prev;
    }
};
#endif
