/**
 * Algorithms 5 Longest Palindromic Substring                              Hard
 * 
 * Given a string S, find the longest palindromic substring in S. You may
 * assume that the maximum length of S is 1000, and there exists one unique
 * longest palindromic substring.
 * 
 * Tags: String
 * Similar Problems: (H) Shortest Palindrome
 */

#include <string>
#include <vector>

class Solution {
public:
    std::string longestPalindrome( const std::string & s ) {
        return longest_palindrome_expand( s );
    }
private:
    /**
     * A common mistake:
     * 
     * Reverse S and become S'. Find the longest common substring between S
     * and S' which must also be the longest palindromic substring.
     * 
     * A counter example: S = "abacdfgdcaba", S' = "abacdgfdcaba"
     * The longest common substring between S and S' is "abacd" which is not a
     * valid palindrome.
     * 
     * We can see that the longest common substring method fails when there
     * exists a reversed copy of a non-palindromic substring in some other
     * part of S. To rectifythis, each time we find a longest common substring
     * candidate, we check if the substring's indices are the same as the
     * reversed substring's original indices. If it is, then we attempt to
     * update the longest palindrome found so far; if not, we skip this and
     * find the next candidate.
     * 
     * This results an O( n^2 ) runtime, O( n^2 ) space DP solution (can be
     * improved to use O( n ) space).
     */
    
    /**
     * O(n^3) runtime, O(1) space - Brute force
     * pick all possible starting and ending positions for a substring
     * and verify it is a palindrome.
     * There are C( n, 2 ) such substrings (excluding the trivial solution
     * where a character itself is a palindrome). Since verifying each
     * substring takes O( n ) time, the run time complexity is O( n^3 ).
     */

    /**
     * O( n^2 ) runtime, O( n^2 ) space - Dynamic programming
     *
     * Define P( i, j ) == true if substring s[ i ... j ] is a palindrome
     * where i <= j.
     * 
     * P( i, i )     = true   0 <= i < n
     * P( i, i + 1 ) = true   if s[ i ] == s[ i + 1 ] and 0 <= i < n - 1
     * P( i, j )     = P( i + 1, j - 1 ) == true && s[ i ] == s[ j ]
     */
    std::string longest_palindrome_DP( const std::string & s ) {
        if ( s.empty() ) return std::string();
        
        const int n = s.length();
        std::vector< std::vector< bool > >
                P( n, std::vector< bool >( n, false ) );
            
        int max_i = n - 1;
        int max_j = n - 1;
        int max_len = 1;
        P[ n - 1 ][ n - 1 ] = true;
        for ( int i = n - 2; i >= 0; --i ) {
            P[ i ][ i ] = true;
            P[ i ][ i + 1 ] = ( s[ i ] == s[ i + 1 ] );
            if ( P[ i ][ i + 1 ] && 2 > max_len ) {
                max_len = 2;
                max_i = i;
                max_j = i + 1;
            }
            for ( int j = i + 2; j < n; ++j ) {
                P[ i ][ j ] = P[ i + 1 ][ j - 1 ] && s[ i ] == s[ j ];
                if ( P[ i ][ j ] && j - i + 1 > max_len ) {
                    max_len = j - i + 1;
                    max_i = i;
                    max_j = j;
                }
            }
        }
        
        return s.substr( max_i, max_j - max_i + 1 );
    }
    /**
     * O( n^2 ) runtime, O( n ) space - Dynamic programming
     */
    std::string longest_palindrome_DP2( const std::string & s ) {
        if ( s.empty() ) return std::string();
        
        const int n = s.length();
        std::vector< bool > P( n, false );
            
        int max_i = n - 1;
        int max_j = n - 1;
        int max_len = 1;
        P[ n - 1 ] = true;
        for ( int i = n - 2; i >= 0; --i ) {
            for ( int j = n - 1; j >= i + 2; --j ) {
                P[ j ] = P[ j - 1 ] && s[ i ] == s[ j ];
                if ( P[ j ] && j - i + 1 > max_len ) {
                    max_len = j - i + 1;
                    max_i = i;
                    max_j = j;
                }
            }
            P[ i + 1 ] = ( s[ i ] == s[ i + 1 ] );
            if ( P[ i + 1 ] && 2 > max_len ) {
                max_len = 2;
                max_i = i;
                max_j = i + 1;
            }
            P[ i ] = true;
        }
        
        return s.substr( max_i, max_j - max_i + 1 );
    }
        
