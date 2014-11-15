//Min Queue
//
//Extension of the leetcode problem Min Stack
//
//Implement a queue in which push_rear(), pop_front() and get_min() are all
//constant time operations.

//This implementation is to use two min stacks.

#include "../Min.Stack.cpp"
#include <exception>

class MinQueue {
public:
    void push_rear( int x ) {
        d_min_stack1.push( x );
    }

    void pop_front() {
        if ( d_min_stack2.empty() )
        {
            move_from_stack1_to_stack2();    
        }
        
        if ( d_min_stack2.empty() )
            return;

        d_min_stack2.pop();
    }

    int front() {

        if ( d_min_stack2.empty() )
        {
            move_from_stack1_to_stack2();    
        }

        if ( d_min_stack2.empty() )
            throw std::exception();

        return d_min_stack2.top();
    }

    int get_min() {

        if ( ! d_min_stack1.empty()
          && ! d_min_stack2.empty() )
            return std::min( d_min_stack1.getMin(), d_min_stack2.getMin() );
        else if ( ! d_min_stack1.empty() )
            return d_min_stack1.getMin();
        else if ( ! d_min_stack2.empty() )
            return d_min_stack2.getMin();
        else
            throw std::exception();
    }
private:
    
    void move_from_stack1_to_stack2()
    {
        while ( ! d_min_stack1.empty() )
        {
            d_min_stack2.push( d_min_stack1.top() );
            d_min_stack1.pop();
        }
    }

    MinStack d_min_stack1;
    MinStack d_min_stack2;
};
