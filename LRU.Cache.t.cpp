#include "LRU.Cache.cpp"

#include <iostream>

int main()
{
	LRUCache c( 10 );

	c.set( 10, 13 );
	c.set( 3, 17 );
	c.set( 6, 11 );
	c.set( 10, 5 );
	c.set( 9, 10 );
	std::cout << c.get( 13 ) << std::endl;
	c.set( 2, 19 );
	std::cout << c.get( 2 ) << std::endl;
	std::cout << c.get( 3 ) << std::endl;
	c.set( 5, 25 );
	std::cout << c.get( 8 ) << std::endl;
	c.set(9,22);
	c.set(5,5);
	c.set(1,30);
	std::cout << c.get(11) << std::endl;//-1
	c.set(9,12);
	std::cout << c.get(7) << std::endl;//-1
	std::cout << c.get(5) << std::endl;//5
	std::cout << c.get(8) << std::endl;//-1
	std::cout << c.get(9) << std::endl;//12
	c.set(4,30);
	c.set(9,3);
	std::cout << c.get(9) << std::endl;//3
	std::cout << c.get(10) << std::endl;//5
	std::cout << c.get(10) << std::endl;//5
	c.set(6,14);
	c.set(3,1);
	std::cout << c.get(3) << std::endl;//1
	c.set(10,11);
	std::cout << c.get(8) << std::endl;//-1
	c.set(2,14);
	std::cout << c.get(1) << std::endl;//30
	std::cout << c.get(5) << std::endl;//5
	std::cout << c.get(4) << std::endl;//30
	c.set(11,4);
	c.set(12,24);
	c.set(5,18);
	std::cout << c.get(13) << std::endl;//-1
	c.set(7,23);
	std::cout << c.get(8) << std::endl;//-1
	std::cout << c.get(12) << std::endl;//24
	c.set(3,27);
	c.set(2,12);
	std::cout << c.get(5) << std::endl;//18
	c.set(2,9);
	c.set(13,4);
	c.set(8,18);
	c.set(1,7);
	std::cout << c.get(6) << std::endl;//-1
	return 0;
}
