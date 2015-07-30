/**
 * Algorithms 71 Simplify Path                                           Medium
 * 
 * Given an absolute path for a file (Unix-style), simplify it.
 * 
 * For example,
 * path = "/home/", => "/home"
 * path = "/a/./b/../../c/", => "/c"
 * 
 * click to show corner cases.
 * 
 * Corner Cases:
 * * Did you consider the case where path = "/../"?
 *   In this case, you should return "/".
 * * Another corner case is the path might contain multiple slashes '/' together,
 *   such as "/home//foo/".
 *   In this case, you should ignore redundant slashes and return "/home/foo".
 * 
 * Tags: Stack, String
 */

#include <string>
#include <vector>
#include <stdexcept>

class Solution {
public:
    std::string simplifyPath( const std::string & path ) {
        return simplify_path_impl( path );
    }
private:
    /**
     * O( n ) runtime, O( n ) space
     */
    std::string simplify_path_impl( const std::string & path ) {
        if ( path.empty() || path[ 0 ] != '/' )
            throw std::invalid_argument( "invalid absolute path" );
        int i = 1;
        const int n = path.length();
        std::vector< std::string > s;
        while ( i < n ) {
            //skip '/' in a row
            while ( i < n && path[ i ] == '/' ) ++i;
            int j = i;
            while ( j < n && path[ j ] != '/' ) ++j;
            const std::string dir_name = path.substr( i, j - i );
            if ( dir_name == ".." ) {
                if ( ! s.empty() ) s.pop_back();
            } else if ( dir_name != "." && ! dir_name.empty() ) {
                s.push_back( dir_name );
            }
            i = j + 1;
        }
        std::string result;
        for ( int i = 0; i < s.size(); ++i ) {
            result += "/";
            result += s[ i ];
        }
        if ( s.empty() ) result += "/";
        return result;
    }
};
