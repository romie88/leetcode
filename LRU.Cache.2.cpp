//LRU Cache
//
//Design and implement a data structure for Least Recently Used (LRU) cache.
//It should support the following operations: get and set.
//
//get(key) - Get the value (will always be positive) of the key if the key
//exists in the cache, otherwise return -1.
//
//set(key, value) - Set or insert the value if the key is not already present.
//When the cache reached its capacity, it should invalidate the least recently
//used item before inserting a new item.

//Tags: Data Structure

#include <unordered_map>
#include <list>
#include <limits>

class LRUCache {

public:

    LRUCache( int capacity )
	: m_capacity( capacity )
	{}
    
    int get( int key ) {

		Key2ValueIterMap::iterator it = m_key2ValueIterMap.find( key );
		if ( it == m_key2ValueIterMap.end() )
		{
			return -1;
		}
		else
		{
			KeyList::iterator keyListIter = it->second.iter;
			//move key to the end of m_keyList
			m_keyList.erase( keyListIter );
			m_keyList.push_back( key );
			it->second.iter = --m_keyList.end();

			return it->second.value;
		}
    }
    
    void set( int key, int value ) {

		Key2ValueIterMap::iterator it = m_key2ValueIterMap.find( key );
		if ( it != m_key2ValueIterMap.end() )
		{
			//update value
			it->second.value = value;
			
			KeyList::iterator keyListIter = it->second.iter;
			//move key to the end of m_keyList
			m_keyList.erase( keyListIter );
			m_keyList.push_back( key );
			it->second.iter = --m_keyList.end();
		}
		else//need to insert
		{
			//delete the oldest entry
        	if ( m_key2ValueIterMap.size() == m_capacity )
			{
				KeyList::iterator keyListIter = m_keyList.begin();
				int key = *keyListIter;
				m_keyList.pop_front();
				m_key2ValueIterMap.erase( key );
			}
			
			m_keyList.push_back( key );
			KeyList::iterator keyListIter = --m_keyList.end();
			m_key2ValueIterMap.insert( std::pair< int, ValueIter >( key, ValueIter( value, keyListIter ) ) );
		}
    }
	
private:

	typedef std::list< int > KeyList;
	KeyList m_keyList;//store the keys from oldest to latest

	struct ValueIter {
		int value;
		KeyList::iterator iter;
		ValueIter( int v, KeyList::iterator i )
			: value( v ), iter( i )
		{}
	};
	
	int m_capacity;
	
	typedef std::unordered_map< int, ValueIter > Key2ValueIterMap;
	Key2ValueIterMap m_key2ValueIterMap;
};
