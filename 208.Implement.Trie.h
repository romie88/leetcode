/**
 * Algorithms 208 Implement Trie (Prefix Tree)                           Medium
 *
 * Implement a trie with insert, search, and startsWith methods.
 *
 * Note:
 * You may assume that all inputs are consist of lowercase letters a-z.
 *
 * Tags: Data Structure, Trie
 * Similar Problems: (M) Add and Search Word - Data structure design
 */

#include <string>
#include <stack>

class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() : is_word( false ) {
        for ( int i = 0; i < sizeof ( children ) / sizeof ( children[ 0 ] );
              ++i ) {
            children[ i ] = nullptr;
        }
    }
    TrieNode * children[ 26 ];
    bool       is_word;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        dtor_helper( root );
    }

    void dtor_helper( TrieNode * p ) {
        if ( p == nullptr ) return;

        for ( int i = 0;
              i < sizeof( p->children ) / sizeof( p->children[ 0 ] );
              ++i ) {
            if ( p->children[ i ] != nullptr )
                dtor_helper( p->children[ i ] );
        }

        delete p;
    }

    // Inserts a word into the trie.
    void insert( const std::string & word ) {
        TrieNode * p = root;
        for ( int i = 0; i < word.length(); ++i ) {
            if ( p->children[ word[ i ] - 'a' ] == nullptr )
                p->children[ word[ i ] - 'a' ] = new TrieNode();
            p = p->children[ word[ i ] - 'a' ];
        }
        p->is_word = true;
    }

    // Returns if the word is in the trie.
    bool search( const std::string & word ) {
        TrieNode * p = root;
        for ( int i = 0; i < word.length(); ++i ) {
            if ( p->children[ word[ i ] - 'a' ] == nullptr )
                return false;
            p = p->children[ word[ i ] - 'a' ];
        }
        return p->is_word;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith( const std::string & prefix ) {
        TrieNode * p = root;
        for ( int i = 0; i < prefix.length(); ++i ) {
            if ( p->children[ prefix[ i ] - 'a' ] == nullptr )
                return false;
            p = p->children[ prefix[ i ] - 'a' ];
        }
        return true;
    }

    void delete_recursive( const std::string & word ) {
        delete_helper( word, 0, root );
    }

    bool has_any_child( TrieNode * p ) {
        for ( int i = 0;
              i < sizeof( p->children ) / sizeof ( p->children[ 0 ] );
              ++i )
            if ( p->children[ i ] != nullptr ) return true;
        return false;
    }

    bool delete_helper( const std::string & word, int i, TrieNode * p ) {
        if ( p == nullptr ) return false;

        if ( i == word.length() ) {
            if ( p->is_word ) p->is_word = false;
            return ! has_any_child( p );
#if 0
            //equivalently
            if ( p->is_word ) {
                p->is_word = false;
                return ! has_any_child( p );
            } else
                //if current node is not a word node
                //it must have children
                return false;
#endif
        } else {
            //the following check can be removed since we can recurse
            //to check if p->children[ word[ i ] ] == nullptr
            //if ( p->children[ word[ i ] ] == nullptr ) return false;
            if ( delete_helper( word, i + 1, p->children[ word[ i ] ] ) ) {
                delete p->children[ word[ i ] - 'a' ];
                p->children[ word[ i ] - 'a' ] = nullptr;
                return ! p->is_word && ! has_any_child( p );
            } else {
                return false;
            }
        }
    }

    void delete_iterative( const std::string & word ) {
        std::stack< TrieNode * > s;
        TrieNode * p = root;
        s.push( p );
        for ( int i = 0; i < word.length(); ++i ) {
            if ( p->children[ word[ i ] - 'a' ] == nullptr )
                return;
            p = p->children[ word[ i ] - 'a' ];
            s.push( p );
        }

        p = s.top();
        s.pop();
        if ( p->is_word == false ) return;
        p->is_word = false;
        while ( p != root && ! p->is_word && has_any_child( p ) ) {
            delete p;
            p = s.top();
            s.pop();
        }
    }

private:
    TrieNode * root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");