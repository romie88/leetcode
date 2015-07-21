/**
 * Algorithms 49 Anagrams                                                Medium
 * 
 * Given an array of strings, return all groups of strings that are anagrams.
 * 
 * Note: All inputs will be in lower-case.
 * 
 * Tags: Hash Table, String
 */

#include <vector>
#include <string>
#include <unordered_map>

class Solution {
public:
    std::vector< std::string > anagrams(
            const std::vector< std::string > & strs ) {
        return anagrams_impl_3( strs );
    }
private:
    /**
     * O( n k log k ) runtime, O( nk ) space - sort string and put in hash table
     * k is the length of the longest string
     * n is the total number of strings
     */
    std::vector< std::string > anagrams_impl_1(
            const std::vector< std::string > & strs ) {
        
        std::unordered_map< std::string, std::vector< int > > m;
        //iterate through all the strings and sort each string
        //insert the sorted string as key and the index as the value
        //to the hash table
        for ( int i = 0; i < strs.size(); ++i ) {
            std::string s( strs[ i ] );
            std::sort( s.begin(), s.end() );
            m[ s ].push_back( i );
        }
        //iterate through the hash table
        std::vector< std::string > results;
        for ( std::unordered_map< std::string, std::vector< int > >::const_iterator
              cit = m.begin(); cit != m.end(); ++cit ) {
            if ( cit->second.size() > 1 ) {
                for ( int i = 0; i < cit->second.size(); ++i )
                    results.push_back( strs[ cit->second[ i ] ] );
            }
        }
        
        return results;
    }
    /**
     * O( n k log k ) runtime, O( nk ) space - one single pass scan
     * k is the length of the longest string
     * n is the total number of strings
     */
    std::vector< std::string > anagrams_impl_2(
            const std::vector< std::string > & strs ) {
        
        std::vector< std::string > results;
        std::unordered_map< std::string, int > m;
        for ( int i = 0; i < strs.size(); ++i ) {
            std::string s( strs[ i ] );
            std::sort( s.begin(), s.end() );
            std::unordered_map< std::string, int >::iterator
            it = m.find( s );
            if ( it == m.end() ) {
                m.insert( std::make_pair( s, i ) );
            } else {
                if ( it->second >= 0 ) {
                    results.push_back( strs[ it->second ] );
                    it->second = -1;
                }
                results.push_back( strs[ i ] );
            }
        }
        return results;
    }
    /**
     * My implementation does not involve sorting but need to define
     * the hash table key for given strings.
     */
    //The class AnagramKey represents a key for a given string
    //It is used to decide whether two strings are anagrams.
    //The idea is simple: counting the number of alphabets from
    //a given string and storing these number in an array.
    class AnagramKey {
        public:
            enum { ALPHABET_NUM = 26 };
            AnagramKey( const std::string & s )
            {
                std::memset( alphabet_count, 0, sizeof( alphabet_count ) );
                for ( std::size_t i = 0; i < s.length(); ++i )
                {
                    ++alphabet_count[ s[ i ] - 'a' ];
                }
            }
            static bool lessThan( const AnagramKey & lhs, const AnagramKey & rhs )
            {
                for ( std::size_t i = 0; i < ALPHABET_NUM; ++i )
                {
                    if ( lhs.alphabet_count[ i ] < rhs.alphabet_count[ i ] )
                        return true;
                    else if ( lhs.alphabet_count[ i ] == rhs.alphabet_count[ i ] )
                        continue;
                    else
                        return false;
                }
                return false;
            }
        private:
            unsigned int alphabet_count[ ALPHABET_NUM ];
    };
    
    //This class is used to create the functor for std::map
    class AnagramKeyLessThan {
    public:
        bool operator () ( const AnagramKey & lhs, const AnagramKey & rhs ) const
        {
            return AnagramKey::lessThan( lhs, rhs );
        }
    };
    
    std::vector< std::string > anagrams_impl_3(
            const std::vector< std::string > & strs ) {
        
        //The AnagramKey to vector of string map
        typedef std::map< AnagramKey, int, AnagramKeyLessThan >
            AnagramKey2IndexMap;
        
        std::vector< std::string > results;
        //loop through given strings to populate the map
        AnagramKey2IndexMap m;
        for ( std::size_t i = 0; i < strs.size(); ++i )
        {
            AnagramKey k( strs[ i ] );
            AnagramKey2IndexMap::iterator it = m.find( k );
            if ( it == m.end() ) {
                m.insert( std::make_pair( k, i ) );
            } else {
                if ( it->second >= 0 ) {
                    results.push_back( strs[ it->second ] );
                    it->second = -1;
                }
                results.push_back( strs[ i ] );;
            }
        }
        return results;
    }
};
