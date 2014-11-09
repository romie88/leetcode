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
#include <iostream>

class Solution {
public:
    int canCompleteCircuit( std::vector< int > & gas, std::vector< int > & cost ) {
		
		const int n = gas.size();
		//try all the gas stations
		for ( int i = 0; i < n; )
		{
			//start from i
			int gas_in_tank = 0;
			int j = i;
			int k = j;
			for ( ; k < j + n; ++k )
			{
				int t = k % n;
				gas_in_tank += gas[ t ] - cost[ t ];
				if ( gas_in_tank < 0 )
					break;
			}
			if ( gas_in_tank >= 0 )
				return j;
			else
				i = k + 1;
		}
		
		return -1;
    }
};
