/**
 * Algorithms 36 Valid Sudoku                                              Easy
 * 
 * Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.
 * http://sudoku.com.au/TheRules.aspx
 * 
 * 5 3 . . 7 . . . . 
 * 6 . . 1 9 5 . . .
 * . 9 8 . . . . 6 .
 * 8 . . . 6 . . . 3
 * 4 . . 8 . 3 . . 1
 * 7 . . . 2 . . . 6
 * . 6 . . . . 2 8 .
 * . . . 4 1 9 . . 5
 * . . . . 8 . . 7 9
 * 
 * The Sudoku board could be partially filled, where empty cells are filled
 * with the character '.'.
 * 
 * 
 * A partially filled sudoku which is valid.
 * 
 * Note:
 * A valid Sudoku board (partially filled) is not necessarily solvable. Only
 * the filled cells need to be validated.
 * 
 * Tags: Hash Table
 * Similar Problems: (H) Sudoku Solver
 */

#include <vector>
#include <cctype>
#include <cstring>

class Solution {
public:
    bool isValidSudoku( const std::vector< std::vector< char > > & board ) {
        return are_rows_valid( board )
            && are_cols_valid( board )
            && are_subsquares_valid( board );
    }
private:
    bool are_rows_valid( const std::vector< std::vector< char > > & board ) {
        const int R = board.size();
        const int C = board[ 0 ].size();
        bool ht[ 9 ];
        for ( int i = 0; i < R; ++i ) {
            std::memset( ht, 0, sizeof( ht ) );
            for ( int j = 0; j < C; ++j ) {
                if ( std::isdigit( board[ i ][ j ] ) ) {
                    int x = board[ i ][ j ] - '1';
                    if ( ht[ x ] ) return false;
                    else ht[ x ] = true;
                }
            }
        }
        return true;
    }
    bool are_cols_valid( const std::vector< std::vector< char > > & board ) {
        const int R = board.size();
        const int C = board[ 0 ].size();
        bool ht[ 9 ];
        for ( int j = 0; j < C; ++j ) {
            std::memset( ht, 0, sizeof( ht ) );
            for ( int i = 0; i < R; ++i ) {
                if ( std::isdigit( board[ i ][ j ] ) ) {
                    int x = board[ i ][ j ] - '1';
                    if ( ht[ x ] ) return false;
                    else ht[ x ] = true;
                }
            }
        }
        return true;
    }
    bool are_subsquares_valid( const std::vector< std::vector< char > > & board ) {
        const int R = board.size();
        const int C = board[ 0 ].size();
        bool ht[ 9 ];
        for ( int i = 0; i < R; i += 3 ) {
            for ( int j = 0; j < C; j += 3 ) {
                std::memset( ht, 0, sizeof( ht ) );
                for ( int x = i; x < i + 3; ++x ) {
                    for ( int y = j; y < j + 3; ++y ) {
                        if ( std::isdigit( board[ x ][ y ] ) ) {
                            int z = board[ x ][ y ] - '1';
                            if ( ht[ z ] ) return false;
                            else ht[ z ] = true;
                        }
                    }
                }
            }
        }
        return true;
    }
};

