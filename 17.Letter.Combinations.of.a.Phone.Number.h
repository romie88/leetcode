/**
 * Algorithms 17 Letter Combinations of a Phone Number                   Medium
 * 
 * Given a digit string, return all possible letter combinations that the
 * number could represent.
 * 
 * A mapping of digit to letters (just like on the telephone buttons) is given
 * below.
 * 
 * 1      2 abc  3 def
 * 4 ghi  5 jkl  6 mno
 * 7 pqrs 8 tuv  9 wxyz
 * * +    0      # 
 * 
 * Input: Digit string "23"
 * Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 * 
 * Note:
 * Although the above answer is in lexicographical order, your answer could be
 * in any order you want.
 * 
 * Tags: Backtracking, String
 * Similar Problems: (M) Generate Parentheses, (M) Combination Sum
 */

#include <string>
#include <vector>

class Solution {
public:
    Solution() : letters_for_digit{ " ", "", "abc", "def", "ghi", "jkl", "mno",
        "pqrs", "tuv", "wxyz" } {}
    std::vector< std::string > letterCombinations( const std::string & digits ) {
        return letter_combinations_recursive( digits );
    }
private:
    //letters_for_digit[ d - '0' ] is the string contains the letters for
    //the digit d
    const std::vector< std::string > letters_for_digit;
    
    /**
     * O( m^n ) runtime where n is the number of digits and m is the
     * number of letters for a given digit.
     * 
     * This is a recursive implementation.
     */
    std::vector< std::string > letter_combinations_recursive(
            const std::string & digits ) {
        std::vector< std::string > results;
        if ( digits.empty() ) return results;
        
        std::string one_result;
        letter_combinations_recursive_impl( digits, 0, results, one_result );
        return results;
    }
    void letter_combinations_recursive_impl(
            const std::string          & digits,
            const int                    i,
            std::vector< std::string > & results,
            std::string                & one_result ) {
        if ( i == digits.length() ) {
            results.push_back( one_result );
            return;
        }
        
        const std::string & letters = letters_for_digit[ digits[ i ] - '0' ];
        //handle the case that letters are empty for a given digit
        if ( letters.empty() ) {
            letter_combinations_recursive_impl(
                digits, i + 1, results, one_result );
            return;
        }
        
        for ( int k = 0; k < letters.length(); ++k ) {
            one_result.push_back( letters[ k ] );
            letter_combinations_recursive_impl(
                digits, i + 1, results, one_result );
            one_result.pop_back();
        }
    }
    
    /**
     * O( m^n ) runtime - an iterative implementation
     * 
     * This implementation uses a very tricky loop to enumeration all the
     * combinations of the indices of the letters from all the digits.
     */
    std::vector< std::string > letter_combinations_iterative1(
            const std::string & digits ) {
        std::vector< std::string > results;
        if ( digits.empty() ) return results;
        
        std::string one_result( digits.length(), ' ' );
        //indices[ i ] is the index to the letter from the string
        //letters_for_digit[ digits[ i ] - '0' ]
        std::vector< int > indices( digits.length(), 0 );
        
        while ( true ) {
            for ( int i = 0; i < digits.size(); ++i )
                one_result[ i ]
                    = letters_for_digit[ digits[ i ] - '0' ][ indices[ i ] ];
            results.push_back( one_result );
            
            int k = digits.size() - 1;
            while ( k >= 0 ) {
                if ( indices[ k ] + 1
                   < letters_for_digit[ digits[ k ] - '0' ].size() ) {
                    ++indices[ k ];
                    break;
                } else {
                    indices[ k ] = 0;
                    --k;
                }
            }
            if ( k < 0 ) break;
        }
        
        return results;
    }
    
    /**
     * O( m^n ) runtime - another iterative implementation
     * 
     * The idea is to add more and more digits to the existing results.
     * However this implementation involves a lot of data copying.
     */
    std::vector< std::string > letter_combinations_iterative2(
            const std::string & digits ) {
        std::vector< std::string > results;
        if ( digits.empty() ) return results;
        
        results.push_back( "" );
        std::vector< std::string > tmp_results;
        for ( int i = 0; i < digits.length(); ++i ) {
            tmp_results.clear();
            for ( int j = 0; j < results.size(); ++j ) {
                const std::string & s = letters_for_digit[ digits[ i ] - '0' ];
                for ( int k = 0; k < s.length(); ++k ) {
                    tmp_results.push_back( results[ j ] + s[ k ] );
                }
            }
            tmp_results.swap( results );
        }
        return results;
    }
};