    /**
     * O(n^2) runtime, O(1) space - Simpler solution
     *
     * A palindrome mirrors around its center. Therefore, a palindrome
     * can be expanded from its center, and there are only 2n - 1 such centers.
     */
    std::string longest_palindrome_expand( const std::string & s ) {
        int max_len = 0;
        int max_i = -1, max_j = -1;
        for ( int i = 0; i < s.length(); ++i ) {
            int len1 = expand_around_center( s, i, i );
            int len2 = expand_around_center( s, i, i + 1 );
            int len = std::max( len1, len2 );
            if ( len > max_len ) {
                max_len = len;
                max_i   = i - ( len - 1 ) / 2;
                max_j   = i + len / 2;
            }
        }
        return s.substr( max_i, max_j - max_i + 1 );
    }
    
    int expand_around_center( const std::string & s, int left, int right ) {
        const int n = s.length();
        while ( left >= 0 && right < n && s[ left ] == s[ right ] ) {
            --left;
            ++right;
        }
        return right - left - 1;
    }
    
    /**
     * O( n ) runtime, O( n ) space - Manacher's algorithm
     * 
     * http://articles.leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
     * 
     * First, we transform the input string S to another string T by inserting
     * a special character '#' in between letters. Did you notice by inserting
     * special characters '#' in between letters, both palindromes of odd and
     * even lengths are handled graciously?
     * 
     * For example, S = "abaaba", T = "#a#b#a#a#b#a#".
     * 
     * To find the longest palindromic substring, we need to expand around each
     * T_i such that T_(i-d) ... T_(i+d) forms a palindrome. You should
     * immediately see that d is the length of the palindrome itself centered
     * at T_i.
     * 
     * We store intermediate result in an array P, where P[ i ] equals to the
     * length of the palindrome centers at T_i. The longest palindromic
     * substring would then be the maximum element in P.
     * 
     * Using the above example, we populate P as below:
     * 
     * T = # a # b # a # a # b # a #
     * P = 0 1 0 3 0 1 6 1 0 3 0 1 0
     * 
     * Looking at P, we immediately see that the longest palindrome is
     * "abaaba", as indicated by P[ 6 ] = 6.
     * 
     * Now, imagine that you draw an imaginary vertical line at the center of
     * the palindrome “abaaba”. Did you notice the numbers in P are symmetric
     * around this center? That’s not only it, try another palindrome "aba",
     * the numbers also reflect similar symmetric property. Is this a
     * coincidence? The answer is yes and no. This is only true subjected to a
     * condition, but anyway, we have great progress, since we can eliminate
     * recomputing part of P[ i ]’s.
     * 
     * Let us move on to a slightly more sophisticated example with more some
     * overlapping palindromes, where S = “babcbabcbaccba”.
     * 
     * index       2             9   11  13            20
     * var         L             i'  C   i             R
     *             |                 |                 |
     * T     = # b # a # b # c # b # a # b # c # b # a # c # c # b # a #
     *             |                 |                 |
     * P     = 0 1 0 3 0 1 0 7 0 1 0 9 0 ?             |
     * 
     * Above image shows T transformed from S = "babcbabcbaccba". Assumed that
     * you reached a state where table P is partially completed. The solid
     * line indicates that the center (C) of the palindrome "abcbabcba". The
     * two dotted vertical line indicates its left (L) and right (R) edges
     * respectively. You are at index i and its mirrored index around C is i'.
     * How would you calculate P[ i ] efficiently?
     * 
     * Assume that we have arrived at index i =13, and we need to calculate
     * P[ 13 ] (indicated by the question mark?). We first look at its mirrored
     * index i' around the palindrome's center C, which is index i' = 9.
     * 
     * index       2             9   11  13            20
     * var         L             i'  C   i             R
     *             |           --|-- | --|--           |
     * T     = # b # a # b # c # b # a # b # c # b # a # c # c # b # a #
     *             |                 |                 |
     * P     = 0 1 0 3 0 1 0 7 0 1 0 9 0 ?             |
     * 
     * Two two green solid lines above indicate the covered region by the two
     * palindromes centered at i and i'. We look at the mirrored index of i
     * around C, which is index i'. P[ i' ] = P[ 9 ] = 1. It is clear that
     * P[ i ] must also be 1, due to the symmetric property of a palindrome
     * around its center.
     * 
     * As you can see above, it is very obvious that P[ i ] = P[ i' ] = 1,
     * which must be true due to the symmetric property around a palindrome's
     * center. In fact, all three elements after C follow the symmetric
     * property (that is, P[ 12 ] = P[ 10 ] = 0, P[ 13 ] = P[ 9 ] = 1,
     * P[ 14 ] = P[ 8 ] = 0).
     * 
     * index       2         7       11      15        20
     * var         L         i'      C       i         R
     *             |                 |                 |
     * T     = # b # a # b # c # b # a # b # c # b # a # c # c # b # a #
     *             |                 |                 |
     * P     = 0 1 0 3 0 1 0 7 0 1 0 9 0 1 0 ?         |
     * 
     * Now we are at index i = 15, and its mirrored index around C is i' = 7.
     * Is P[ 15 ] = P[ 7 ] = 7?
     * 
     * Now we are at index i = 15. What’s the value of P[ i ]? If we follow the
     * symmetric property, the value of P[ i ] should be the same as
     * P[ i’ ] = 7. But this is wrong. If we expand around the center at
     * T[ 15 ], it forms the palindrome "a#b#c#b#a", which is actually shorter
     * than what is indicated by its symmetric counterpart. Why?
     * 
     * index       2         7       11      15        20
     * var         L         i'      C       i         R
     *             |         |       |       |         |
     *         ____-------------------......
     *                         ......-------------------____
     * T     = # b # a # b # c # b # a # b # c # b # a # c # c # b # a #
     *             |                 |                 |
     * P     = 0 1 0 3 0 1 0 7 0 1 0 9 0 1 0 ?         |
     * 
     * Lines are overlaid around the center at index i and i'. --- lines shows
     * the region that must match for both sides due to symmetric property
     * around C. ___ lines show the region that might not match for both
     * sides. ... lines show the region that crosses over the center.
     * 
     * It is clear that the two substrings in the region indicated by the two
     * --- lines must match exactly. Areas across the center (indicated by
     * ... lines) must also be symmetric. Notice carefully that P[ i' ] is 7
     * and it expands all the way across the left edge (L) of the palindrome
     * (indicated by the ___ lines), which does not fall under the symmetric
     * property of the palindrome anymore. All we know is P[ i ] >= 5, and to
     * find the real value of P[ i ] we have to do character matching by
     * expanding past the right edge (R). In this case, since
     * P[ 21 ] != P[ 9 ], we conclude that P[ i ] = 5.
     * 
     * Let’s summarize the key part of this algorithm as below:
     * 
     * if P[ i' ] < R - i
     *     P[ i ] = P[ i' ]
     * else
     *     P[ i ] >= std::min( P[ i' ], R - i )
     *     we have to expand past the right edge (R) to find P[ i ]
     * 
     * The final part is to determine when should we move the position of C
     * together with R to the right, which is easy:
     * 
     * If the palindrome centered at i does expand past R, we update C to i,
     * (the center of this new palindrome), and extend R to the new
     * palindrome’s right edge.
     * 
     * In each step, there are two possibilities. If P[ i ] <= R – i, we set
     * P[ i ] to P[ i’ ] which takes exactly one step. Otherwise we attempt to
     * change the palindrome’s center to i by expanding it starting at the
     * right edge, R. Extending R (the inner while loop) takes at most a total
     * of N steps, and positioning and testing each centers take a total of N
     * steps too. Therefore, this algorithm guarantees to finish in at most
     * 2*N steps, giving a linear time solution.
     * 
     * http://www.felix021.com/blog/read.php?2040
     * 
     * How to calculate P[ i ]? C is the center of the max palindrome centered
     * at C. R is the right edge, i.e., C + P[ C ].
     * 
     * If R > i:
     * 
     * int j = 2 * C - i; //j is the symmetric of i about C
     * if ( R - i > P[ j ] )
     *     P[ i ] = P[ j ];
     * else
     *     P[ i ] = R - i; //then we can expand and get P[ i ] maximized
     * 
     * Summarize the above it is actually P[ i ] = std::min( P[ j ], R - i );
     * 
     * If R <= i:
     * 
     * We do not have any information about P[ i ] we have to expand.
     * 
     * Actually if P[ j ] > R - i, because P[ C ] = R - C we have
     * P[ R + 1 ] != P[ 2 * C - R - 1 ]. If P[ i ] > R - i we can imply that
     * P[ C ] > R - C which is contraversial to P[ C ] is the max palindrome
     * length.
     * 
     * Thus we only need to expand beyond R - i when P[ j ] == R - i.
     * 
     * However when we implement all the logic we will find that it can be
     * dramatically simplified if we just set P[ i ] = std::min( P[ j ], R - i )
     * if R > i, otherwise P[ i ] = 0; then always try to expand. The expansion
     * will definitely fail immediately if P[ j ] != R - i.
     */
    std::string preprocess_manacher( const std::string & s ) {
        std::string t;
        for ( int i = 0; i < s.length(); ++i ) {
            t += '#';
            t += s[ i ];
        }
        t += '#';
        return t;
    }
    std::string longest_palindrome_manacher( const std::string & s ) {
        std::string t = preprocess_manacher( s );
        std::vector< int > P( t.length(), 0 );
        const int n = t.length();
        int R = 0;//right edge
        int C = 0;//center
        //the first and the last character # has P[ 0 ] and P[ n - 1 ] as 0.
        for ( int i = 1; i < n - 1; ++i ) {
            if ( i < R ) {
                int j = 2 * C - i;
                if ( P[ j ] == R - i ) {
                    P[ j ] = R - i;
                    while ( i - P[ i ] - 1 >= 0
                         && i + P[ i ] + 1 < n
                         && t[ i - P[ i ] - 1 ] == t[ i + P[ i ] + 1 ] )
                        ++P[ i ];
                } else {
                    P[ i ] = std::min( P[ j ], R - i );
                }
            } else {
                while ( i - P[ i ] - 1 >= 0
                     && i + P[ i ] + 1 < n
                     && t[ i - P[ i ] - 1 ] == t[ i + P[ i ] + 1 ] )
                    ++P[ i ];
            }
            
            if ( i + P[ i ] > R ) {
                C = i;
                R = i + P[ i ];
            }
        }
        
        int max_len = P[ 0 ];
        int max_i   = 0;
        for ( int i = 1; i < n; ++i ) {
            if ( max_len < P[ i ] ) {
                max_i = i;
                max_len = P[ i ];
            }
        }
        
        return s.substr( ( max_i - max_len ) / 2, max_len );
    }
    
