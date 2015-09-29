/**
 * Algorithms 244 Shortest Word Distance II                              Medium
 * 
 * This is a follow up of Shortest Word Distance. The only difference is now you
 * are given the list of words and your method will be called repeatedly many
 * times with different parameters. How would you optimize it?
 * 
 * Design a class which receives a list of words in the constructor, and
 * implements a method that takes two words word1 and word2 and return the
 * shortest distance between these two words in the list.
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
 * Tags: Hash Table, Design
 * Similar Problems: (E) Merge Two Sorted Lists,
 *                   (E) Shortest Word Distance,
 *                   (M) Shortest Word Distance III
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithms>

class WordDistance {
public:
    WordDistance( const std::vector< std::string > & words )
            : total_words( words.size() ) {
        for ( int i = 0; i < words.size(); ++i ) {
            auto it = positions_map.find( words[ i ] );
            if ( it == positions_map.end() ) {
                positions_map.insert( std::make_pair( words[ i ], std::vector< int >( 1, i ) ) );
            } else {
                it->second.push_back( i );
            }
        }
    }
    
    int shortest( const std::string & word1, const std::string & word2 ) {
        const std::vector< int > & v1 = positions_map[ word1 ];
        const std::vector< int > & v2 = positions_map[ word2 ];
        int shortest = total_words;
        for ( int i1 = 0, i2 = 0; i1 < v1.size() && i2 < v2.size(); ) {
            if ( v1[ i1 ] > v2[ i2 ] ) {
                shortest = std::min( v1[ i1 ] - v2[ i2++ ], shortest );
            } else {
                shortest = std::min( v2[ i2 ] - v1[ i1++ ], shortest );
            }
        }
        return shortest;
    }
private:
    std::unordered_map< std::string, std::vector< int > > positions_map;
    const int total_words;
};


// Your WordDistance object will be instantiated and called as such:
// WordDistance wordDistance(words);
// wordDistance.shortest("word1", "word2");
// wordDistance.shortest("anotherWord1", "anotherWord2");
