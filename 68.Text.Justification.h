/**
 * Algorithms 68 Text Justification                                        Hard
 * 
 * Given an array of words and a length L, format the text such that each line
 * has exactly L characters and is fully (left and right) justified.
 * 
 * You should pack your words in a greedy approach; that is, pack as many words
 * as you can in each line. Pad extra spaces ' ' when necessary so that each
 * line has exactly L characters.
 * 
 * Extra spaces between words should be distributed as evenly as possible. If
 * the number of spaces on a line do not divide evenly between words, the empty
 * slots on the left will be assigned more spaces than the slots on the right.
 *
 * For the last line of text, it should be left justified and no extra space is
 * inserted between words.
 *
 * For example,
 * words: ["This", "is", "an", "example", "of", "text", "justification."]
 * L: 16.
 * 
 * Return the formatted lines as:
 * [
 *    "This    is    an",
 *    "example  of text",
 *    "justification.  "
 * ]
 * Note: Each word is guaranteed not to exceed L in length.
 * 
 * click to show corner cases.
 * 
 * Corner Cases:
 * * A line other than the last line might contain only one word. What should
 *   you do in this case? In this case, that line should be left-justified.
 *
 * Tags: String
 */

#include <vector>
#include <string>

class Solution {
public:
    std::vector< std::string >
    fullJustify( std::vector< std::string > & words,
                 const int                    maxWidth ) {
        const int n = words.size();
        std::vector< std::string > results;
        int i = 0;
        while ( i < n ) {
            std::string line;
            //assume words[ i ].length() <= maxWidth
            int count     = words[ i ].length();
            int words_len = words[ i ].length();
            int j = i + 1;
            while ( j < n ) {
                count += 1 + words[ j ].length();
                words_len += words[ j ].length();
                if ( count > maxWidth ) {
                    words_len -= words[ j ].length();
                    break;
                }
                ++j;
            }
            if ( j == n ) {
                line += words[ i ];
                for ( int k = i + 1; k < j; ++k ) {
                    line += ' ';
                    line += words[ k ];
                }
                line.append( maxWidth - line.length(), ' ' );
            } else {
                int total_spaces = maxWidth - words_len;
                int num_words = j - i;
                if ( num_words == 1 ) {
                    line += words[ i ];
                    line.append( maxWidth - line.length(), ' ' );
                } else {
                    int spaces_between = total_spaces / ( num_words - 1 );
                    int extra = total_spaces % ( num_words - 1 );
                    line += words[ i ];
                    for ( int k = i + 1; k < j; ++k ) {
                        line.append( spaces_between + ( extra-- > 0 ), ' ' );
                        line += words[ k ];
                    }
                }
            }
            results.push_back( line );
            i = j;
        }
        return results;
    }
};
