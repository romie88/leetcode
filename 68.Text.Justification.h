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
        std::vector< std::string > lines;
        int total_length = 0;
        int i = 0;
        while ( i < words.size() ) {
            total_length += words[ i ].length();
            int start = i;
            ++i;
            while ( i < words.size()
                 && total_length + 1 + words[ i ].length() <= maxWidth ) {
                total_length += 1 + words[ i ].length();
                ++i;
            }
            
            std::string one_line;
            if ( i == words.size() ) {
                one_line += words[ start ];
                for ( int k = start + 1; k < i; ++k ) {
                    one_line += ' ';
                    one_line += words[ k ];
                }
                one_line += std::string( maxWidth - total_length, ' ' );  
            } else {
                justify_one_line( words, start, i, total_length, maxWidth,
                                  one_line );
            }
            lines.push_back( one_line );
            total_length = 0;
        }
        return lines;
    }
private:
    void justify_one_line( const std::vector< std::string > & words,
                           const int                          start,
                           const int                          end,
                           const int                          total_length,
                           const int                          max_width,
                           std::string                      & one_line ) {
        int num_words = end - start;
        int num_spaces = max_width - total_length + num_words - 1;
        if ( num_words == 1 ) {
            one_line = words[ start ];
            one_line += std::string( num_spaces, ' ' );
        } else {
            int k = start;
            int x = num_words - 1;
            one_line = words[ k++ ];
            while ( k < end ) {
                int s = num_spaces / x;
                if ( num_spaces % x ) ++s;
                one_line += std::string( s, ' ' );
                one_line += words[ k++ ];
                --x;
                num_spaces -= s;
            }
        }
    }
};
