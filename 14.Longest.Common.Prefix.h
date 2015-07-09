/**
 * Algorithms 14 Longest Common Prefix                                     Easy
 * 
 * Write a function to find the longest common prefix string amongst an array
 * of strings.
 * 
 * Tags: String
 */

#include <string>
#include <vector>

class Solution {
public:
    /**
     * O( n * L ) runtime where n is the number of strings and L is the
     * the length of the longest common prefix.
     */
    std::string longestCommonPrefix( std::vector< std::string > & strs ) {
        std::string prefix;
        if ( strs.empty() ) return prefix;
        
        for ( int i = 0; i < strs[ 0 ].length(); ++i ) {
            bool match = true;
            for ( int j = 1; j < strs.size(); ++j ) {
                if ( i >= strs[ j ].length()
                  || strs[ j ][ i ] != strs[ 0 ][ i ] ) {
                    match = false;
                    break;
                }
            }
            if ( match )
                prefix += strs[ 0 ][ i ];
            else
                break;
        }
        return prefix;
    }
};
