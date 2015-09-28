/**
 * Algorithms 241 Different Ways to Add Parentheses                      Medium
 * 
 * Given a string of numbers and operators, return all possible results from
 * computing all the different possible ways to group numbers and operators.
 * The valid operators are +, - and *.
 * 
 * Example 1
 * 
 * Input: "2-1-1".
 * 
 * ((2-1)-1) = 0
 * (2-(1-1)) = 2
 * 
 * Output: [0, 2]
 * 
 * Example 2
 * 
 * Input: "2*3-4*5"
 * 
 * (2*(3-(4*5))) = -34
 * ((2*3)-(4*5)) = -14
 * ((2*(3-4))*5) = -10
 * (2*((3-4)*5)) = -10
 * (((2*3)-4)*5) = 10
 * 
 * Output: [-34, -14, -10, -10, 10]
 * 
 * Credits:
 * 
 * Special thanks to @mithmatt for adding this problem and creating all test
 * cases.
 * 
 * Tags: Divide and Conquer
 * Similar Problems: (M) Unique Binary Search Trees II
 *                   (M) Basic Calculator
 *                   (H) Expression Add Operators
 */

#include <vector>
#include <string>
#include <cctype>
#include <map>

class Solution {
public:
    std::vector< int > diffWaysToCompute( const std::string & input ) {
        return diff_ways_to_compute_bottom_up_DP( input );
    }
private:
    /**
     * Top down DP
     */
    std::vector< int > diff_ways_to_compute_top_down_DP(
            const std::string & input ) {
        std::map< int, std::vector< int > > cache;
        const std::vector< int > * p
            = diff_ways_to_compute_recursive( input, 0, input.length(), cache );
        return *p;
    }
    const std::vector< int > *
    diff_ways_to_compute_recursive(
            const std::string                & input,
            const int                          start,
            const int                          end,
            std::map< int, std::vector< int > > & cache ) {
        
        int key = start * input.length() + end;
        auto it = cache.find( key );
        if ( it != cache.end() ) {
            return &(it->second);
        }
        
        std::vector< int > results;
        for ( int i = start; i < end; ++i ) {
            if ( ! std::isdigit( input[ i ] ) ) {
                const std::vector< int > * p1
                    = diff_ways_to_compute_recursive( input, start, i, cache );
                const std::vector< int > * p2
                    = diff_ways_to_compute_recursive( input, i + 1, end, cache );
                for ( const auto op1 : *p1 ) {
                    for ( const auto op2 : *p2 ) {
                        int op = 0;
                        switch ( input[ i ] ) {
                            case '+': op = op1 + op2; break;
                            case '-': op = op1 - op2; break;
                            case '*': op = op1 * op2; break;
                        }
                        results.push_back( op );
                    }
                }
            }
        }
        if ( results.empty() ) {
            results.push_back( std::stoi( input.substr( start, end - start ) ) );
        }
        
        auto rp = cache.insert( std::make_pair( key, results ) );
        return &rp.first->second;
    }
    /**
     * Bottom up DP
     */
    void parse_expression( const std::string   & input,
                           std::vector< int >  & operands,
                           std::vector< char > & operators ) {
        int op = 0;
        for ( int i = 0; i < input.length(); ++i ) {
            if ( ! std::isdigit( input[ i ] ) ) {
                operators.push_back( input[ i ] );
                operands.push_back( op );
                op = 0;
            } else {
                op = op * 10 + input[ i ] - '0';
            }
        }
        operands.push_back( op );
    }
    /**
     * dp[ i ][ j ] is the vector of results starting from the i-th operands
     * to the j-th operands:
     * i is the index to the i-th operands
     * j is the index to the j-th operands
     * i <= j
     * i = 0, ..., j
     * j = i, ..., n - 1
     * 
     * dp[ i ][ i ] is the vector of one element which is exactly the i-th
     * operand by itself.
     * 
     * dp[ i ][ j ] = dp[ i ][ i ]     X dp[ i + 1 ][ j ]
     *              + dp[ i ][ i + 1 ] X dp[ i + 2 ][ j ]
     *              + dp[ i ][ i + 2 ] X dp[ i + 3 ][ j ]
     *              + ...
     *              + dp[ i ][ j - 1 ] X dp[ j ][ j ]
     * X is the Cartisian production
     * + is the vector appending
     */
    std::vector< int > diff_ways_to_compute_bottom_up_DP(
            const std::string & input ) {
        
        std::vector< int  > operands;
        std::vector< char > operators;
        parse_expression( input, operands, operators );
        const int n = operands.size();
        std::vector< std::vector< std::vector< int > > >
                dp( n,
                    std::vector< std::vector< int > >( n,
                                                       std::vector< int >() ) );
        for ( int i = n - 1; i >=0; --i ) {
            dp[ i ][ i ].push_back( operands[ i ] );
            for ( int j = i + 1; j < n; ++j ) {
                for( int k = i; k < j; ++k ) {
                    for ( const auto x : dp[ i ][ k ] )
                        for ( const auto y : dp[ k + 1 ][ j ] ) {
                            int result = 0;
                            switch ( operators[ k ] ) {
                                case '*': result = x * y; break;
                                case '+': result = x + y; break;
                                case '-': result = x - y; break;
                            }
                            dp[ i ][ j ].push_back( result );
                        }
                }
            }
        }
        return dp[ 0 ][ n - 1 ];
    }
};
