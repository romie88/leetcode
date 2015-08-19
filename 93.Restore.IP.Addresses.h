/**
 * Algorithms 93 Restore IP Addresses                                    Medium
 *
 * Given a string containing only digits, restore it by returning all possible
 * valid IP address combinations.
 *
 * For example:
 * Given "25525511135",
 *
 * return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
 *
 * Tags: Backtracking, String
 */

#include <string>
#include <vector>

class Solution {
public:
    std::vector< std::string > restoreIpAddresses( const std::string & s ) {
        return restore_ip_addresses_backtracking( s );
    }
private:
    std::vector< std::string > restore_ip_addresses_backtracking(
            const std::string & s ) {
        std::vector< std::string > ips;
        std::string                ip;
        restore_ip_addresses_backtracking_helper( s, 0, 0, ip, ips );
        return ips;
    }
    void restore_ip_addresses_backtracking_helper(
            const std::string & s,
            const int           i,
            const int           n,
            std::string       & ip,
            std::vector< std::string > & ips ) {
        const int L = s.length();
        if ( n > 4 || i > L ) return;

        if ( n == 4 && i == L ) {
            ips.push_back( ip );
            return;
        }

        //if there are more characters left than the most we need
        if ( ( 4 - n ) * 3 < ( L - i ) ) return;

        //one digit
        ip.push_back( s[ i ] );
        if ( n < 3 ) ip.push_back( '.' );
        restore_ip_addresses_backtracking_helper( s, i + 1, n + 1, ip, ips );
        if ( n < 3 ) ip.pop_back();

        //two digits
        if ( i + 1 < L && s[ i ] != '0' ) {
            ip.push_back( s[ i + 1 ] );
            if ( n < 3 ) ip.push_back( '.' );
            restore_ip_addresses_backtracking_helper( s, i + 2, n + 1, ip, ips );
            if ( n < 3 ) ip.pop_back();

            //three digits
            if ( i + 2 < L
              && ( s[ i ] == '1'
                || ( s[ i ] == '2' && ( s[ i + 1 ] < '5'
                                     || ( s[ i + 1 ] == '5' && s[ i + 2 ] <= '5' ) ) ) ) ) {
                ip.push_back( s[ i + 2 ] );
                if ( n < 3 ) ip.push_back( '.' );
                restore_ip_addresses_backtracking_helper( s, i + 3, n + 1, ip, ips );
                if ( n < 3 ) ip.pop_back();
                ip.pop_back();
            }

            ip.pop_back();
        }

        ip.pop_back();
    }
};