//Word Ladder 2013-02-10
//
//Given two words (start and end), and a dictionary, find all shortest
//transformation sequence(s) from start to end, such that:
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
//Return
//  [
//    ["hit","hot","dot","dog","cog"],
//    ["hit","hot","lot","log","cog"]
//  ]
//
//Note:
//* All words have the same length.
//* All words contain only lowercase alphabetic characters.

//Tags: Breadth-first Search

#include <string>
#include <unordered_set>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <iostream>

using namespace std;

class Solution {
public:
    std::vector< std::vector< std::string > >
    findLadders( std::string start, std::string end,
                 std::unordered_set< std::string > & dict ) {
        
        std::vector< std::vector< std::string > > all_ladders;
        if ( next_to_each_other( start, end ) )
        {
            std::vector< std::string > one_ladder;
            one_ladder.push_back( start );
            one_ladder.push_back( end );
            all_ladders.push_back( one_ladder );
            return all_ladders;
        }

        std::queue< std::string > q;
        std::set< std::string > current_level_s;//contains all the words from the current level
        std::unordered_map< std::string, std::vector< std::string > > word_to_previous_map;
        
        bool hasFound = false;
        q.push( start );
        q.push( std::string() );
        while ( ! q.empty() )
        {
            std::string w = q.front();
            q.pop();
            
            if ( w.empty()
              && ! q.empty() )
            {
                //This is to prevent infinite loop
                //otherwise q is always has empty string
                if ( hasFound )
                    break;

                for ( const auto & n : current_level_s )
                    dict.erase( n );

                current_level_s.clear();
                q.push( std::string() );
            }
            else
            {
                std::vector< std::string > words;
                find_next_words_from_dict( w, dict, words );
                for ( const auto & n : words )
                {
                    if ( n == end )
                    {
                        hasFound = true;
                        word_to_previous_map[ n ].push_back( w );
                        break;
                    }
                    
                    if ( dict.find( n ) != dict.end() )
                    {
                        word_to_previous_map[ n ].push_back( w );
                        
                        if ( current_level_s.find( n ) == current_level_s.end() )
                        {
                            q.push( n );
                            current_level_s.insert( n );
                        }
                    }
                }
            }
        }
        
        if ( hasFound )
        {
            std::vector< std::string > one_ladder;
            back_track_ladders( start, end, word_to_previous_map, one_ladder, all_ladders );
        }

        return all_ladders;
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

    void back_track_ladders(
            const std::string & start,
            const std::string & end,
            const std::unordered_map< std::string, std::vector< std::string > > & word_to_previous_map,
            std::vector< std::string > & one_ladder,
            std::vector< std::vector< std::string > > & ladders )
    {
        one_ladder.push_back( end );
        
        if ( start == end )
        {
            std::reverse( one_ladder.begin(), one_ladder.end() );
            ladders.push_back( one_ladder );
            std::reverse( one_ladder.begin(), one_ladder.end() );
            return;
        }
        
        auto it = word_to_previous_map.find( end );
        for ( const auto & w : it->second )
        {
            back_track_ladders( start, w, word_to_previous_map, one_ladder, ladders );
            one_ladder.pop_back();
        }
    }
};

