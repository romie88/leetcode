//Find Minimum in Rotated Sorted Array
//
//Suppose a sorted array is rotated at some pivot unknown to you beforehand.
//
//(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
//
//Find the minimum element.
//
//You may assume no duplicate exists in the array.

#include <vector>

class Solution {
public:
    //let v be the input vector, i.e., v[0] ... v[n-1] be
    //the rotated sorted array
    //let p be the index of the minimum element.
    //
    //a few observations are following:
    //1. consider the partition of the array: v[0 .. p-1] and v[p .. n-1]
    //v[0], v[1], ..., v[p-1] are all larger than v[p], v[p+1], ..., v[n-1]
    //2. if p = 0, then the array is not rotated at all,
    //the minimum element is located at index 0;
    //otherwise v[0] > v[n-1] (no duplicate in the array).
    //
    //try the idea of binary search:
    //three elements are considered v[low], v[mid], v[high]
    //initially low = 0, high = n-1
    //first check if v[low] > v[high]:
    //if v[low] < v[high], then p == low
    //and the minimum element is found;
    //if v[low] > v[high], then p != low and p is one of low+1, ..., high.
    //and check v[mid], v[mid] is either in v[low], ..., v[p-1] or
    //in v[p], ..., v[high].
    //
    //Extension: what if the question is asking for the maximum element?
    //what if there are duplicated elements?
    int findMin( std::vector< int > & num ) {
        int low  = 0;
        int high = num.size() - 1;
        int mid  = ( low + high ) / 2;
        int i    = 0;//the index of the minimum element
        while ( low <= high )
        {
            if ( low == high )
            {
                i = low;
                break;
            }
            else//low < high
            {
                if ( num[ low ] < num[ high ] )
                {
                    i = low;
                    break;
                }
                else if ( num[ low ] == num[ high ] )//handle duplicates
                {
                    while ( low < high && num[ low ] == num[ high ] )
                        ++low;
                }
                else//num[ low ] > num[ high ]
                {
                    if ( mid == low )//mid == low, low + 1 == high
                    {
                        i = high;
                        break;
                    }
                    else//low, mid, high are all different from each other
                    {
                        if ( num[ mid ] >= num[ low ] )//handle duplicates
                        {
                            low = mid + 1;
                        }
                        else
                        {
                            high = mid;
                        }
                        mid = ( low + high ) / 2;
                    }
                }
            } 
        }
        return num[i];
    }
};
