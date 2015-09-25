/**
 * Algorithms 282 Expression Add Operators                                 Hard
 * 
 * Given a string that contains only digits 0-9 and a target value, return all
 * possibilities to add operators +, -, or * between the digits so they
 * evaluate to the target value.
 * 
 * Examples:
 * 
 * "123", 6 -> ["1+2+3", "1*2*3"] 
 * "232", 8 -> ["2*3+2", "2+3*2"]
 * "00", 0 -> ["0+0", "0-0", "0*0"]
 * "3456237490", 9191 -> []
 * 
 * Credits:
 * 
 * Special thanks to @davidtan1890 for adding this problem and creating all
 * test cases.
 * 
 * Tags: Divide and Conquer
 * Similar Problems: (M) Evaluate Reverse Polish Notation,
 *                   (M) Basic Calculator,
 *                   (M) Basic Calculator II,
 *                   (M) Different Ways to Add Parentheses
 */

#include <string>
#include <vector>
#include <stdexcept>
#include <stack>
#include <limits>

/**
 * My naive implementation TLE
 */
#if 0
class Solution {
public:
    std::vector< std::string >
    addOperators( const std::string & num, const int target ) {
        
        std::stack< int > num_stack;
        std::stack< char > op_stack;
        std::vector< std::pair< int, char > > one_expr_info;
        std::vector< std::string > all_exprs;
        add_operators_impl( num, 0, target, num_stack, op_stack, one_expr_info, all_exprs );
        return all_exprs;
    }
private:
    void add_operators_impl( const std::string          & num,
                             const int                    start,
                             const int                    target,
                             std::stack< int >          & num_stack,
                             std::stack< char >         & op_stack,
                             std::vector< std::pair< int, char > > & one_expr_info,
                             std::vector< std::string > & all_exprs ) {
               
        int new_op = 0;
        if ( ! op_stack.empty() ) {
            if ( start >= num.length() ) return;
            if ( convert_to_int( num, start, num.length() - start, new_op ) ) {
                std::stack< int > ns( num_stack );
                std::stack< char > ops( op_stack );
                ns.push( new_op );
                if ( target == evaluate( ns, ops ) )
                    all_exprs.push_back( generate_expr( num, one_expr_info ) );
            }
        }
        
        int len = 1;
        while ( start + len <= num.length()
             && convert_to_int( num, start, len, new_op ) ) {
            
            num_stack.push( new_op );
            
            one_expr_info.push_back( std::make_pair( start + len, '+' ) );
            if ( ! op_stack.empty() && op_stack.top() == '*' ) {
                int op2 = num_stack.top(); num_stack.pop();
                int op1 = num_stack.top(); num_stack.pop();
                num_stack.push( op1 * op2 );
                op_stack.pop();
                op_stack.push( '+' );
                add_operators_impl( num, start + len, target, num_stack, op_stack, one_expr_info, all_exprs );
                op_stack.pop();
                op_stack.push( '*' );
                num_stack.pop();
                num_stack.push( op1 );
                num_stack.push( op2 );
            } else {
                op_stack.push( '+' );
                add_operators_impl( num, start + len, target, num_stack, op_stack, one_expr_info, all_exprs );
                op_stack.pop();
            }
            one_expr_info.pop_back();
            
            one_expr_info.push_back( std::make_pair( start + len, '-' ) );
            if ( ! op_stack.empty() && op_stack.top() == '*' ) {
                int op2 = num_stack.top(); num_stack.pop();
                int op1 = num_stack.top(); num_stack.pop();
                num_stack.push( op1 * op2 );
                op_stack.pop();
                op_stack.push( '-' );
                add_operators_impl( num, start + len, target, num_stack, op_stack, one_expr_info, all_exprs );
                op_stack.pop();
                op_stack.push( '*' );
                num_stack.pop();
                num_stack.push( op1 );
                num_stack.push( op2 );
            } else {
                op_stack.push( '-' );
                add_operators_impl( num, start + len, target, num_stack, op_stack, one_expr_info, all_exprs );
                op_stack.pop();
            }
            one_expr_info.pop_back();
            
            one_expr_info.push_back( std::make_pair( start + len, '*' ) );
            op_stack.push( '*' );
            add_operators_impl( num, start + len, target, num_stack, op_stack, one_expr_info, all_exprs );
            op_stack.pop();
            one_expr_info.pop_back();
            
            num_stack.pop();
            ++len;
        }
    }
    bool convert_to_int( const std::string & s,
                         const int           start,
                         const int           len,
                         int               & result ) {
        try {
            std::size_t pos;
            
            result = std::stoi( s.substr( start, len ), &pos );
            return true;
        } catch ( const std::out_of_range & e ) {
            return false;
        }
    }
    int evaluate( std::stack< int  > & num_stack,
                  std::stack< char > & op_stack ) {
        while ( ! op_stack.empty() ) {
            int n2 = num_stack.top(); num_stack.pop();
            int n1 = num_stack.top(); num_stack.pop();
            char op = op_stack.top(); op_stack.pop();
            int result;
            switch ( op ) {
                case '+': result = n1 + n2; break;
                case '-': result = n1 - n2; break;
                case '*': result = n1 * n2; break;
            }
            num_stack.push( result );
        }
        return num_stack.top();
    }
    std::string generate_expr( const std::string & num,
                               const std::vector< std::pair< int, char > > & one_expr_info ) {
        std::string result;
        int j = 0;
        for ( int i = 0; i < one_expr_info.size(); ++i ) {
            result += num.substr( j, one_expr_info[ i ].first - j );
            result += one_expr_info[ i ].second;
            j = one_expr_info[ i ].first;
        }
        result = num.substr( j, num.length() - j );
        
        return result;
    }
};
#endif

