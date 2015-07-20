/**
 * Algorithms 44 Wildcard Matching                                         Hard
 * 
 * Implement wildcard pattern matching with support for '?' and '*'.
 *
 * '?' Matches any single character.
 * '*' Matches any sequence of characters (including the empty sequence).
 *
 * The matching should cover the entire input string (not partial).
 * 
 * The function prototype should be:
 * bool isMatch(const char *s, const char *p)
 * 
 * Some examples:
 * isMatch("aa","a") -> false
 * isMatch("aa","aa") -> true
 * isMatch("aaa","aa") -> false
 * isMatch("aa", "*") -> true
 * isMatch("aa", "a*") -> true
 * isMatch("ab", "?*") -> true
 * isMatch("aab", "c*a*b") -> false
 *
 * Tags: Dynamic Programming, Backtracking, Greedy, String
 * Similar Problems: (H) Regular Expression Matching
 */

#include <string>

class Solution {
public:
    bool isMatch( const std::string & s, const std::string & p ) {
        return is_match_iterative( s, p );
    }
private:
    /**
     * Exponential runt time - brute force recursive
     * TLE on input
     * "abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb", "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb"
     */
    bool is_match_brute_force_recursive_impl( const std::string & s, int si,
                                              const std::string & p, int pi ) {
        const int n = s.length();
        const int m = p.length();
        if ( pi == m ) return si == n;
        if ( si == n ) {
            //if there is any trailing '*'s in the pattern string
            //skip all of them since they match zero characters
            while ( pi < m && p[ pi ] == '*' ) ++pi;
            //if there is any characters left in the pattern string
            return pi == m;
        }
        
        if ( p[ pi ] == '?' || s[ si ] == p[ pi ] )
            return is_match_brute_force_recursive_impl( s, si + 1, p, pi + 1 );
        else if ( p[ pi ] == '*' ) {
            //skip any continuous '*'s
            while ( pi < m && p[ pi ] == '*' ) ++pi;
            //now pi points to the end or pi points the non-'*'
#if 0
            return is_match_brute_force_recursive_impl( s, si, p, pi )
                   //match zero character
                   //note that we pass in pi which points to the end or non-'*'
                || is_match_brute_force_recursive_impl( s, si + 1, p, pi - 1 );
                   //match one or more characters
                   //note that we need to pass in pi - 1 which points to '*'
#endif
            //the above pure recursive code can also be implemented in an
            //iterative way
            for ( int k = si; k <= n; ++k )
                if ( is_match_brute_force_recursive_impl( s, k, p, pi ) )
                    return true;
            return false;
        } else
            return false;
    }
    bool is_match_brute_force_recursive( const std::string & s,
                                         const std::string & p ) {
        return is_match_brute_force_recursive_impl( s, 0, p, 0 );
    }
    /**
     * O( n * m ) runtime, O( n * m ) space - DP
     * n is the length of the string s and m is the length of the string p
     * D[ i ][ j ] = true    if p[ 0 ... i - 1 ] matches s[ 0 ... j - 1 ]
     * D[ 0 ][ 0 ] = true    the empty p matches the empty s
     * D[ 0 ][ j ] = false   when j = 1 ... n
     * 
     * if p[ i - 1 ] == '*' then D[ i ][ j ] = D[ i - 1 ][ j ] || D[ i ][ j - 1 ]
     * if p[ i - 1 ] == '?' || s[ i ] == p[ i ] then D[ i ][ j ] = D[ i - 1 ][ j - 1 ]
     * else D[ i ][ j ] = false
     * 
     * And important boundary case
     * D[ i ][ 0 ] = D[ i - 1 ][ 0 ] && p[ i - 1 ] == '*'
     */
    bool is_match_DP( const std::string & s, const std::string & p ) {
        const int n = s.length();
        const int m = p.length();
        
        //a hack to avoid leetcode oj TLE
        int num_not_star = 0;
        for ( int i = 0; i < m; ++i )
            if ( p[ i ] != '*' ) ++num_not_star;
        if ( num_not_star > n ) return false;
        
        std::vector< std::vector< bool > >
            D( m + 1, std::vector< bool >( n + 1, false ) );
        //use bool D[ 500 ][ 500 ] to avoid leetcode oj MLE
        D[ 0 ][ 0 ] = true;
        for ( int i = 1; i <= m; ++i ) {
            D[ i ][ 0 ] = D[ i - 1 ][ 0 ] && p[ i - 1 ] == '*';
            for ( int j = 1; j <= n; ++j ) {
                if ( p[ i - 1 ] == '*' ) {
                    D[ i ][ j ] = D[ i - 1 ][ j ] || D[ i ][ j - 1 ];
                } else if ( p[ i - 1 ] == '?' || p[ i - 1 ] == s[ j - 1 ] ) {
                    D[ i ][ j ] = D[ i - 1 ][ j - 1 ];
                }
            }
        }
        return D[ m ][ n ];
    }
    /**
     * O( n * m ) runtime, O( n ) space - DP space optimized
     */
    bool is_match_DP2( const std::string & s, const std::string & p ) {
        const int n = s.length();
        const int m = p.length();
        
        //a hack to avoid leetcode oj TLE
        int num_not_star = 0;
        for ( int i = 0; i < m; ++i )
            if ( p[ i ] != '*' ) ++num_not_star;
        if ( num_not_star > n ) return false;
        
        std::vector< bool > D1( n + 1, false );
        std::vector< bool > D2( n + 1, false );
        D1[ 0 ] = true;
        for ( int i = 1; i <= m; ++i ) {
            D2[ 0 ] = D1[ 0 ] && p[ i - 1 ] == '*';
            for ( int j = 1; j <= n; ++j ) {
                if ( p[ i - 1 ] == '*' ) {
                    D2[ j ] = D1[ j ] || D2[ j - 1 ];
                }
#if 0
                else if ( p[ i - 1 ] == '?' || p[ i - 1 ] == s[ j - 1 ] ) {
                    D2[ j ] = D1[ j - 1 ];
                } else
                    D2[ j ] = false;
#endif
                else
                    D2[ j ] = D1[ j - 1 ]
                           && ( p[ i - 1 ] == '?' || p[ i - 1 ] == s[ j - 1 ] );
            }
            D1.swap( D2 );
        }
        return D1[ n ];
    }
    /**
     * This is an iterative scanning solution.
     */
    bool is_match_iterative( const std::string & s,
                             const std::string & p ) {
        int si = 0;
        int pi = 0;
        int si_save = -1;
        int pi_save = -1;
        int n = s.length();
        int m = p.length();
        /**
         * You may ask why the outer loop is iterating through s instead of p?
         * The reason is simple: consider the case s = "hi" and p = "*?".
         * If we write the outer loop like:
         * while ( pi < m ) {
         * ...
         * }
         * We will run into the problem that when pi == m, we want to go back
         * to si_save and pi_save and use the latest '*' to match more
         * characters from s to save more characters from p.
         */
        while ( si < n ) {
            if ( pi >= m ) {
                if ( pi_save == -1 ) return false;
                ++si_save;
                si = si_save;
                pi = pi_save;
            } else if ( p[ pi ] == '*' ) {
                //skip mutiple '*'
                while ( pi < m && p[ pi ] == '*' )
                    ++pi;
                if ( pi == m ) return true;
                si_save = si;
                pi_save = pi;
                //I have a big question here:
                //we alway save/override with the latest '*' we meet.
                //If there is a mismatch happening we will only go back
                //to the latest '*' and use it to match more character
                //do we need to go back to the previous '*' or even
                //further?
            } else if ( p[ pi ] == '?' || p[ pi ] == s[ si ] ) {
                ++si;
                ++pi;
            } else {
                if ( pi_save == -1 ) return false;
                ++si_save;
                si = si_save;
                pi = pi_save;
            }
        }
        
        while ( pi < m && p[ pi ] == '*' )
            ++pi;
        
        return pi == m;
    }
    /**
     * An alternative view on this problem:
     * Divide p into segments by '*' and try to match these segments in s
     * as long as these segments have matching in s and these matchings are not
     * overlapping we say it matches. Note that if the first segment does not
     * start with '*', we must start comparing with the first character in s.
     * And if the last segment does not end with '*', we must compare the last
     * character in s.
     */
};
