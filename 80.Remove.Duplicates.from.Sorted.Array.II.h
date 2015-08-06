/**
 * Algorithms 80 Remove Duplicates from Sorted Array II                  Medium
 *
 * Follow up for "Remove Duplicates":
 * What if duplicates are allowed at most twice?
 *
 * For example,
 * Given sorted array nums = [1,1,1,2,2,3],
 *
 * Your function should return length = 5, with the first five elements of nums
 * being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new
 * length.
 *
 * Tags: Array, Two Pointers
 */

#include <vector>

class Solution {
public:
    int removeDuplicates( std::vector< int > & nums ) {
        return remove_duplicates_impl2( nums );
    }
private:
    int remove_duplicates_impl1( std::vector< int > & nums ) {
        if ( nums.empty() ) return 0;
        int j = 1;
        int c = 1;
        for ( int i = 1; i < nums.size(); ++i ) {
            if ( nums[ i - 1 ] == nums[ i ] ) {
                ++c;
                if ( c <= 2 )
                    nums[ j++ ] = nums[ i ];
            } else {
                c = 1;
                nums[ j++ ] = nums[ i ];
            }
        }
        return j;
    }
    int remove_duplicates_impl2( std::vector< int > & nums ) {
        if ( nums.size() < 3 ) return nums.size();
        int j = 2;
        for ( int i = 2; i < nums.size(); ++i ) {
            //if nums[ i ] == nums[ j - 2 ] all the elements between
            //nums[ i ] and nums[ j - 2 ] are all equal.
            if ( nums[ i ] != nums[ j - 2 ] )
                nums[ j++ ] = nums[ i ];
        }
        return j;
    }
};