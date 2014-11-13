//Min Stack 2014-11-09
//
//Design a stack that supports push, pop, top, and retrieving the minimum
//element in constant time.
//
// * push(x) -- Push element x onto stack.
// * pop() -- Removes the element on top of the stack.
// * top() -- Get the top element.
// * getMin() -- Retrieve the minimum element in the stack.

//Tags: Stack, Data Structure

#include <stack>

class MinStack {
public:
    void push( int x ) {
        
        if ( d_min_stack.empty()
          || x <= d_min_stack.top() )
            d_min_stack.push( x );

        d_stack.push( x );
    }

    void pop() {
        
        if ( d_stack.empty() )
            return;

        if ( d_stack.top() == d_min_stack.top() )
            d_min_stack.pop();

        d_stack.pop();
    }

    int top() {
        return d_stack.top();
    }

    int getMin() {
        return d_min_stack.top();
    }
private:
    std::stack< int > d_stack;
    //top of the d_min_vec is the minimum element of d_vec
    std::stack< int > d_min_stack;
};
