//Candy
//
//There are N children standing in a line. Each child is assigned a
//rating value.
//
//You are giving candies to these children subjected to the following
//requirements:
//
//* Each child must have at least one candy.
//
//* Children with a higher rating get more candies than their neighbors.
//
//What is the minimum candies you must give?

//Tags: Greedy

#include <vector>
#include <algorithm>

/**
 * use two arrays:
 * one for minimum candy required to satisfy constraint from left neighbor,
 * the other for minimum candy required to satisfy constraint from right
 * neighbor.
 *
 * The candy required for each child is the max of the related values in
 * the two arrays.
 */
class Solution {
public:
    int candy( std::vector< int > & ratings ) {
        
		//input size == 0 or == 1 cases
		if ( ratings.size() <= 1 )
			return ratings.size();
		
		std::vector< int > lc( ratings.size(), 1 );
		std::vector< int > rc( ratings.size(), 1 );
		
		for ( int i = 1; i < lc.size(); ++i )
		{
			if ( ratings[ i - 1 ] < ratings[ i ] )
			{
				lc[ i ] = lc[ i - 1 ] + 1;
			}
		}

		for ( int i = rc.size() - 2; i >= 0; --i )
		{
			if ( ratings[ i ] > ratings[ i + 1 ] )
			{
				rc[ i ] = rc[ i + 1 ] + 1;
			}
		}

		int total_candies = 0;
		for ( int i = 0; i < ratings.size(); ++i )
			total_candies += std::max( lc[ i ], rc[ i ] );
		
		return total_candies;
    }
};

