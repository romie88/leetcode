//Longest Consecutive Sequence
//
//Given an unsorted array of integers, find the length of the longest
//consecutive elements sequence.
//
//For example,
//Given [100, 4, 200, 1, 3, 2],
//The longest consecutive elements sequence is [1, 2, 3, 4]. Return its
//length: 4.
//
//Your algorithm should run in O(n) complexity.

//Tags: Array

#include <vector>
#include <unordered_map>

class Solution {
public:
    int longestConsecutive( std::vector< int > & num ) {
        
        //hash map from number to a flag
        //the flag is used in the later loop
        //to indicate if this number has been checked
        unordered_map< int, bool > num_to_flag;
        for ( const auto n : num )
            num_to_flag[ n ] = false;

        int result = 0;
        for ( auto p : num_to_flag )
        {
            if ( ! p.second )
            {
                p.second = false;

                int seq_length = 1;
                for ( int i = p.first + 1;
                      num_to_flag.find( i ) != num_to_flag.end();
                      ++i )
                {
                    num_to_flag[ i ] = true;
                    ++seq_length;
                }

                for ( int i = p.first - 1;
                      num_to_flag.find( i ) != num_to_flag.end();
                      --i )
                {
                    num_to_flag[ i ] = true;
                    ++seq_length;
                }

                if ( seq_length > result )
                    result = seq_length;
            }
        }

        return result;
    }
};
