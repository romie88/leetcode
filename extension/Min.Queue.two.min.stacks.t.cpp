#include "Min.Queue.two.min.stacks.cpp"
#include <iostream>

int main()
{
    MinQueue mq;

    mq.push_rear( 12 );
    std::cout << mq.front() << std::endl;
    std::cout << mq.get_min() << std::endl;

    mq.push_rear( 5 );
    std::cout << mq.front() << std::endl;
    std::cout << mq.get_min() << std::endl;

    mq.push_rear( 10 );
    std::cout << mq.front() << std::endl;
    std::cout << mq.get_min() << std::endl;

    mq.push_rear( 7 );
    std::cout << mq.front() << std::endl;
    std::cout << mq.get_min() << std::endl;
    
    mq.push_rear( 11 );
    std::cout << mq.front() << std::endl;
    std::cout << mq.get_min() << std::endl;

    mq.push_rear( 19 );
    std::cout << mq.front() << std::endl;
    std::cout << mq.get_min() << std::endl;
    
    mq.pop_front();
    std::cout << mq.front() << std::endl;
    std::cout << mq.get_min() << std::endl;

    mq.pop_front();
    std::cout << mq.front() << std::endl;
    std::cout << mq.get_min() << std::endl;

    return 0;
}
