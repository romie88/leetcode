/**
 * Algorithms 170 Two Sum III - Data structure design                      Easy
 * 
 * Design and implement a TwoSum class. It should support the following
 * operations: add and find.
 * 
 * add  - Add the number to an internal data structure.
 * find - Find if there exists any pair of numbers which sum is equal to the
 *        value.
 * 
 * For example,
 * 
 * add(1); add(3); add(5);
 * find(4) -> true
 * find(7) -> false
 * 
 * Tags: Hash Table, Data Structure
 */

#include <unordered_map>
#include <utility>
/**
 * add - O( n ) runtime, find - O( 1 ) runtime, O( n^2 ) space - Store
 * pairs sums in a hash table
 * 
 * Each add operation essentially go through the list and form new pair
 * sums that go into the hash table.
 * 
 * The find operation involves a single hash table lookup in O( 1 ) runtime.
 * 
 * This method is useful if the number of find operations far exceeds the
 * number of add operations.
 */

/**
 * add - O( n ) runtime, find - O( n ) runtime, O( n ) space - Binary
 * search + Two pointers
 * 
 * Maintain a sorted array of numbers. First we search for the correct
 * insert position in O( log n ) time using a modified binary search.
 * 
 * Each add operation takes O( n ) time because all elements after the
 * inserted element need to be shifted.
 * 
 * For find operation we could then apply the Two pointers approach in
 * O( n ) runtime.
 */

/**
 * add - O( 1 ) runtime, find - O( n log n ) runtime, O( n ) space - Sort
 * + Two pointers
 * 
 * We store each input into an array without maintaining its sorted order.
 * 
 * For find operation we first sort the array in O( n log n ) time, then
 * apply the Two pointers approach in O( n ) runtime.
 */

/**
 * add - O( 1 ) runtime, find - O( n ) runtime, O( n ) space - Store input
 * in hash table
 * 
 * A simpler approach is to store each input into a hash table with input
 * as key and its count as value. To find if a pair sum exists, just iterate
 * through the hash table in O( n ) runtime.
 */
class TwoSum {
public:
    
	void add( const int number ) {
        /**
         * The following code will have TLE.
         */
        /*
	    auto it = hash_table.find( number );
        if ( it == hash_table.end() )
            hash_table.insert( std::make_pair( number, 1 ) );
        else
            ++it->second;
        */
        ++hash_table[ number ];
	}
    
	bool find( const int value ) {
	    for ( auto i : hash_table ) {
            int y = value - i.first;
            if ( y == i.first ) {
                 if ( i.second > 1 )
                     return true;
            } else {
                auto it = hash_table.find( y );
                if ( it != hash_table.end() )
                    return true;
            }
        }
        return false;
	}
private:
    std::unordered_map< int, int > hash_table;
};
