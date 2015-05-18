/**
 * Algorithms 23 Merge k Sorted Lists                                     Hard
 *
 * Merge k sorted linked lists and return it as one sorted list. Analyze and
 * describe its complexity.
 *
 * Tags: Divide and Conquer, Linked List, Heap
 */

#include <vector>
#include <queue>

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
    ListNode * mergeKLists( std::vector< ListNode * > & lists ) {
        return merge_k_lists_by_DnC( lists );
    }
private:
    /**
     * Merge by heap
     * n is the length of a list
     * O(nk log(k)) time, O(k) space
     */
    struct HeapComp {
        bool operator()( const ListNode * lhs, const ListNode * rhs ) const {
            return lhs->val > rhs->val;
        }
    };
    ListNode * merge_k_lists_by_heap( std::vector< ListNode * > & lists ) {
        std::priority_queue< ListNode *,
                             std::vector< ListNode * >,
                             HeapComp > heap;
        ListNode dummy_head( 0 );
        ListNode * p = &dummy_head;
        for ( unsigned int i = 0; i < lists.size(); ++i )
            if ( lists[ i ] )
                heap.push( lists[ i ] );
        while ( ! heap.empty() ) {
            ListNode * q = heap.top();
            heap.pop();
            p->next = q;
            if ( q->next )
                heap.push( q->next );
            p = p->next;
        }
        return dummy_head.next;
    }
    /**
     * Divide-and-Conquer
     * O(nk log(k)) time, O(1) space
     */
    ListNode * merge_k_lists_by_DnC( std::vector< ListNode * > & lists ) {
        if ( lists.empty() ) return nullptr;
        int j = lists.size() - 1;
        while ( j > 0 ) {
            int i = 0;
            while ( i < j ) {
                lists[ i ] = merge( lists[ i ], lists[ j ] );
                ++i;
                --j;
            }
        }
        return lists[ 0 ];
    }
    ListNode * merge( ListNode * l1, ListNode * l2 ) {
        ListNode dummy_head( 0 );
        ListNode * p = &dummy_head;
        while ( l1 && l2 ) {
            if ( l1->val < l2->val ) {
                p->next = l1;
                l1 = l1->next;
            } else {
                p->next = l2;
                l2 = l2->next;
            }
            p = p->next;
        }
        if ( l1 ) p->next = l1;
        if ( l2 ) p->next = l2;
        return dummy_head.next;
    }
};
