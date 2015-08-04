/**
 * Algorithms 79 Word Search                                             Medium
 *
 * Given a 2D board and a word, find if the word exists in the grid.
 * The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.
 *
 * For example,
 *
 * Given board =
 *
 * [
 *   ["ABCE"],
 *   ["SFCS"],
 *   ["ADEE"]
 * ]
 *
 * word = "ABCCED", -> returns true,
 * word = "SEE", -> returns true,
 * word = "ABCB", -> returns false.
 *
 * Tags: Array, Backtracking
 * Similar Problems: (H) Word Search II
 */

#include <vector>
#include <string>

class Solution {
public:
    bool exist( const std::vector< std::vector< char > > & board,
                const std::string                        & word ) {
        return exist_impl( board, word );
    }
private:
    /**
     * O( m^2 * n^2 ) runtime, O( m * n ) space - DFS
     *
     * For each cell we do a DFS which has complexity O( E + V ) where
     * E is the number of edges and V is the number of vertices. In this
     * problem E and V are both m * n. Thus the runtime O( m * n * m * n )
     * and the space is O( m * n ) a two-dimension array to log the visit
     * status.
     */
    bool search( const std::vector< std::vector< char > > & board,
                 const int                                  i,
                 const int                                  j,
                 const std::string                        & word,
                 const int                                  s,
                 std::vector< std::vector< bool > >       & visited ) {
        if ( s == word.length() ) return true;

        if ( i < 0 || j < 0 || i >= board.size() || j >= board[ 0 ].size()
          || visited[ i ][ j ] || board[ i ][ j ] != word[ s ] )
            return false;

        visited[ i ][ j ] = true;
        if ( search( board, i + 1, j, word, s + 1, visited ) )
            return true;
        if ( search( board, i - 1, j, word, s + 1, visited ) )
            return true;
        if ( search( board, i, j + 1, word, s + 1, visited ) )
            return true;
        if ( search( board, i, j - 1, word, s + 1, visited ) )
            return true;

        visited[ i ][ j ] = false;
        return false;
    }
    bool exist_impl( const std::vector< std::vector< char > > & board,
                     const std::string & word ) {
        std::vector< std::vector< bool > >
            visited( board.size(),
                     std::vector< bool >( board[ 0 ].size(), false ) );
        for ( int i = 0; i < board.size(); ++i ) {
            for ( int j = 0; j < board[ 0 ].size(); ++j ) {
                if ( search( board, i, j, word, 0, visited ) )
                    return true;
            }
        }
        return false;
    }
};