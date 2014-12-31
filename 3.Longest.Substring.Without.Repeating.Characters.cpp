//3 Longest Substring Without Repeating Characters [ Medium ]
//
//Given a string, find the length of the longest substring without repeating
//characters. For example, the longest substring without repeating letters for
//"abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest
//substring is "b", with the length of 1.

//Tags: Hash Table, Two Pointers, String

#include <string>
#include <unordered_set>

class Solution {
public:
    int lengthOfLongestSubstring( const std::string & s ) {
        
        std::string::size_type i = 0;//start of the substring
        std::string::size_type j = 0;//end of the substring (past the last character)
        int max_len = 0;
        std::unordered_set< char > set;
        while ( j < s.length() ) {
            //found repeated character
            if ( set.find( s[ j ] ) != set.end() ) {
                if ( j - i > max_len )
                    max_len = j - i;

                while ( s[ i ] != s[ j ] ) {
                    set.erase( set.find( s[ i ] ) );
                    ++i;
                }
                
                ++i;
                ++j;
            } else {
                set.insert( s[ j ] );
                ++j;
            }
        }
        //don't forget the last potential substring
        if ( s.length() - i > max_len ) max_len = s.length() - i;

        return max_len;
    }
};

