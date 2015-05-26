/**
 * Algorithms 217 Contains Duplicate                                       Easy
 * 
 * Given an array of integers, find if the array contains any duplicates. Your
 * function should return true if any value appears at least twice in the
 * array, and it should return false if every element is distinct.
 *
 * Tags: Array, Hash Table
 */

#include <vector>
#include <unordered_set>

class Solution {
public:
    bool containsDuplicate( std::vector< int > & nums ) {
        return contains_duplicate_hashtable( nums );
    }
private:
    bool contains_duplicate_hashtable( const std::vector< int > & nums ) {
        std::unordered_set< int > s;
        for( const auto n : nums ) {
            auto it = s.find( n );
            if ( it != s.end () )
                return true;
            else
                s.insert( n );
        }
        return false;
    } 
};
