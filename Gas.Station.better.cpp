//Gas Station
//
//There are N gas stations along a circular route, where the amount of gas
//at station i is gas[i].
//
//You have a car with an unlimited gas tank and it costs cost[i] of gas to
//travel from station i to its next station (i+1). You begin the journey with
//an empty tank at one of the gas stations.
//
//Return the starting gas station's index if you can travel around the
//circuit once, otherwise return -1.
//
//Note:
//The solution is guaranteed to be unique.

//Tags: Greedy

#include <vector>

class Solution {
public:
    int canCompleteCircuit( std::vector< int > & gas, std::vector< int > & cost ) {
		
		int total_gas_left = 0;
		int gas_left_i = 0;
		int j = 0;
		for ( int i = 0; i < gas.size(); ++i )
		{
			total_gas_left += gas[ i ] - cost[ i ];
			gas_left_i += gas[ i ] - cost[ i ];
			if ( gas_left_i < 0 )
			{
				j = i;
				gas_left_i = 0;
			}
		}
		
		if ( total_gas_left < 0 )
			return -1;
		else
			return j + 1;
    }
};
