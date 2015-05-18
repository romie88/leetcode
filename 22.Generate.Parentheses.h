/**
 * Algorithms 22 Generate Parentheses                                   Medium
 *
 * Given n pairs of parentheses, write a function to generate all combinations
 * of well-formed parentheses.
 * 
 * For example, given n = 3, a solution set is:
 * 
 * "((()))", "(()())", "(())()", "()(())", "()()()"
 *
 * Tags: Backtracking, String
 */

#include <vector>
#include <string>

class Solution {
public:
    std::vector< std::string > generateParenthesis( int n ) {
        std::string s;
        std::vector< std::string > results;
        generate_parentheses_impl( n, n, s, results );
        return results;
    }
private:
    void generate_parentheses_impl( int ln, int rn, std::string & s,
                                    std::vector< std::string > & results ) {
        if ( ln == 0 ) {
            s.append( rn, ')');
            results.push_back( s );
            s.resize( s.length() - rn );
            return;
        }
        if ( ln == rn ) {
            s += '(';
            generate_parentheses_impl( ln - 1, rn, s, results );
            s.pop_back();
        } else if ( ln < rn ) {
            s += '(';
            generate_parentheses_impl( ln - 1, rn, s, results );
            s.pop_back();
            
            s += ')';
            generate_parentheses_impl( ln, rn - 1, s, results );
            s.pop_back();
        }
    }
};
