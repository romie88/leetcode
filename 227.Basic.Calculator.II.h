/**
 * 227 Basic Calculator II                                               Medium
 * 
 * Implement a basic calculator to evaluate a simple expression string.
 * 
 * The expression string contains only non-negative integers, +, -, *, /
 * operators and empty spaces . The integer division should truncate toward
 * zero.
 * 
 * You may assume that the given expression is always valid.
 * 
 * Some examples:
 * 
 * "3+2*2" = 7
 * " 3/2 " = 1
 * " 3+5 / 2 " = 5
 * 
 * Note: Do not use the eval built-in library function.
 * 
 * Credits:
 * Special thanks to @ts for adding this problem and creating all test cases.
 * 
 * Tags:
 */

#include <string>
#include <stack>
#include <stdexcept>
#include <cctype>

class Solution {
public:
    int calculate( const std::string & s ) {
        std::string postfix = infix_to_postfix( s );
        return evaluate_postfix( postfix );
    }
private:
    int op_precedence( const char op ) {
        switch ( op ) {
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
                return 2;
            case '(':
                return 3;
            default:
                throw std::invalid_argument( "unknown operator" );
        }
    }
    
    std::string infix_to_postfix( const std::string & s ) {
        std::string t;
        std::stack< char > stk;
        for ( int i = 0; i < s.length(); ++i ) {
            if ( std::isdigit( s[ i ] ) ) {
                while ( i < s.length() && std::isdigit( s[ i ] ) ) {
                    t += s[ i ];
                    ++i;
                }
                --i;
                t += ' ';
            } else if ( s[ i ] == '*'
                     || s[ i ] == '/'
                     || s[ i ] == '+'
                     || s[ i ] == '-'
                     || s[ i ] == '(' ) {
                if ( stk.empty()
                  || op_precedence( stk.top() ) < op_precedence( s[ i ] ) ) {
                    stk.push( s[ i ] );  
                } else {
                    while ( ! stk.empty()
                         && op_precedence( stk.top() ) >= op_precedence( s[ i ] ) ) {
                        t += stk.top();
                        stk.pop();
                    }
                    stk.push( s[ i ] );
                }
            } else if ( s[ i ] == ')' ) {
                while ( ! stk.empty() && stk.top() != '(' ) {
                    t += stk.top();
                    stk.pop();
                }
                if ( stk.empty() ) throw std::invalid_argument( "unmatched )" );
                else stk.pop();
            } else if ( ! std::isspace( s[ i ] ) ) {
                throw std::invalid_argument( "unknown characters" );
            }
        }
        while ( ! stk.empty() ) {
            t += stk.top();
            stk.pop();
        }
        return t;
    }
    
    int evaluate_postfix( const std::string & t ) {
        std::stack< int > stk;
        for ( int i = 0; i < t.length(); ++i ) {
            if ( std::isdigit( t[ i ] ) ) {
                int num = 0;
                while ( i < t.length() && std::isdigit( t[ i ] ) ) {
                    num = num * 10 + ( t[ i ] - '0' );
                    ++i;
                }
                --i;
                stk.push( num );
            } else if ( t[ i ] == '*'
                     || t[ i ] == '/'
                     || t[ i ] == '+'
                     || t[ i ] == '-' ) {
                if ( stk.empty() ) throw std::invalid_argument( "missing operand" );
                int op1 = stk.top();
                stk.pop();
                if ( stk.empty() ) throw std::invalid_argument( "missing operand" );
                int op2 = stk.top();
                stk.pop();
                int result;
                switch ( t[ i ] ) {
                    case '+':
                        result = op1 + op2;
                        break;
                    case '-':
                        result = op2 - op1;
                        break;
                    case '*':
                        result = op1 * op2;
                        break;
                    case '/':
                        result = op2 / op1;
                        break;
                    default:
                        throw std::invalid_argument( "unknown operator" );
                }
                stk.push( result );
            } else if ( ! std::isspace( t[ i ] ) ) {
                throw std::invalid_argument( "unknown characters" );
            }
        }
        if ( stk.size() > 1 ) throw std::invalid_argument( "operands left" );
        return stk.top();
    }
};
