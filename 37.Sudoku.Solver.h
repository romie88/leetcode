/**
 * Algorithms 37 Sudoku Solver                                             Hard
 * 
 * Write a program to solve a Sudoku puzzle by filling the empty cells.
 * 
 * Empty cells are indicated by the character '.'.
 * 
 * You may assume that there will be only one unique solution.
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
 * A sudoku puzzle...
 * 
 * 5 3 4 6 7 8 9 1 2
 * 6 7 2 1 9 5 3 4 8
 * 1 9 8 3 4 2 5 6 7
 * 8 5 9 7 6 1 4 2 3
 * 4 2 6 8 5 3 7 9 1
 * 7 1 3 9 2 4 8 5 6
 * 9 6 1 5 3 7 2 8 4
 * 2 8 7 4 1 9 6 3 5
 * 3 4 5 2 8 6 1 7 9
 * 
 * ...and its solution numbers marked in red.
 * 
 * Tags: Backtracking, Hash Table
 * Similar Problems: (E) Valid Sudoku
 */

#include <vector>
#include <stdexcept>
#include <cstring>

class Solution {
public:
    void solveSudoku( std::vector< std::vector< char > > & board ) {
        solve_sudoku_impl_2( board );
    }
private:
    /**
     * My initial implementation - instead of trying all the numbers from
     * 1 to 9 on an empty cell, we first scan the row, the column and the
     * subsquare to get the feasible numbers in the hash_table vector and
     * only try these numbers.
     */
    void solve_sudoku_impl_1( std::vector< std::vector< char > > & board ) {
        if ( solve_sudoku_impl_1_helper( board, 0, 0 ) )
            return;
        else
            throw std::invalid_argument( "Sudoku board not solvable" );
    }
    bool solve_sudoku_impl_1_helper(
            std::vector< std::vector< char > > & board,
            int i, int j ) {
        
        //start from position ( i, j ) and search row by row
        //skip all the '.' on the way
        while ( i != 9 && board[ i ][ j ] != '.' ) {
            if ( j == 8 ) {
                ++i;
                j = 0;
            } else {
                ++j;
            }
        }
        
        if ( i == 9 ) return true;
        
        bool hash_table[ 9 ];
        for ( int k = 0; k < 9; ++k ) hash_table[ k ] = false;
        scan_for_feasible_numbers( board, hash_table, i, j );
        //hash_table[ i ] == true means number i + '1' is already filled
        for ( int k = 0; k < 9; ++k ) {
            if ( ! hash_table[ k ] ) {
                board[ i ][ j ] = k + '1';
                int next_i = i;
                int next_j = j + 1;
                if ( next_j == 9 ) {
                    ++next_i;
                    next_j = 0;
                }
                if ( solve_sudoku_impl_1_helper( board, next_i, next_j ) )
                    return true;
            }
        }
        board[ i ][ j ] = '.';
        return false;
    }
    void scan_for_feasible_numbers(
            const std::vector< std::vector< char > > & board,
            bool * hash_table, int i, int j ) {
        //row
        for ( int y = 0; y < 9; ++y )
            if ( board[ i ][ y ] != '.' )
                hash_table[ board[ i ][ y ] - '1' ] = true;
        //col
        for ( int x = 0; x < 9; ++x )
            if ( board[ x ][ j ] != '.' )
                hash_table[ board[ x ][ j ] - '1' ] = true;
        //subsquare
        const int I = i / 3 * 3;
        const int J = j / 3 * 3;
        for ( int x = I; x < I + 3; ++x )
            for ( int y = J; y < J + 3; ++y )
                if ( board[ x ][ y ] != '.' )
                    hash_table[ board[ x ][ y ] - '1' ] = true;
    }
    /**
     * My second implementation - directly try all the numbers from 1 to 9
     * on an empty cell.
     */
    void solve_sudoku_impl_2( std::vector< std::vector< char > > & board ) {
        if ( solve_sudoku_impl_2_helper( board, 0, 0 ) )
            return;
        else
            throw std::invalid_argument( "Sudoku board not solvable" );
    }
    bool solve_sudoku_impl_2_helper(
            std::vector< std::vector< char > > & board,
            int i, int j ) {
        int i2, j2;
        if ( ! next_available_position( board, i, j, i2, j2 ) ) return true;
        
        for ( int n = 0; n < 9; ++n ) {
            board[ i2 ][ j2 ] = n + '1';
            if ( is_valid_board( board, i2, j2 )
              && solve_sudoku_impl_2_helper( board, i2, j2 + 1 ) ) return true;
        }
        board[ i2 ][ j2 ] = '.';
        return false;
    }
    bool next_available_position(
            const std::vector< std::vector< char > > & board,
            int i, int j, int & i2, int & j2 ) {
        if ( j == 9 ) {
            j = 0;
            ++i;
        }
        
        while ( i < 9 && j < 9 ) {
            if ( board[ i ][ j ] == '.' ) {
                i2 = i;
                j2 = j;
                return true;
            }
            ++j;
            if ( j == 9 ) {
                j = 0;
                ++i;
            }
        }
        return false;
    }
    bool is_valid_board( const std::vector< std::vector< char > > & board,
                         int i, int j ) {
        ;
        //actually there is no need to use a hash_table here
        for ( int r = 0; r < 9; ++r )
            if ( r != i && board[ r ][ j ] == board[ i ][ j ] )
                return false;
        
        for ( int c = 0; c < 9; ++c )
            if ( c != j && board[ i ][ c ] == board[ i ][ j ] )
                return false;
        
        const int I = i / 3 * 3;
        const int J = j / 3 * 3;
        for ( int x = I; x < I + 3; ++x )
            for ( int y = J; y < J + 3; ++y )
                if ( ( x != i || y != j ) && board[ x ][ y ] == board[ i ][ j ] )
                    return false;
        
        return true;
    }
#if 0
    bool is_valid_board( const std::vector< std::vector< char > > & board,
                         int i, int j ) {
        bool ht[ 9 ];
        std::memset( ht, 0, sizeof( ht  ) );
        for ( int r = 0; r < 9; ++r ) {
            if ( board[ r ][ j ] == '.' ) continue;
            if ( ht[ board[ r ][ j ] - '1' ] ) return false;
            else ht[ board[ r ][ j ] - '1' ] = true;
        }
        
        std::memset( ht, 0, sizeof( ht  ) );
        for ( int c = 0; c < 9; ++c ) {
            if ( board[ i ][ c ] == '.' ) continue;
            if ( ht[ board[ i ][ c ] - '1' ] ) return false;
            else ht[ board[ i ][ c ] - '1' ] = true;
        }
        
        int x = i / 3 * 3;
        int y = j / 3 * 3;
        std::memset( ht, 0, sizeof( ht  ) );
        for ( int xx = x; xx < x + 3; ++xx ) {
            for ( int yy = y; yy < y + 3; ++yy ) {
                if ( board[ xx ][ yy ] == '.' ) continue;
                if ( ht[ board[ xx ][ yy ] - '1' ] ) return false;
                else ht[ board[ xx ][ yy ] - '1' ] = true;
            }
        }
        
        return true;
    }
#endif
    /**
     * The fastest implementation
     * - using a single index k to derive i and j;
     * - using extra memory to ensure O(1) check for validness
     * - handle '.' and other characters in the same way
     */
    void fill( int r, int c, int n ) {
        rowValid[ r ][ n ] = true;
        colValid[ c ][ n ] = true;
        subValid[ r / 3 * 3 + c / 3 ][ n ] = true;
    }
    void clear( int r, int c, int n ) {
        rowValid[ r ][ n ] = false;
        colValid[ c ][ n ] = false;
        subValid[ r / 3 * 3 + c / 3 ][ n ] = false;
    }
    bool is_valid( int r, int c, int n ) {
        return ! rowValid[ r ][ n ]
            && ! colValid[ c ][ n ]
            && ! subValid[ r / 3 * 3 + c / 3 ][ n ];
    }
    void solve_sudoku_impl_3( std::vector< std::vector< char > > & board ) {
        for ( int i = 0; i < 9; ++i )
            for ( int j = 0; j < 9; ++j )
                if ( board[ i ][ j ] != '.' )
                    fill( i, j, board[ i ][ j ] - '1' );
        
        if ( solve_sudoku_impl_3_helper( board, 0 ) )
            return;
        else
            throw std::invalid_argument( "Sudoku board not solvable" );
    }
    bool solve_sudoku_impl_3_helper(
            std::vector< std::vector< char > > & board,
            int k ) {
        if ( k > 80 ) return true;
        
        int r = k / 9;
        int c = k % 9;
        if ( board[ r ][ c ] != '.' )
            return solve_sudoku_impl_3_helper( board, k + 1 );
        
        for ( int n = 0; n < 9; ++n ) {
            if ( is_valid( r, c, n ) ) {
                board[ r ][ c ] = n + '1';
                fill( r, c, n );
                if ( solve_sudoku_impl_3_helper( board, k + 1 ) ) return true;
                clear( r, c, n );
            }
        }
        board[ r ][ c ] = '.';
        return false;
    }
    /**
     * Every row, column, subsquare has its own hash table
     */
    bool rowValid[ 9 ][ 9 ];
    bool colValid[ 9 ][ 9 ];
    bool subValid[ 9 ][ 9 ];
};

