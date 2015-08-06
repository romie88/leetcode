/**
 * Algorithms 212 Word Search II                                           Hard
 *
 * Given a 2D board and a list of words from the dictionary, find all words in
 * the board.
 *
 * Each word must be constructed from letters of sequentially adjacent cell,
 * where "adjacent" cells are those horizontally or vertically neighboring.
 * The same letter cell may not be used more than once in a word.
 *
 * For example,
 *
 * Given words = ["oath","pea","eat","rain"] and board =
 *
 * [
 *   ['o','a','a','n'],
 *   ['e','t','a','e'],
 *   ['i','h','k','r'],
 *   ['i','f','l','v']
 * ]
 *
 * Return ["eat","oath"].
 *
 * Note:
 *
 * You may assume that all inputs are consist of lowercase letters a-z.
 *
 * click to show hint.
 *
 * You would need to optimize your backtracking to pass the larger test. Could
 * you stop backtracking earlier?
 *
 * If the current candidate does not exist in all words' prefix, you could stop
 * backtracking immediately. What kind of data structure could answer such
 * query efficiently? Does a hash table work? Why or why not? How about a Trie?
 * If you would like to learn how to implement a basic trie, please work on
 * this problem: Implement Trie (Prefix Tree) first.
 *
 * Tags: Backtracking, Trie
 * Similar Problems: (M) Word Search
 */

#include <vector>
#include <string>
#include <unordered_set>

class TrieNode {
public:
    TrieNode() : is_word( false ) {
        for ( int i = 0; i < sizeof( children ) / sizeof ( children[ 0 ] );
              ++i )
            children[ i ] = nullptr;
    }
    TrieNode * children[ 26 ];
    bool       is_word;
};

/**
 * This Trie implementation is a little different from the Trie class
 * from Problem 208 Implement Trie.
 *
 * I change the return value of startsWith() from bool to TrieNode *.
 * Later we use the returned point to check is_word directly and flip
 * is_word to make sure the uniqueness of the found words.
 *
 * A further optimization is to expose the root and allow DFS to traverse
 * down the Trie.
 */
class Trie {
public:
    Trie() : root( new TrieNode() ) {}
    ~Trie() { dtor_helper( root ); }
    void dtor_helper( TrieNode * p ) {
        if ( p == nullptr ) return;
        for ( int i = 0;
              i < sizeof( p->children ) / sizeof ( p->children[ 0 ] );
              ++i )
            if ( p->children[ i ] != nullptr )
                dtor_helper( p->children[ i ] );
        delete p;
    }
    void insert( const std::string & word ) {
        TrieNode * p = root;
        for ( int i = 0; i < word.length(); ++i ) {
            if ( p->children[ word[ i ] - 'a' ] == nullptr )
                p->children[ word[ i ] - 'a' ] = new TrieNode();
            p = p->children[ word[ i ] - 'a' ];
        }
        p->is_word = true;
    }
    bool contains( const std::string & word ) {
        TrieNode * p = root;
        for ( int i = 0; i < word.length(); ++i ) {
            if ( p->children[ word[ i ] - 'a' ] == nullptr ) return false;
            p = p->children[ word[ i ] - 'a' ];
        }
        return p->is_word;
    }
    TrieNode * startsWith( const std::string & prefix ) {
        TrieNode * p = root;
        for ( int i = 0; i < prefix.length(); ++i ) {
            if ( p->children[ prefix[ i ] - 'a' ] == nullptr ) return nullptr;
            p = p->children[ prefix[ i ] - 'a' ];
        }
        return p;
    }
    TrieNode * root;
};

