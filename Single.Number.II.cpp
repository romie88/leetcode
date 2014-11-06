//Single Number II
//
//Given an array of integers, every element appears three times except for one.
//Find that single one.
//
//Note:
//
//Your algorithm should have a linear runtime complexity.
//Could you implement it without using extra memory?

//Tags:

#include <unordered_map>

class Solution {
public:
    int singleNumber( int A[], int n ) {
		
		std::unordered_map< int, int >
			num_to_appear_times_map;

		for ( int i = 0; i < n; ++i )
		{
			num_to_appear_times_map[ A[ i ] ]++;
		}

		for ( const auto & p : num_to_appear_times_map )
			if ( p.second == 1 )
				return p.first;
    }
};
