//Valid Palindrome 2013-01-12
//
//Given a string, determine if it is a palindrome, considering only
//alphanumeric characters and ignoring cases.
//
//For example,
//"A man, a plan, a canal: Panama" is a palindrome.
//"race a car" is not a palindrome.
//
//Note:
//Have you consider that the string might be empty? This is a good
//question to ask during an interview.
//
//For the purpose of this problem, we define empty string as valid
//palindrome.

//Tags: Two Pointers, String

#include <string>
#include <cctype>

class Solution {
public:
    bool isPalindrome( std::string s ) {
        
        bool result = true;
        int i = 0, j = s.length() - 1;
        while ( i < j )
        {
            //skip non alphanumeric
            while ( i < j && ! std::isalnum( s[ i ] ) )
                ++i;
            while ( j > i && ! std::isalnum( s[ j ] ) )
                --j;

            if ( std::tolower( s[ i ] ) != std::tolower( s[ j ] ) )
            {
                result = false;
                break;
            }
            else
            {
                ++i;
                --j;
            }
        }
        
        return result;

    }
};