    /**
     * A better simplified manacher algorithm implementation
     */
    std::string longest_palindrome_manacher( const std::string & s ) {
        std::string t = preprocess_manacher( s );
        std::vector< int > P( t.length(), 0 );
        const int n = t.length();
        int R = 0;//right edge
        int C = 0;//center
        //the first and the last character # has P[ 0 ] and P[ n - 1 ] as 0.
        for ( int i = 1; i < n - 1; ++i ) {
            int j = C - ( C - i );//symmetric j
            P[ i ] = R > i ? std::min( P[ j ], R - i ) : 0;
            //no matter R > i or not, P[ j ] and R - i relation
            //we always try to expand around i
            while ( i - P[ i ] - 1 >= 0
                 && i + P[ i ] + 1 < n
                 && t[ i - P[ i ] - 1 ] == t[ i + P[ i ] + 1 ] )
                ++P[ i ];
        }
        
        int max_len = P[ 0 ];
        int max_i   = 0;
        for ( int i = 1; i < n; ++i ) {
            if ( max_len < P[ i ] ) {
                max_i = i;
                max_len = P[ i ];
            }
        }
        
        return s.substr( ( max_i - max_len ) / 2, max_len );
    }
    
    /**
     * Another solution - suffix trees. O( n log n ) runtime
     */
};
