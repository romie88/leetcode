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
 * Similar Problems: (M) Letter Combinations of a Phone Number,
 *                   (E) Valid Parentheses
 */

#include <vector>
#include <string>

class Solution {
public:
    std::vector< std::string > generateParenthesis( int n ) {
        std::string one_result;
        std::vector< std::string > results;
        generate_parentheses_impl( n, n, one_result, results );
        return results;
    }
private:
    void generate_parentheses_impl( int ln, int rn, std::string & one_result,
                                    std::vector< std::string > & results ) {
        if ( ln == 0 ) {
            one_result.append( rn, ')');
            results.push_back( one_result );
            one_result.resize( one_result.length() - rn );
            return;
        }
        
        one_result += '(';
        generate_parentheses_impl( ln - 1, rn, one_result, results );
        one_result.pop_back();
        if ( ln < rn ) {
            one_result += ')';
            generate_parentheses_impl( ln, rn - 1, one_result, results );
            one_result.pop_back();
        }
    }
};
