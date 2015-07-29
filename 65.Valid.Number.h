/**
 * Algorithms 65 Valid Number                                              Hard
 * 
 * Validate if a given string is numeric.
 * 
 * Some examples:
 * "0" => true
 * " 0.1 " => true
 * "abc" => false
 * "1 a" => false
 * "2e10" => true
 * 
 * Note: It is intended for the problem statement to be ambiguous. You should
 * gather all requirements up front before implementing one.
 * 
 * Update (2015-02-10):
 * The signature of the C++ function had been updated. If you still see your
 * function signature accepts a const char * argument, please click the reload
 * button  to reset your code definition.
 * 
 * Tags: Math, String
 * Similar Problems: (E) String to Integer (atoi)
 */

#include <string>
#include <cctype>

class Solution {
public:
    bool isNumber( const std::string & s ) {
        return is_number_by_automata( s );
    }
private:
    /**
     * O( n ) runtime, O( 1 ) space - automata
     */
    enum InputType {
        INVALID,    //0
        SPACE,      //1
        SIGN,       //2
        DIGIT,      //3
        DOT,        //4
        EXPONENT,   //5
        NUM_INPUTS  //6
    };
    bool is_number_by_automata( const std::string & s ) {
        
        //transition table: state by input
        int transition_table[][ NUM_INPUTS ] = {
            { -1,  0,  3,  1,  2, -1 },//0
            { -1,  8, -1,  1,  4,  5 },//1
            { -1, -1, -1,  4, -1, -1 },//2
            { -1, -1, -1,  1,  2, -1 },//3
            { -1,  8, -1,  4, -1,  5 },//4
            { -1, -1,  6,  7, -1, -1 },//5
            { -1, -1, -1,  7, -1, -1 },//6
            { -1,  8, -1,  7, -1, -1 },//7
            { -1,  8, -1, -1, -1, -1 } //8
        };
        
        int state = 0;//start state
        for ( int i = 0; i < s.length(); ++i ) {
            InputType it = get_input_type( s[ i ] );
            state = transition_table[ state ][ it ];
            if ( state == -1 ) return false;
        }
        return state == 1 || state == 4 || state == 7 || state == 8;
    }
    InputType get_input_type( const char c ) {
        InputType it = INVALID;
        if ( std::isspace( c ) )
            it = SPACE;
        else if ( c == '+' || c == '-' )
            it = SIGN;
        else if ( std::isdigit( c ) )
            it = DIGIT;
        else if ( c == '.' )
            it = DOT;
        else if ( c == 'e' || c == 'E' )
            it = EXPONENT;
        else
            it = INVALID;
        
        return it;
    }
    
    /**
     * O( n ) runtime, O( 1 ) space - directly check
     */
    bool is_number_directly( const std::string & s ) {
        const int n = s.length();
        int i = 0;
        
        //skip all leading the white spaces
        while ( i < n && std::isspace( s[ i ] ) ) ++i;
        if ( i == n ) return false;
        
        //check sign
        if ( s[ i ] == '+' || s[ i ] == '-' ) {
            ++i;
            if ( i == n ) return false;
        }
        
        //integer part
        int i_copy = i;
        while ( i < n && std::isdigit( s[ i ] ) ) ++i;
        if ( i == n ) return i_copy != i;
        bool has_integer_part = i_copy != i;
        
        //decimal point
        bool has_fraction_part = false;
        if ( s[ i ] == '.' ) {
            ++i;
            i_copy = i;
            while ( i < n && std::isdigit( s[ i ] ) ) ++i;
            if ( ! has_integer_part && i_copy == i ) return false;
            if ( i == n ) return true;
            has_fraction_part = true;
        }
        
        //exponent
        if ( s[ i ] == 'e' || s[ i ] == 'E' ) {
            ++i;
            if ( i == n ) return false;
        
            //exponent sign
            if ( s[ i ] == '+' || s[ i ] == '-' ) {
                ++i;
                if ( i == n ) return false;
            }
            
            //exponent integer
            i_copy = i;
            while ( i < n && std::isdigit( s[ i ] ) ) ++i;
            if ( i_copy == i ) return false;
        }
        
        //skip all the trailing spaces
        while ( i < n && std::isspace( s[ i ] ) ) ++i;
        return i == n && ( has_integer_part || has_fraction_part );
    }
    
    /**
     * O( n ) runtime, O( 1 ) space - solution from CleanCodeHandbook
     */
    bool is_number_solution( const std::string & s ) {
        const int n = s.length();
        int i = 0;
        //skip all the leading spaces
        while ( i < n && std::isspace( s[ i ] ) ) ++i;
        //check sign
        if ( i < n && ( s[ i ] == '+' || s[ i ] == '-' ) ) ++i;
        //integer part
        bool is_valid = false;
        while ( i < n && std::isdigit( s[ i ] ) ) {
            ++i;
            is_valid = true;
        }
        //fraction part
        if ( i < n && s[ i ] == '.' ) {
            ++i;
            while ( i < n && std::isdigit( s[ i ] ) ) {
                ++i;
                is_valid = true;
            }
        }
        //exponent
        if ( is_valid && i < n && ( s[ i ] == 'e' || s[ i ] == 'E' ) ) {
            ++i;
            is_valid = false;
            if ( i < n && ( s[ i ] == '+' || s[ i ] == '-' ) ) ++i;
            while ( i < n && std::isdigit( s[ i ] ) ) {
                ++i;
                is_valid = true;
            }
        }
        //skip all the trailing spaces
        while ( i < n && std::isspace( s[ i ] ) ) ++i;
        return is_valid && i == n;
    }
};
