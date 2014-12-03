//Distinct Subsequences 2012-10-18
//
//Given a string S and a string T, count the number of distinct subsequences
//of T in S.
//
//A subsequence of a string is a new string which is formed from the original
//string by deleting some (can be none) of the characters without disturbing
//the relative positions of the remaining characters. (ie, "ACE" is a
//subsequence of "ABCDE" while "AEC" is not).
//
//Here is an example:
//S = "rabbbit", T = "rabbit"
//
//Return 3.

//Tags:

#include <string>

class Solution {
public:
    int numDistinct( std::string S, std::string T ) {
        
        return num_distinct_imp( S, S.length() - 1, T, T.length() - 1 );
    }
private:
    int num_distinct_imp( const std::string & S,
                          int s_end,
                          const std::string & T,
                          int t_end )
    {
        if ( t_end == 0 )
            return 1;

        if ( t_end > s_end )
            return 0;
        else if ( t_end == s_end )
        {
            int i = s_end;
            for ( ; i >= 0 && S[ i ] == T[ i ]; --i )
                ;
            return i >= 0 ? 0 : 1; 
        }
        else
        {
            int i = s_end;
            for ( ; i >= 0; --i )
            {
                if ( S[ i ] == T[ t_end ] )
                    break;
            }
            
            return num_distinct_imp( S, i - 1, T, t_end )
                 + num_distinct_imp( S, i - 1, T, t_end - 1 );
        }
    }
};
