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
#include <map>
#include <limits>

class LRUCache {

public:

    LRUCache( int capacity )
	: m_capacity( capacity ),
	  m_seq( 0 )
	{}
    
    int get( int key ) {

		//check key in m_key2ValueSeqMap
		Key2ValueSeqMap::iterator it = m_key2ValueSeqMap.find( key );
		if ( it == m_key2ValueSeqMap.end() )
		{
			return -1;
		}
		else
		{
			//found the key, need to update its seq
			unsigned long long seq = it->second.seq;

			Seq2KeyMap::iterator it2 = m_seq2KeyMap.find( seq );
			//it is found certainly!!
			if ( it2 != m_seq2KeyMap.end() )
			{
				m_seq2KeyMap.erase( it2 );
				
				m_seq2KeyMap.insert( std::pair< unsigned long long, int >( m_seq, key ) );
				
				it->second.seq = m_seq;

				if ( m_seq == std::numeric_limits< unsigned long long >::max() )
				{
					reset_seq();
				}
				else
				{
					++m_seq;
				}
			}
			
			return it->second.value;
		}
    }
    
    void set( int key, int value ) {

		Key2ValueSeqMap::iterator it = m_key2ValueSeqMap.find( key );
		if ( it != m_key2ValueSeqMap.end() )
		{
			//update value
			it->second.value = value;
			//update seq
			Seq2KeyMap::iterator it2 = m_seq2KeyMap.find( it->second.seq );
			if ( it2 != m_seq2KeyMap.end() )
			{
				m_seq2KeyMap.erase( it2 );

				m_seq2KeyMap.insert( std::pair< unsigned long long, int >( m_seq, key ) );
				
				it->second.seq = m_seq;

				if ( m_seq == std::numeric_limits< unsigned long long >::max() )
				{
					reset_seq();
				}
				else
				{
					++m_seq;
				}
			}
		}
		else//need to insert
		{
			//delete the least recent entry
        	if ( m_key2ValueSeqMap.size() == m_capacity )
			{
				Seq2KeyMap::iterator it = m_seq2KeyMap.begin();
				if ( it != m_seq2KeyMap.end() )
				{
					int key2delete = it->second;

					m_seq2KeyMap.erase( it );
					
					Key2ValueSeqMap::iterator it2 = m_key2ValueSeqMap.find( key2delete );
					if ( it2 != m_key2ValueSeqMap.end() )
						m_key2ValueSeqMap.erase( it2 );
				}
			}

			m_key2ValueSeqMap.insert( std::pair< int, ValueSeq >( key, ValueSeq( value, m_seq ) ) );
			m_seq2KeyMap.insert( std::pair< unsigned long long, int >( m_seq, key ) );

			if ( m_seq == std::numeric_limits< unsigned long long >::max() )
			{
				reset_seq();
			}
			else
			{
				++m_seq;
			}
		}
    }
	
private:

	void reset_seq() {

		m_seq = 0;
					
		//iterate through m_seq2KeyMap (so seq iterated in order)
		//and update m_key2ValueSeqMap with new increasing seq
		for ( Seq2KeyMap::iterator cit = m_seq2KeyMap.begin();
			  cit != m_seq2KeyMap.end();
			  ++cit )
		{
			int key = cit->second;
			Key2ValueSeqMap::iterator it = m_key2ValueSeqMap.find( key );
			it->second.seq = m_seq++;
		}
					
		//repopulate m_seq2KeyMap from m_key2ValueSeqMap
		m_seq2KeyMap.clear();
		for ( Key2ValueSeqMap::const_iterator cit = m_key2ValueSeqMap.begin();
			  cit != m_key2ValueSeqMap.end();
			  ++cit )
		{
			int key = cit->first;
			unsigned long long seq = cit->second.seq;
			m_seq2KeyMap.insert( std::pair< unsigned long long, int >( seq, key ) );
		}
	}

	struct ValueSeq {
		int value;
		unsigned long long seq;
		ValueSeq( int v, unsigned long long s )
			: value( v ), seq( s )
		{}
	};
	
	int m_capacity;
	unsigned long long m_seq;
	
	typedef std::unordered_map< int, ValueSeq > Key2ValueSeqMap;
	Key2ValueSeqMap	m_key2ValueSeqMap;

	typedef std::map< unsigned long long, int > Seq2KeyMap;
	Seq2KeyMap m_seq2KeyMap;
};
