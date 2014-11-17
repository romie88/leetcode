//Word Ladder 2013-02-10
//
//Given two words (start and end), and a dictionary, find the length of
//shortest transformation sequence from start to end, such that:
//
//1. Only one letter can be changed at a time
//2. Each intermediate word must exist in the dictionary
//
//For example,
//
//Given:
//start = "hit"
//end = "cog"
//dict = ["hot","dot","dog","lot","log"]
//As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
//return its length 5.
//
//Note:
//* Return 0 if there is no such transformation sequence.
//* All words have the same length.
//* All words contain only lowercase alphabetic characters.

//Tags: Breadth-first Search

#include <string>
#include <unordered_set>
#include <vector>
#include <queue>
#include <set>

class Solution {
public:
    int ladderLength( std::string start, std::string end,
                      std::unordered_set< std::string > & dict ) {
        
        if ( next_to_each_other( start, end ) )
            return 2;
        
        struct Node {
            std::string   w;
            int           level;
            Node( const std::string & s, int lev )
                : w( s ), level( lev ) {}
        };

        std::queue< Node > q;
        std::set< std::string > s;

        q.push( Node( start, 1 ) );
        s.insert( start );
        while ( ! q.empty() )
        {
            Node n = q.front();
            q.pop();
            std::vector< std::string > words;
            find_next_words_from_dict( n.w, dict, words );
            for ( const auto & w : words )
            {
                if ( w == end )
                    return n.level + 1;
                else if ( s.find( w ) == s.end() )
                {
                    s.insert( w );
                    q.push( Node( w, n.level + 1 ) );
                }
            }
        }

        return 0;
    }
private:
    void find_next_words_from_dict(
            const std::string & s,
            const std::unordered_set< std::string > & dict,
            std::vector< std::string > & words )
    {
        std::string w( s );
        for ( std::string::size_type i = 0;
              i < s.length(); ++i )
        {
            for ( char c = 'a'; c <= 'z'; ++c )
            {
                if ( c == s[ i ] )
                    continue;
                
                w[ i ] = c;
                if ( dict.find( w ) != dict.end() )
                    words.push_back( w );
            }
            w[ i ] = s[ i ];//restore w
        }
    }

    bool next_to_each_other( const std::string & w1,
                             const std::string & w2 )
    {
        bool result = false;
        for ( std::string::size_type i = 0;
              i < w1.length(); ++i )
        {
            if ( w1[ i ] != w2[ i ] )
            {
                if ( result == false )
                    result = true;
                else
                    return false;
            }
        }
        return result;
    }
};