/**
 * The first accepted version
 */
#if 0
class Solution {
public:
    std::vector< std::string > addOperators(
            const std::string & num,
            const int           target ) {
        std::string expr;
        std::vector< std::string > all_exprs;
        add_operators_impl( num, target, 0, 0, 0, expr, all_exprs );
        return all_exprs;
    }
private:
    /**
     * some little optimization can be applied here:
     * remove the convert_to_int() call because each time it is invoked
     * in the loop we do not employ the previously new_op calculated.
     */
    void add_operators_impl( const std::string          & num,
                             const int                    target,
                             const int                    start,
                             const int                    prev_result,
                             const int                    prev_op,
                             std::string                & expr,
                             std::vector< std::string > & all_exprs ) {
        if ( start == num.length() && prev_result + prev_op == target ) {
            all_exprs.push_back( expr );
            return;
        }
        
        for ( int len = 1; len <= num.length() - start; ++len ) {
            int new_op = 0;
            if ( ! convert_to_int( num, start, len, new_op ) ) break;
            if ( expr.empty() ) {
                expr += num.substr( start, len );
                add_operators_impl( num, target, start + len, 0, new_op, expr, all_exprs );
                expr.resize( expr.length() - len );
            } else {
                expr += '*';
                expr += num.substr( start, len );
                add_operators_impl( num, target, start + len, prev_result, prev_op * new_op, expr, all_exprs );
                expr.resize( expr.length() - len - 1 );
                
                expr += '+';
                expr += num.substr( start, len );
                add_operators_impl( num, target, start + len, prev_result + prev_op, new_op, expr, all_exprs );
                expr.resize( expr.length() - len - 1 );
                
                expr += '-';
                expr += num.substr( start, len );
                add_operators_impl( num, target, start + len, prev_result + prev_op, -new_op, expr, all_exprs );
                expr.resize( expr.length() - len - 1 );
            }
            
            if ( new_op == 0 ) break;
        }
    }
    
    bool convert_to_int( const std::string & num,
                         const int           start,
                         const int           len,
                         int               & result ) {
        result = 0;
        if ( num[ start ] == '0' )
            return true;
        for ( int i = start; i < start + len; ++i ) {
            if ( result >
                 ( ( std::numeric_limits< int >::max() - ( num[ i ] - '0' ) ) / 10 ) )
                return false;
            result = result * 10 + ( num[ i ] - '0' );
        }
        return true;
    }
};
#endif

/**
 * A effective implementation
 */
#if 0
#include <vector>
#include <string>
#include <numeric_limits>

