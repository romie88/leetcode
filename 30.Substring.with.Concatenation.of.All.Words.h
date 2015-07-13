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
 * Similar Problems: (H) Minimum Window Substring
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>

class Solution {
public:
    std::vector< int > findSubstring( const std::string & s,
                                      const std::vector< std::string > & words ) {
        return find_substring_moving_window( s, words );
    }
private:
    /**
     * O( n * m * w ) runtime, O( m * w ) space - brute force
     * where n is the length of s, m is the size of words, and, w is the length
     * of each word.
     */
    std::vector< int > find_substring_brute_force_iterative(
            const std::string                & s,
            const std::vector< std::string > & words ) {
        if ( words.empty() ) throw std::invalid_argument( "words is empty" );
        
        //m is a map from word to word counts
        std::unordered_map< std::string, int > m;
        for ( const auto & w : words )
            ++m[ w ];
        
        std::vector< int > results;
        const int word_len = words[ 0 ].length();
        const int num_words = words.size();
        const int s_len = s.length();
        for ( int i = 0; i <= s_len - word_len * num_words; ++i ) {
            //this copy is very expensive
            std::unordered_map< std::string, int > m2 = m;
            bool matched = true;
            for ( int j = 0; j < num_words; ++j ) {
                const std::string & w = s.substr( i + j * word_len, word_len );
                const auto it = m2.find( w );
                if ( it == m2.end() ) {
                    matched = false;
                    break;
                } else {
                    if ( it->second ) --it->second;
                    else {
                        matched = false;
                        break;
                    }
                }
            }
            if ( matched ) results.push_back( i );
        }
        return results;
    }
    /**
     * A recursive brute force implementation saves the copying of the hash map.
     */
    std::vector< int > find_substring_brute_force_recursive(
            const std::string                & s,
            const std::vector< std::string > & words ) {
        if ( words.empty() ) throw std::invalid_argument( "words is empty" );
        
        //m is a map from word to word counts
        std::unordered_map< std::string, int > m;
        for ( const auto & w : words )
            ++m[ w ];
        
        std::vector< int > results;
        const int word_len = words[ 0 ].length();
        const int num_words = words.size();
        const int s_len = s.length();
        for ( int i = 0; i <= s_len - word_len * num_words; ++i ) {
            if ( helper( s, i, m, num_words, word_len ) )
                results.push_back( i );
        }
        return results;
    }
    bool helper( const std::string & s, const int i,
                 std::unordered_map< std::string, int > & m,
                 const int num_words,
                 const int word_len ) {
        if ( num_words == 0 ) return true;
        const std::string & w = s.substr( i, word_len );
        const auto it = m.find( w );
        if ( it != m.end() && it->second > 0 ) {
            --it->second;
            bool b = helper( s, i + word_len, m, num_words - 1, word_len );
            ++it->second;
            return b;
        } else
            return false;
    }
    /**
     * O( m * n ) runtime, O( m * w ) space - a moving window approach
     * where n is the length of s, m is the size of words, and, w is the length
     * of each word.
     */
    std::vector< int > find_substring_moving_window(
            const std::string                & s,
            const std::vector< std::string > & words ) {
        if ( words.empty() ) throw std::invalid_argument( "words is empty" );
        
        //m is a map from word to word counts
        std::unordered_map< std::string, int > m;
        for ( const auto & w : words )
            ++m[ w ];
        
        std::vector< int > results;
        const int word_len = words[ 0 ].length();
        const int num_words = words.size();
        const int s_len = s.length();
        //in order to try the moving window approach we move the window
        //by length of a word; to avoid missing any potential solution
        //we check all the starting indices from i = 0 to word_len.
        //The runtime for this outer loop is num_words.
        for ( int i = 0; i < word_len; ++i ) {
            std::unordered_map< std::string, int > m2;
            int win_start = i;
            int count = 0;//number of words matched
            //The runtime for this inner loop is
            //2 * word_len * ( s_len / word_len ) (floor)
            //because each word enters and leaves the window just once
            for ( int j = i; j <= s_len - word_len; j += word_len ) {
                const std::string & w = s.substr( j, word_len );
                const auto it = m.find( w );
                if ( it != m.end() ) {
                    ++m2[ w ];
                    if ( m2[ w ] <= m[ w ] ) ++count;
                    else {
                        //while ( m2[ w ] > m[ w ] ] )
                        for ( int k = win_start; ; k += word_len ) {
                            const std::string & w2 = s.substr( k, word_len );
                            --m2[ w2 ];
                            if ( w2 == w ) {
                                win_start = k + word_len;
                                break;
                            }
                            --count;
                        }
                    }
                    if ( count == num_words )
                        results.push_back( win_start );
                } else {
                    m2.clear();
                    win_start = j + word_len;
                    count = 0;
                }
            }
        }
        return results;
    }
};
#if 0
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
#endif
