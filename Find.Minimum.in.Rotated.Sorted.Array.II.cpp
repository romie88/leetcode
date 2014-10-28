//Find Minimum in Rotated Sorted Array II
//
//Follow up for "Find Minimum in Rotated Sorted Array":
//What if duplicates are allowed?
//
//Would this affect the run-time complexity? How and why?
//
//Suppose a sorted array is rotated at some pivot unknown to you beforehand.
//
//(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
//
//Find the minimum element.
//
//The array may contain duplicates.

//Tags: Array, Binary Search
#include <vector>

class Solution {
public:
    int findMin( std::vector< int > & num ) {
        
		int low  = 0;
		int high = num.size() - 1;
		int mid  = ( low + high ) / 2;
		while ( low <= high )
		{
			if ( num[ low ] < num[ high ] )
			{
				mid = low;
				break;
			}
			else if ( num[ low ] == num[ high ] )
			{
				while ( num[ low ] == num[ high ] )
					++low;//or --high
			}
			else//num[ low ] > num[ high ]
			{
				if ( num[ mid ] <= num[ high ] )
				{
					high = mid;
				}
				else//num[ mid ] > num[ high ]
				{
					low = mid + 1;
				}
			}
			mid = ( low + high ) / 2;
		}
		
		return num[ mid ];
    }
};
