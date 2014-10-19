//Reverse Words in a String
//
//Given an input string, reverse the string word by word.
//
//For example,
//Given s = "the sky is blue",
//return "blue is sky the".
//
//Clarification:
//
//What constitutes a word?
//
//A sequence of non-space characters constitutes a word.
//
//Could the input string contain leading or trailing spaces?
//
//Yes. However, your reversed string should not contain leading or trailing spaces.
//
//How about multiple spaces between two words?
//
//Reduce them to a single space in the reversed string.

#include <string>
#include <cctype>
#include <vector>

class Solution {
public:
    void reverseWords( std::string & s ) {
        
		bool in_word = false;
		std::string word;
		std::vector< std::string > words;
		for ( std::string::size_type i = 0;
		      i < s.length(); ++i )
		{
			if ( std::isspace( s[ i ] ) )
			{
				if ( in_word )
				{
					words.push_back( word );
					word.clear();
					in_word = false;
				}
			}
			else//see a nonspace character
			{
				in_word = true;
				word.push_back( s[ i ] );
			}
		}
		if ( in_word )
		{
			words.push_back( word );
		}
		
		s.clear();
		for ( auto crit = words.crbegin();
		      crit != words.crend(); ++crit )
		{
			s.append( *crit );
			if ( crit + 1 != words.crend() )
			{
				s.push_back( ' ' );
			}
		}
    }
};
