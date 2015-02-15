struct ListNode {
    int val;
    ListNode * next;
    ListNode( int x ) : val( x ), next( nullptr ) {}
};

#include "19.Remove.Nth.Node.From.End.of.List.h"

#include <iostream>

void print_list( ListNode * p ) {
    while ( p ) {
        std::cout << p->val << ", ";
        p = p->next;
    }
    std::cout << std::endl;
}

int main() {
    
    {
        ListNode * p1 = new ListNode( 1 );
        ListNode * p2 = new ListNode( 2 );
        ListNode * p3 = new ListNode( 3 );
        ListNode * p4 = new ListNode( 4 );
        ListNode * p5 = new ListNode( 5 );
        
        p1->next = p2;
        p2->next = p3;
        p3->next = p4;
        p4->next = p5;
        
        ListNode * head = p1;
        Solution sln;
        head = sln.removeNthFromEnd( head, 5 );
        print_list( head );
        head = sln.removeNthFromEnd( head, 1 );
        print_list( head );
        head = sln.removeNthFromEnd( head, 2 );
        print_list( head );
    }

    return 0;
}
