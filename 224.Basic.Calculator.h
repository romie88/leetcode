/**
 * Algorithms 224 Basic Calculator                                       Medium
 * 
 * Implement a basic calculator to evaluate a simple expression string.
 * 
 * The expression string may contain open ( and closing parentheses ), the plus
 * + or minus sign -, non-negative integers and empty spaces .
 * 
 * You may assume that the given expression is always valid.
 * 
 * Some examples:
 * 
 * "1 + 1" = 2
 * " 2-1 + 2 " = 3
 * "(1+(4+5+2)-3)+(6+8)" = 23
 * 
 * Note: Do not use the eval built-in library function.
 * 
 * Tags: Stack, Math
 */

#include <string>
#include <stack>
#include <stdexcept>

class Solution {
public:
    int calculate( const std::string & s ) {
        std::string t;
        infix_to_postfix( s, t );
        return evaluate_postfix( t );
    }
private:
    int get_operator_precedence( const char c ) {
        switch ( c ) {
            case '(': return 0;
            case '*':
            case '/': return 2;
            case '+':
            case '-': return 1;
            default: throw std::invalid_argument( "unknown operator" );
        }
    }
    void infix_to_postfix( const std::string & s, std::string & t ) {
        std::stack< char > stk;
        for ( int i = 0; i < s.length(); ++i ) {
            if ( s[ i ] == ' ' )
                continue;
            else if ( s[ i ] == '(' )
                stk.push( s[ i ] );
            else if ( s[ i ] == ')' ) {
                while ( ! stk.empty() && stk.top() != '(' ) {
                    t += stk.top();
                    stk.pop();
                }
                if ( stk.top() == '(' )
                    stk.pop();
                else
                    throw std::invalid_argument( "unmatched )" );
            } else if ( s[ i ] == '+'
                     || s[ i ] == '-'
                     || s[ i ] == '*'
                     || s[ i ] == '/' ) {
                int p = get_operator_precedence( s[ i ] );
                while ( ! stk.empty()
                     && p <= get_operator_precedence( stk.top() ) ) {
                    t += stk.top();
                    stk.pop();
                }
                stk.push( s[ i ] );
            } else {
                while ( std::isdigit( s[ i ] ) ) {
                    t += s[ i ];
                    ++i;
                }
                t += ' ';
                --i;
            }
        }
        while ( ! stk.empty() ) {
            t += stk.top();
            stk.pop();
        }
    }
    int evaluate_postfix( const std::string & s ) {
        std::stack< int > stk;
        for ( int i = 0; i < s.length(); ++i ) {
            if ( s[ i ] == ' ' ) continue;
            else if ( s[ i ] == '+'
                   || s[ i ] == '-'
                   || s[ i ] == '*'
                   || s[ i ] == '/' ) {
                if ( stk.empty() )
                    throw std::invalid_argument( "missing operand" );
                int op1 = stk.top();
                stk.pop();
                if ( stk.empty() )
                    throw std::invalid_argument( "missing operand" );
                int op2 = stk.top();
                stk.pop();
                switch ( s[ i ] ) {
                    case '+': stk.push( op1 + op2 ); break;
                    case '-': stk.push( op2 - op1 ); break;
                    case '*': stk.push( op1 * op2 ); break;
                    case '/': stk.push( op2 / op1 ); break;
                }
            } else if ( std::isdigit( s[ i ] ) ) {
                int op = 0;
                while ( std::isdigit( s[ i ] ) ) {
                    op = op * 10 + s[ i ] - '0';
                    ++i;
                }
                --i;
                stk.push( op );
            } else {
                throw std::invalid_argument( "unknown characters" );
            }
        }
        if ( stk.size() == 1 )
            return stk.top();
        else
            throw std::invalid_argument( "still operands left" );
    }
};
