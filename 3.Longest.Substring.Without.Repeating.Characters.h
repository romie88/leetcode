/**
 * 3 Longest Substring Without Repeating Characters                      Medium 
 * 
 * Given a string, find the length of the longest substring without repeating
 * characters. For example, the longest substring without repeating letters for
 * "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest
 * substring is "b", with the length of 1.
 * 
 * Tags: Hash Table, Two Pointers, String
 */

#include <string>
#include <algorithm>

class Solution {
public:
    int lengthOfLongestSubstring( const std::string & s ) {
        return length_of_longest_substring( s );
    }
private:
    int length_of_longest_substring( const std::string & s ) {
        int hash_table[ 256 ];
        for ( auto & i : hash_table ) i = -1;
        
        int max_len = 0;
        int start = -1;
        for ( int i = 0; i < s.length(); ++i ) {
            if ( hash_table[ s[ i ] ] > start )
                start = hash_table[ s[ i ] ];
            
            hash_table[ s[ i ] ] = i;
            max_len = std::max( max_len, i - start );
        }
        return max_len;
    }
};

