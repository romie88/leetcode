/**
 * Algorithms 245 Shortest Word Distance II                              Medium
 * 
 * This is a follow up of Shortest Word Distance. The only difference is now
 * word1 could be the same as word2.
 * 
 * Given a list of words and two words word1 and word2, return the shortest
 * distance between these two words in the list.
 * 
 * word1 and word2 may be the same and they represent two individual words in
 * the list.
 * 
 * For example,
 * Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
 * 
 * Given word1 = “makes”, word2 = “coding”, return 1.
 * Given word1 = "makes", word2 = "makes", return 3.
 * 
 * Note:
 * You may assume word1 and word2 are both in the list.
 * 
 * Tags: Array
 * Similar Problems: (E) Shortest Word Distance,
 *                   (M) Shortest Word Distance II
 */

#include <vector>
#include <string>
#include <algorithms>

class Solution {
public:
    int shortestWordDistance( const std::vector< std::string > & words,
                              const std::string                & word1,
                              const std::string                & word2 ) {
        return shortest_word_distance( words, word1, word2 );
    }
private:
    int shortest_word_distance( const std::vector< std::string > & words,
                                const std::string                & word1,
                                const std::string                & word2 ) {
        int shortest = words.size();
        if ( word1 == word2 ) {
            int i1 = -1;
            for ( int i = 0; i < words.size(); ++i ) {
                if ( words[ i ] == word1 ) {
                    if ( i1 == -1 ) {
                        i1 = i;
                    } else {
                        shortest = std::min( shortest, i - i1 );
                        i1 = i;
                    }
                }
            }
        } else {
            int i1 = -1, i2 = -1;
            for ( int i = 0; i < words.size(); ++i ) {
                if ( words[ i ] == word1 ) {
                    if ( i2 != -1 )
                        shortest = std::min( shortest, i - i2 );
                    i1 = i;
                } else if ( words[ i ] == word2 ) {
                    if ( i1 != -1 )
                        shortest = std::min( shortest, i - i1 );
                    i2 = i;
                }
            }
        }
        return shortest;
    }
};