class Solution {
public:
    std::vector< std::string > addOperators( const std::string & num,
                                             const int           target ) {
        std::string expr;
        std::vector< std::string > all_exprs;
        add_operators_recursive( num, target, 0, 0, 0, '+', expr, all_exprs );
        return all_exprs;
    }
private:
    void add_operators_recursive( const std::string & num,
                                  const int           target,
                                  const int           start,
                                  const int           val,
                                  const int           prev_operand,
                                  const char          prev_operator,
                                  std::string       & expr,
                                  std::vector< std::string > & all_exprs ) {
        
        if ( start == num.length() ) {
            if ( target == val + prev_operand )
                all_exprs.push_back( expr );
            return;
        }
        
        //we parse out the new_operand from start index of num
        //and expr already has val + prev_operand prev_operator
        //so we need to merge prev_operand prev_operator new_operand
        //together and append *, +, -
        int old_len = expr.length();
        int new_operand = 0;
        int end = num[ start ] == '0' ? start + 1 : num.length();
        int new_prev_operand = 0;
        int new_val = 0;
        for ( int i = start; i < end; ++i ) {
            int digit = num[ i ] - '0';
            //check overflow for int
            if ( new_operand
               > ( ( std::numeric_limits< int >::max() - digit ) / 10 ) )
                break;
            new_operand = 10 * new_operand + digit;
            expr.push_back( num[ i ] );
            
            if ( prev_operator == '*' ) {
                new_prev_operand = prev_operand * new_operand;
                new_val = val;
            } else {
                new_prev_operand = prev_operator == '+'
                                 ? new_operand : -new_operand;
                new_val = val + prev_operand;
            }
            
            if ( i == num.length() - 1 ) {
                //it does not matter which operator we pass in
                add_operators_recursive( num, target, i + 1, new_val,
                                         new_prev_operand, '+', expr, all_exprs );
                break;
            }
            
            expr.push_back( '*' );
            add_operators_recursive( num, target, i + 1, new_val,
                                     new_prev_operand, '*', expr, all_exprs );
            
            expr.back() = '+';
            add_operators_recursive( num, target, i + 1, new_val,
                                     new_prev_operand, '+', expr, all_exprs );
            
            expr.back() = '-';
            add_operators_recursive( num, target, i + 1, new_val,
                                     new_prev_operand, '-', expr, all_exprs );
            
            expr.pop_back();
        }
        //restore expr
        while ( expr.length() > old_len )
            expr.pop_back();
    }
};
#endif

/**
 * Optimized and efficient implementation
 */
#include <vector>
#include <string>
#include <numeric_limits>

class Solution {
public:
    std::vector< std::string > addOperators( const std::string & num,
                                             const int           target ) {
        char * buf = new char[ num.length() * 2 + 1 ];
        std::vector< std::string > all_exprs;
        add_operators_recursive( num, target, 0, 0, 0, buf, 0, all_exprs );
        delete [] buf;
        return all_exprs;
    }
private:
    /**
     * O( 3^n ) runtime, O( n ) space
     */
    void add_operators_recursive( const std::string & num,
                                  const int           target,
                                  const int           start,
                                  const int           val,
                                  const int           prev_operand,
                                  char              * buf,
                                  const int           buf_index,
                                  std::vector< std::string > & all_exprs ) {
        if ( start == num.length() ) {
            if ( target == val + prev_operand )
                all_exprs.push_back( std::string( buf, buf + buf_index ) );
            return;
        }
        
        int new_operand = 0;
        int end = num[ start ] == '0' ? start + 1 : num.length();
        for ( int i = start; i < end; ++i ) {
            int digit = num[ i ] - '0';
            //check overflow for int
            if ( new_operand
               > ( ( std::numeric_limits< int >::max() - digit ) / 10 ) )
                break;
            new_operand = 10 * new_operand + digit;
            if ( buf_index == 0 ) {
                buf[ buf_index + i - start ] = num[ i ];
                add_operators_recursive( num, target, i + 1, val, new_operand,
                        buf, buf_index + i - start + 1, all_exprs );
            } else {
                buf[ buf_index + i - start + 1 ] = num[ i ];
                buf[ buf_index ] = '*';
                add_operators_recursive( num, target, i + 1, val,
                        prev_operand * new_operand, buf, buf_index + i - start + 2, all_exprs );
                
                buf[ buf_index ] = '+';
                add_operators_recursive( num, target, i + 1, val + prev_operand,
                        new_operand, buf, buf_index + i - start + 2, all_exprs );
                
                buf[ buf_index ] = '-';
                add_operators_recursive( num, target, i + 1, val + prev_operand,
                        -new_operand, buf, buf_index + i - start + 2, all_exprs );
            }
        }
    }
};
