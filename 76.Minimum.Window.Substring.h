/**
 * Algorithms 76 Minimum Window Substring                                  Hard
 *
 * Given a string S and a string T, find the minimum window in S which will
 * contain all the characters in T in complexity O(n).
 *
 * For example,
 *
 * S = "ADOBECODEBANC"
 * T = "ABC"
 *
 * Minimum window is "BANC".
 *
 * Note:
 * If there is no such window in S that covers all characters in T, return the
 * emtpy string "".
 *
 * If there are multiple such windows, you are guaranteed that there will
 * always be only one unique minimum window in S.
 *
 * Tags: Hash Table, Two Pointers, String
 * Similar Problems: (H) Substring with Concatenation of All Words,
 *                   (M) Minimum Size Subarray Sum,
 *                   (H) Sliding Window Maximum
 */

#include <string>
#include <unordered_map>
#include <cstring>
#include <queue>

class Solution {
public:
    std::string minWindow( const std::string & s, const std::string & t ) {
        return min_window_impl_2( s, t );
    }
private:
    /**
     * O( n + m ) runtime, O( m ) space - my implementation
     */
    std::string min_window_impl_1( const std::string & s,
                                   const std::string & t ) {
        std::unordered_map< char, int > h;
        for ( int i = 0; i < t.length(); ++i )
            ++h[ t[ i ] ];
        const int target_matches = h.size();

        int i = -1;
        int j = -1;
        int matches = 0;
        int max_i = -1;
        int max_j = -1;
        for ( int k = 0; k < s.length(); ++k ) {
            std::unordered_map< char, int >::iterator
                it = h.find( s[ k ] );
            if ( it != h.end() ) {
                if ( i == -1 ) i = k;
                --it->second;
                if ( it->second == 0 ) {
                    if ( matches != target_matches )
                        ++matches;
                } else if ( it->second < 0 ) {
                    int z = i;
                    std::unordered_map< char, int >::iterator
                        it2 = h.find( s[ z ] );
                    while ( z < s.length()
                         && ( it2 == h.end() || it2->second < 0 ) ) {
                        if ( it2 != h.end() ) {
                            ++it2->second;
                        }
                        it2 = h.find( s[ ++z ] );
                    }
                    i = z;
                }
                if ( matches == target_matches ) {
                    j = k;
                    if ( max_i == -1 || ( j - i ) < ( max_j - max_i ) ) {
                        max_i = i;
                        max_j = j;
                    }
                }
            }
        }

        if ( max_j == -1 ) return std::string();
        else return s.substr( max_i, max_j - max_i + 1 );
    }
    /**
     * O( n + m ) runtime, O( m ) space - using array as hashtable
     */
    std::string min_window_impl_2( const std::string & s,
                                   const std::string & t ) {
        int needToFind[ 256 ];
        int hasFound[ 256 ];
        std::queue< int > q;
        std::memset( needToFind, 0, sizeof( needToFind ) );
        std::memset( hasFound, 0, sizeof( hasFound ) );

        for ( int i = 0; i < t.length(); ++i )
            ++needToFind[ t[ i ] ];

        int i = -1;
        int max_i = -1;
        int max_j = -1;
        int count = 0;
        for ( int k = 0; k < s.length(); ++k ) {
            if ( needToFind[ s[ k ] ] == 0 ) continue;
            ++hasFound[ s[ k ] ];
            q.push( k );
            if ( hasFound[ s[ k ] ] <= needToFind[ s[ k ] ] )
                ++count;

            if ( count == t.length() ) {
                while ( ! q.empty()
                     && ( i == -1
                       || hasFound[ s[ i ] ] > needToFind[ s[ i ] ] ) ) {
                    if ( i != -1 )
                        --hasFound[ s[ i ] ];
                    i = q.front();
                    q.pop();
                }
                if ( max_i == -1 || k - i < max_j - max_i ) {
                    max_j = k;
                    max_i = i;
                }
            }
        }

        if ( max_i != -1 ) {
            return s.substr( max_i, max_j - max_i + 1 );
        } else
            return std::string();
    }
};

