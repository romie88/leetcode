/**
 * Algorithms 30 Substring with Concatenation of All Words                Hard
 *
 * You are given a string, s, and a list of words, words, that are all of the
 * same length. Find all starting indices of substring(s) in s that is a
 * concatenation of each word in words exactly once and without any
 * intervening characters.
 *
 * For example, given:
 * s: "barfoothefoobarman"
 * words: ["foo", "bar"]
 * 
 * You should return the indices: [0,9].
 * (order does not matter). 
 *
 * Tags: Hash Table, Two Pointers, String
 */

#include <vector>
#include <string>
#include <unordered_map>

class Solution {
public:
    std::vector< int > findSubstring( const std::string & s,
                                      std::vector< std::string > & words ) {
        std::vector< int > results;
        find_substring_impl_2( s, words, results );
        return results;
    }
private:
    /**
     * Relatively straightforward implementation using two hashtables
     * and scan through the string to check the concatenation of all words.
     */
    void find_substring_impl_1( const std::string                & s,
                                const std::vector< std::string > & words,
                                std::vector< int >               & results ) {
        const int num_words = words.size();
        if ( num_words == 0 ) return;
        const int word_len  = words[ 0 ].length();
        if ( s.length() < num_words * word_len )
            return;

        std::unordered_map< std::string, int > word_count;
        for ( const auto & w : words )
            ++word_count[ w ];

        for ( int i = 0; i <= s.length() - num_words * word_len; ++i )
            if ( match_all_words( s, i, num_words, word_len, word_count ) )
                results.push_back( i );

        return;
    }
    bool match_all_words( const std::string & s,
                          const int           i,
                          const int           num_words,
                          const int           word_len,
                          const std::unordered_map< std::string, int > & word_count ) {
        if ( i + num_words * word_len > s.length() ) return false;

        std::unordered_map< std::string, int > word_count2;
        for ( int k = 0; k < num_words; ++k ) {
            const std::string & w = s.substr( i + k * word_len, word_len );
            const auto it = word_count.find( w );
            if ( it == word_count.end() )
                return false;
            ++word_count2[ w ];
            if ( word_count2[ w ] > it->second )
                return false;
        }
        return true;
    }

    /**
     * A complicated but much faster implemenation from leetcode discussion.
     * I haven't commented the code and just pasted it here for further study.
     */
    void find_substring_impl_2( const std::string                & S,
                                const std::vector< std::string > & words,
                                std::vector< int >               & res ) {

        if (words.empty() || words.size()*words[0].size()>S.length())
            return;

        int lens = S.length();             // string length
        int lenw = words.size();     // number of words
        int wordLen = words[0].size();           // word length

        // give 1..lenw id's to words, this maps each word with an unique id
        unordered_map<string, int> dict;
        dict.reserve(lenw);
        vector<int> toBeFound(lenw + 1, 0);          // baseline counts (needed for repeating words)
        for (int i = 0; i < lenw; ++i) {
            if (dict[words[i]] == 0)
                dict[words[i]] = i + 1;
            toBeFound[dict[words[i]]]++;
        }

        vector<int> curIdArray;
        curIdArray.reserve(lens / wordLen);

        // try start position from 0 to wordLen-1
        for (int startPos = 0; startPos < wordLen; startPos++) {
            curIdArray.clear();
            // from this specific start position, convert every substr of wordLen to their id's (if the word is valid)
            // or -1, if the word is not in the words
            for (int i = startPos; i + wordLen <= lens; i += wordLen) {
                auto di = dict.find(S.substr(i, wordLen));
                if (di != dict.end())
                    curIdArray.push_back(di->second);   // replace known word with id
                else
                    curIdArray.push_back(-1);           // replace unknown word with -1
            }

            // Fill the sliding window with first lenw-1 elements
            // we keep the count of each word and calculate error as the distance
            // between the current counts vector and the baseline count vector
            vector<int> hasFound(lenw + 1, 0);
            int err = lenw;
            for (int i = 0; i < lenw - 1; i++) {
                int id = curIdArray[i];
                if (id > 0) {
                    err -= abs(hasFound[id] - toBeFound[id]);
                    err += abs(hasFound[id] + 1 - toBeFound[id]);
                    hasFound[id]++;
                }
            }

            // move the window of size lenw maintaining the counts
            for (int i = 0; i + lenw <= curIdArray.size(); i++) {
                // add next element
                int id = curIdArray[i + lenw - 1];
                if (id > 0) {
                    err -= abs(hasFound[id] - toBeFound[id]);
                    err += abs(hasFound[id] + 1 - toBeFound[id]);
                    hasFound[id]++;
                }

                // if counts match
                if (err == 0)
                    res.push_back(startPos + i*wordLen);

                // remove first element
                id = curIdArray[i];
                if (id > 0) {
                    err -= abs(hasFound[id] - toBeFound[id]);
                    err += abs(hasFound[id] - 1 - toBeFound[id]);
                    hasFound[id]--;
                }
            }
        }
        return;
    }
};
