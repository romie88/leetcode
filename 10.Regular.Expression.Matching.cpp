//10 Regular Expression Matching [ Hard ]
//
//Implement regular expression matching with support for '.' and '*'.
//
//'.' Matches any single character.
//'*' Matches zero or more of the preceding element.
//
//The matching should cover the entire input string (not partial).
//
//The function prototype should be:
//bool isMatch(const char *s, const char *p)
//
//Some examples:
//isMatch("aa","a") → false
//isMatch("aa","aa") → true
//isMatch("aaa","aa") → false
//isMatch("aa", "a*") → true
//isMatch("aa", ".*") → true
//isMatch("ab", ".*") → true
//isMatch("aab", "c*a*b") → true

//Tags: Dynamic Programming, Backtracking, String

class Solution {
public:
    bool isMatch( const char * s, const char * p ) {
        
        while ( *p && *s ) {
                
            //if next character from the pattern string is not null
            if ( *( p + 1 ) ) {
                if ( *( p + 1 ) == '*' ) {
                    if ( *p == '.' ) {//.*
                        
                        while ( *s )
                            if ( isMatch( s, p + 2 ) )
                                return true;
                            else
                                ++s;
    
                        return isMatch( s, p + 2 );
    
                    } else {
                        if ( *p != *s )
                            return isMatch( s, p + 2 );
                        else {
                            char c = *s;
                            while ( *s == c )
                                if ( isMatch( s, p + 2 ) )
                                    return true;
                                else
                                    ++s;
                            
                            return isMatch( s, p + 2 );
                        }
                    }
                } else {
                    if ( *p == '.' || *p == *s ) {
                        ++p;
                        ++s;
                    } else {
                        return false;
                    }
                }
            } else {
                if ( *p == '.' || *p == *s ) {
                    ++p;
                    ++s;
                } else {
                    return false;
                }
            }
        }
    
        if ( ! *p ) {
            return ! *s;
        } else {//s points to nul character but p points to non-nul character
            //handle case like "" against "c*c*"
            while ( *p && *( p + 1 ) == '*' )
                p += 2;
            
            return ! *p;
        }
    }
};

