/**
 * Algorithms 243 Shortest Word Distance                                   Easy
 * 
 * Given a list of words and two words word1 and word2, return the shortest
 * distance between these two words in the list.
 * 
 * For example,
 * Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
 * 
 * Given word1 = “coding”, word2 = “practice”, return 3.
 * Given word1 = "makes", word2 = "coding", return 1.
 * 
 * Note:
 * You may assume that word1 does not equal to word2, and word1 and word2 are
 * both in the list.
 * 
 * Tags: Array
 * Similar Problems: (M) Shortest Word Distance II
 *                   (M) Shortest Word Distance III
 */

#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    int shortestDistance( const std::vector< std::string > & words,
                          const std::string                & word1,
                          const std::string                & word2 ) {
        return shortest_distance( words, word1, word2 );
    }
private:
    /**
     * O( n ) runtime, O( 1 ) space
     */
    int shortest_distance( const std::vector< std::string > & words,
                           const std::string                & word1,
                           const std::string                & word2 ) {
        int i1 = -1;
        int i2 = -1;
        int shortest = words.size();
        for ( int k = 0; k < words.size(); ++k ) {
            if ( words[ k ] == word1 ) {
                i1 = k;
                if ( i2 != -1 )
                    shortest = std::min( shortest, i1 - i2 );
            } else if ( words[ k ] == word2 ) {
                i2 = k;
                if ( i1 != -1 )
                    shortest = std::min( shortest, i2 - i1 );
            }
        }
        return shortest;
    }
};
