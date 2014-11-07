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

class Solution {
public:
    int candy( std::vector< int > & ratings ) {
        
		//input size == 0 or == 1 cases
		if ( ratings.size() <= 1 )
			return ratings.size();
		
		std::vector< int > candies( ratings.size(), 0 );
		
		//Its OK to set candies[ 0 ] = 1
		//If necessary we can adjust it if ratings[ 0 ] > ratings[ 1 ] > ...
		candies[ 0 ] = 1;
		int i = 1;
		while ( i < ratings.size() )
		{
			if ( ratings[ i - 1 ] < ratings[ i ] )
			{
				candies[ i ] = candies[ i - 1 ] + 1;
				++i;
			}
			else if ( ratings[ i - 1 ] == ratings[ i ] )
			{
				candies[ i ] = 1;
				++i;
			}
			else//ratings[ i - 1 ] > ratings[ i ]
			{
				//seek the decreasing series ratings[ i - 1 ] > ... > ratings[ k ]
				int k = i;
				while ( k < ratings.size()
			    	 && ratings[ k - 1 ] > ratings[ k ] )
					++k;
				
				int c = 1;
				for ( int j = k - 1; j >= i; --j )
				{
					candies[ j ] = c++;
				}
				//this is required consider the case input
				//[ 4 2 3 4 1 ]
				candies[ i - 1 ] = std::max( candies[ i - 1 ], c );

				i = k;
			}
		}
		
		int total_candies = 0;
		for ( const auto & c : candies )
			total_candies += c;
		
		return total_candies;
    }
};

