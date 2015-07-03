/**
 * 159 Longest Substring with At Most Two Distinct Characters              Hard
 * 
 * Given a string, find the length of the longest substring T that contains at
 * most 2 distinct characters.
 * 
 * For example, Given s = “eceba”,
 * 
 * T is "ece" which its length is 3.
 * 
 * Tags: Hash Table, Two Pointers, String
 */

#include <string>
#include <algorithm>
#include <cstring>

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct( const std::string & s ) {
        return length_of_longest_substring_k_distinct( s, 2 );
    }
private:
    int length_of_longest_substring_two_distinct( const std::string & s ) {
        int i = 0;//i points to the starting of the substring we are looking for
        int j = -1;//j points to the latest character which is != s[ k ]
        int max_len = 0;
        const int n = s.length();
        for ( int k = 1; k < n; ++k ) {
            if ( s[ k ] == s[ k - 1 ] ) continue;
            if ( j >= 0 && s[ j ] != s[ k ] ) {
                max_len = std::max( k - i, max_len );
                i = j + 1;
            }
            //s[ j ] != s[ k ]
            j = k - 1;
        }
        return std::max( n - i, max_len );
    }
    /**
     * A generalized version to handle k distinct characters.
     */
    int length_of_longest_substring_k_distinct(
            const std::string & s,
            const int           k ) {
        int hash_table[ 256 ];
        std::memset( hash_table, 0, sizeof( hash_table ) );
        int i = 0;//i points to the starting of the substring we are looking for
        int max_len = 0;
        int num_distinct = 0;
        for ( int j = 0; j < s.length(); ++j ) {
            if ( hash_table[ s[ j ] ] == 0 ) ++num_distinct;
            ++hash_table[ s[ j ] ];
            while ( num_distinct > k ) {
                --hash_table[ s[ i ] ];
                if ( hash_table[ s[ i ] ] == 0 ) --num_distinct;
                ++i;
            }
            max_len = std::max( j - i + 1, max_len );
        }
        return max_len;
    }
};