class Solution {
public:
    std::vector< std::string >
    findWords( const std::vector< std::vector< char > > & board,
               const std::vector< std::string >         & words ) {
        return find_words_impl_2( board, words );
    }
private:
    /**
     * DFS with Trie for pruning
     */
    std::vector< std::string >
    find_words_impl_1( const std::vector< std::vector< char > > & board,
                       const std::vector< std::string >         & words ) {
        std::vector< std::string > results;
        if ( board.empty() || words.empty() ) return results;

        int max_len = 0;
        Trie t;
        for ( int i = 0; i < words.size(); ++i ) {
            t.insert( words[ i ] );
            if ( max_len < words[ i ].length() )
                max_len = words[ i ].length();
        }

        std::string w;
        std::unordered_set< std::string > results_set;
        std::vector< std::vector< bool > >
            visited( board.size(),
                     std::vector< bool >( board[ 0 ].size(), false ) );
        for ( int i = 0; i < board.size(); ++i )
            for ( int j = 0; j < board[ 0 ].size(); ++j )
                dfs_search_1( board, i, j, visited, t, w, max_len, results_set );

        results.insert( results.begin(),
                        results_set.begin(),
                        results_set.end() );
        return results;
    }
    void dfs_search_1( const std::vector< std::vector< char > > & board,
                       const int                                  i,
                       const int                                  j,
                       std::vector< std::vector< bool > >       & visited,
                       Trie                                     & t,
                       std::string                              & w,
                       const int                                  max_len,
                       std::unordered_set< std::string >        & s ) {

        if ( i < 0 || j < 0 || i >= board.size() || j >= board[ 0 ].size()
          || visited[ i ][ j ] || w.length() > max_len ) return;

        w += board[ i ][ j ];
        if ( t.startsWith( w ) ) {
            if ( t.contains( w ) ) s.insert( w );
            visited[ i ][ j ] = true;
            dfs_search_1( board, i + 1, j, visited, t, w, max_len, s );
            dfs_search_1( board, i - 1, j, visited, t, w, max_len, s );
            dfs_search_1( board, i, j + 1, visited, t, w, max_len, s );
            dfs_search_1( board, i, j - 1, visited, t, w, max_len, s );
            visited[ i ][ j ] = false;
        }
        w.pop_back();
    }
    /**
     * A further optimized implementation
     */
    std::vector< std::string >
    find_words_impl_2( const std::vector< std::vector< char > > & board,
                       const std::vector< std::string >         & words ) {
        std::vector< std::string > results;
        if ( board.empty() || words.empty() ) return results;

        int max_len = 0;
        Trie t;
        for ( int i = 0; i < words.size(); ++i ) {
            t.insert( words[ i ] );
            if ( max_len < words[ i ].length() )
                max_len = words[ i ].length();
        }

        std::string w;
        std::vector< std::vector< bool > >
            visited( board.size(),
                     std::vector< bool >( board[ 0 ].size(), false ) );
        for ( int i = 0; i < board.size(); ++i )
            for ( int j = 0; j < board[ 0 ].size(); ++j )
                dfs_search_2( board, i, j, visited, t.root, w, max_len, results );

        return results;
    }
    void dfs_search_2( const std::vector< std::vector< char > > & board,
                       const int                                  i,
                       const int                                  j,
                       std::vector< std::vector< bool > >       & visited,
                       TrieNode                                 * t,
                       std::string                              & w,
                       const int                                  max_len,
                       std::vector< std::string >               & results ) {

        if ( i < 0 || j < 0 || i >= board.size() || j >= board[ 0 ].size()
          || visited[ i ][ j ] || w.length() > max_len ) return;

        w += board[ i ][ j ];
        TrieNode * p = t[ board[ i ][ j ] - 'a' ];
        if ( p ) {
            if ( p->is_word ) {
                results.push_back( w );
                p->is_word = false;
            }
            visited[ i ][ j ] = true;
            dfs_search_2( board, i + 1, j, visited, p, w, max_len, results );
            dfs_search_2( board, i - 1, j, visited, p, w, max_len, results );
            dfs_search_2( board, i, j + 1, visited, p, w, max_len, results );
            dfs_search_2( board, i, j - 1, visited, p, w, max_len, results );
            visited[ i ][ j ] = false;
        }
        w.pop_back();
    }
};