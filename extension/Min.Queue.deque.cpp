//Min Queue
//
//Extension of the leetcode problem Min Stack
//
//Implement a queue in which push_rear(), pop_front() and get_min() are all
//constant time operations.

//The implementation here is to have an extra deque to track the minimum
//on the front of the extra deque.

#include <queue>
#include <deque>

class MinQueue {
public:
    void push_rear( int x ) {
        
        if ( d_min_deque.empty()
          || x >= d_min_deque.back() )
        {
            d_min_deque.push_back( x );
        }
        else
        {
            while ( ! d_min_deque.empty()
                 && x < d_min_deque.back() )
                d_min_deque.pop_back();

            d_min_deque.push_back( x );
        }

        d_queue.push( x );
    }

    void pop_front() {
        
        if ( d_queue.empty() )
            return;

        if ( d_queue.front() == d_min_deque.front() )
            d_min_deque.pop_front();

        d_queue.pop();
    }

    int front() {
        return d_queue.front();
    }

    int get_min() {
        return d_min_deque.front();
    }
private:
    std::queue< int > d_queue;
    //front of the d_min_deque is the minimum element of d_queue
    std::deque< int > d_min_deque;
};
