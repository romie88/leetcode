/**
 * Algorithms 20 Valid Parentheses                                        Easy
 *
 * Given a string containing just the characters '(', ')', '{', '}', '[' and
 * ']', determine if the input string is valid.
 *
 * The brackets must close in the correct order, "()" and "()[]{}" are all
 * valid but "(]" and "([)]" are not.
 *
 * Tags: Stack, String
 */

#include <stack>

class Solution {
public:
    bool isValid( const std::string & s ) {
        std::stack< char > stk;
        for ( const auto c : s ) {
            if ( stk.empty() || c == '(' || c == '{' || c == '[' )
                stk.push( c );
            else {
                if ( ( c == ')' && stk.top() == '(' )
                  || ( c == '}' && stk.top() == '{' )
                  || ( c == ']' && stk.top() == '[' ) )
                    stk.pop();
                else
                    return false;
            }
        }
        return stk.empty();
    }
};
