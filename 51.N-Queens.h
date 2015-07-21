/**
 * Algorithms 51 N-Queens                                                  Hard
 * 
 * The n-queens puzzle is the problem of placing n queens on an n×n chessboard
 * such that no two queens attack each other.
 * 
 *   a b c d e f g h
 * 8       Q         8
 * 7             Q   7
 * 6     Q           6
 * 5               Q 5
 * 4   Q             4
 * 3         Q       3
 * 2 Q               2
 * 1           Q     1
 *   a b c d e f g h
 * One solution to the eight queens puzzle
 * 
 * Given an integer n, return all distinct solutions to the n-queens puzzle.
 *
 * Each solution contains a distinct board configuration of the n-queens'
 * placement, where 'Q' and '.' both indicate a queen and an empty space respectively.
 *
 * For example,
 * There exist two distinct solutions to the 4-queens puzzle:
 *
 * [
 *  [".Q..",  // Solution 1
 *   "...Q",
 *   "Q...",
 *   "..Q."],
 * 
 *  ["..Q.",  // Solution 2
 *   "Q...",
 *   "...Q",
 *   ".Q.."]
 * ]
 *
 * Tags: Backtracking
 */

#include <string>
#include <vector>

class Solution {
public:
    std::vector< std::vector< std::string > > solveNQueens( int n ) {
        std::vector< std::vector< std::string > > results;
        solve_n_queens( n, results );
        return results;
    }
private:
    void solve_n_queens(
            const int                                   n,
            std::vector< std::vector< std::string > > & results ) {
        std::vector< std::string > one_result( n, std::string( n, '.' ) );
        std::vector< bool > column_flag( n, false );
        solve_n_queens_impl( n, 0, column_flag, one_result, results );
    }
    /**
     * one_result[ i ] means one queen is placed at the i-th row
     * 
     * flag[ i ] means the i-th column has a queen already.
     */
    void solve_n_queens_impl(
            const int                                   n,
            const int                                   i,
            std::vector< bool >                       & column_flag,
            std::vector< std::string >                & one_result,
            std::vector< std::vector< std::string > > & results ) {
        
        if ( i == n ) {
            results.push_back( one_result );
            return;
        }
        
        //we are at the i-th row and we try columns one by one
        for ( int j = 0; j < n; ++j ) {
            if ( column_flag[ j ] == false
              && is_diagonal_ok( one_result, i, j ) ) {
                one_result[ i ][ j ] = 'Q';
                column_flag[ j ] = true;
                solve_n_queens_impl( n, i + 1, column_flag, one_result, results );
                one_result[ i ][ j ] = '.';
                column_flag[ j ] = false;
            }
        }
    }
    bool is_diagonal_ok( const std::vector< std::string > & one_result,
                         const int                          i,
                         const int                          j ) {
        const int n = one_result.size();
        //major diagonal check
        for ( int x = i - 1, y = j + 1; x >= 0 && y < n; --x, ++y )
            if ( one_result[ x ][ y ] == 'Q' )
                return false;
        for ( int x = i + 1, y = j - 1; x < n && y >= 0; ++x, --y )
            if ( one_result[ x ][ y ] == 'Q' )
                return false;
        //minor diagonal check
        for ( int x = i - 1, y = j - 1; x >= 0 && y >= 0; --x, --y )
            if ( one_result[ x ][ y ] == 'Q' )
                return false;
        for ( int x = i + 1, y = j + 1; x < n && y < n; ++x, ++y )
            if ( one_result[ x ][ y ] == 'Q' )
                return false;
        return true;
    }
};
