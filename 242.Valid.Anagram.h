/**
 * Algorithms 242 Valid Anagram                                            Easy
 * 
 * Given two strings s and t, write a function to determine if t is an anagram
 * of s.
 * 
 * For example,
 * s = "anagram", t = "nagaram", return true.
 * s = "rat", t = "car", return false.
 * 
 * Note:
 * You may assume the string contains only lowercase alphabets.
 * 
 * Tags: Hash Table, Sort
 * Similar Problems: (M) Group Anagrams, (E) Palindrome Permutation
 */

#include <string>
#include <algorithm>

class Solution {
public:
    bool isAnagram( std::string & s, std::string & t ) {
        return is_anagram_hash( s, t );
    }
private:
    bool is_anagram_hash( const std::string & s, const std::string & t ) {
        if ( s.length() != t.length() ) return false;
        
        int freq[ 26 ] = { 0 };
        for ( const auto c : s )
            ++freq[ c - 'a' ];
        
        for ( const auto c : t ) {
            if ( freq[ c - 'a' ] == 0 )
                return false;
            else
                --freq[ c - 'a' ];
        }
        return true;
    }
    bool is_anagram_sort( std::string & s, std::string & t ) {
        if ( s.length() != t.length() ) return false;
        
        std::sort( s.begin(), s.end() );
        std::sort( t.begin(), t.end() );
        return s == t;
    }
};
