/**
 * Algorithms 32 Longest Valid Parentheses                                 Hard
 * 
 * Given a string containing just the characters '(' and ')', find the length
 * of the longest valid (well-formed) parentheses substring.
 * 
 * For "(()", the longest valid parentheses substring is "()", which has length
 * = 2.
 * 
 * Another example is ")()())", where the longest valid parentheses substring
 * is "()()", which has length = 4.
 * 
 * Tags: Dynamic Programming, String
 * Similar Problems: (E) Valid Parentheses
 */

#include <vector>
#include <string>
#include <stack>
#include <algorithm>

class Solution {
public:
    int longestValidParentheses( const std::string & s ) {
        return longest_valid_parentheses_DP( s );
    }
private:
    /**
     * O( n ) runtime, O( n ) space - DP
     * 
     * Define D[ i ] to be the length of longest valid parentheses ending at
     * s[ i - 1 ] and D[ 0 ] = 0.
     * 
     * If s[ i - 1 ] = '(' then D[ i ] = 0
     * If s[ i - 1 ] = ')' then
     * let j = ( i - 1 ) - D[ i - 1 ] - 1 = i - 2 + D[ i - 1 ]
     * if j >= 0 && s[ j ] == '(' then D[ i ] = 2 + D[ i - 1 ] + D[ j ];
     * otherwise D[ i ] = 0.
     */
    int longest_valid_parentheses_DP( const std::string & s ) {
        const int n = s.length();
        std::vector< int > D( n + 1, 0 );
        int max_len = 0;
        for ( int i = 1; i <= n; ++i ) {
            if ( s[ i - 1 ] == '(' ) D[ i ] = 0;
            else {
                int j = i - 2 - D[ i - 1 ];
                if ( j >= 0 && s[ j ] == '(' ) {
                    D[ i ] = 2 + D[ i - 1 ] + D[ j ];
                    max_len = std::max( max_len, D[ i ] );
                } else {
                    D[ i ] = 0;
                }
            }
        }
        return max_len;
    }
    /**
     * O( n ) runtime, O( n ) space - stack
     * 
     * Use a stack to track the unmatched parentheses' indices.
     * Note that with indices available we can know what character it is by
     * indexing into the string s thus no need to store both the character
     * and the index in the stack.
     * 
     * Try cases like ()() and (())
     */
    int longest_valid_parentheses_stack( const std::string & s ) {
        int max_len = 0;
        std::stack< int > stk;
        for ( int i = 0; i < s.length(); ++i ) {
            if ( s[ i ] == '(' ) {
                stk.push( i );
            } else {
                if ( stk.empty() || s[ stk.top() ] == ')' ) {
                    stk.push( i );
                } else {
                    stk.pop();
                    //max_len = std::max( max_len,
                    //                    i - ( stk.empty() ? -1 : stk.top() ) );
                    int len = 0;
                    if ( stk.empty() ) len = i + 1;
                    else               len = i - stk.top();
                    max_len = std::max( max_len, len );
                }
            }
        }
        return max_len;
    }
};
