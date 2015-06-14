/**
 * Algorithms 225 Implement Stack using Queues                           Medium
 * 
 * Implement the following operations of a stack using queues.
 * 
 * * push(x) -- Push element x onto stack.
 * * pop() -- Removes the element on top of the stack.
 * * top() -- Get the top element.
 * * empty() -- Return whether the stack is empty.
 * 
 * Notes:
 * * You must use only standard operations of a queue -- which means only push
 *   to back, peek/pop from front, size, and is empty operations are valid.
 * * Depending on your language, queue may not be supported natively. You may
 *   simulate a queue by using a list or deque (double-ended queue), as long as
 *   you use only standard operations of a queue.
 * * You may assume that all operations are valid (for example, no pop or top
 *   operations will be called on an empty stack).
 * 
 * Update (2015-06-11):
 * The class name of the Java function had been updated to MyStack instead of
 * Stack.
 * 
 * Credits:
 * Special thanks to @jianchao.li.fighter for adding this problem and all test
 * cases.
 * 
 * Tags: Data Structure
 */

#include <queue>
#include <stdexcept>

class Stack {
public:
    //O( 1 ) runtime
    // Push element x onto stack.
    void push( int x ) {
        if ( ! q1.empty() )
            q1.push( x );
        else
            q2.push( x );
        
        top_element = x;
    }
    
    //O( n ) runtime
    // Removes the element on top of the stack.
    void pop() {
        if ( q1.empty() && q2.empty() )
            throw std::out_of_range( "Empty Stack" );
        
        if ( ! q1.empty() ) {
            while ( q1.size() > 1 ) {
                q2.push( q1.front() );
                top_element = q1.front();
                q1.pop();
            }
            q1.pop();
        } else {
            while ( q2.size() > 1 ) {
                q1.push( q2.front() );
                top_element = q2.front();
                q2.pop();
            }
            q2.pop();
        }
    }
    
    //O( 1 ) runtime
    // Get the top element.
    int top() {
        if ( q1.empty() && q2.empty() )
            throw std::out_of_range( "Empty Stack" );
        
        return top_element;
    }
    
    //O( 1 ) runtime
    // Return whether the stack is empty.
    bool empty() {
        return q1.empty() && q2.empty();
    }
private:
    std::queue< int > q1;
    std::queue< int > q2;
    int top_element;
};
