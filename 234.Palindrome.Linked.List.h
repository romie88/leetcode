/**
 * Algorithm 234 Palindrome Linked List                                    Easy
 * 
 * Given a singly linked list, determine if it is a palindrome.
 * 
 * Follow up:
 * 
 * Could you do it in O(n) time and O(1) space?
 * 
 * Tags: Linked List, Two Pointers
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
    bool isPalindrome( ListNode * head ) {
        if ( head == nullptr ) return true;
        
        //find the pointer to the middle of the list
        //if the number of nodes is odd, p1 points to the middle node
        //if the number of nodes is even, p1 points to the start of the second
        //half
        ListNode * p1 = head;
        ListNode * p2 = head->next;
        int c = 1;//number of nodes
        while ( p2 ) {
            p1 = p1->next;
            p2 = p2->next; ++c;
            if ( p2 ) { p2 = p2->next; ++c; }
        }
        ListNode * p_mid = p1;
        
        if ( c == 1 ) return true;
        
        //reverse the first part of the list until p_mid
        ListNode * prev = nullptr;
        p1 = head;
        while ( p1 != p_mid ) {
            ListNode * p1_next = p1->next;
            p1->next = prev;
            prev = p1;
            p1 = p1_next;
        }
        ListNode * reversed_head = prev;
        
        //start to scan two lists
        p1 = reversed_head;
        p2 = c & 1 ? p_mid->next : p_mid;
        bool is_palindrome = true;
        while ( p1 && p2 ) {
            if ( p1->val != p2->val ) {
                is_palindrome = false;
                break;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        
        //restore the original list
        prev = nullptr;
        p1 = reversed_head;
        while ( p1 ) {
            ListNode * p1_next = p1->next;
            p1->next = prev;
            prev = p1;
            p1 = p1_next;
        }
        reversed_head->next = p_mid;
        
        return is_palindrome;
    }
};
