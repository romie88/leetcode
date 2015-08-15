/**
 * Algorithms 89 Gray Code                                               Medium
 *
 * The gray code is a binary numeral system where two successive values differ
 * in only one bit.
 *
 * Given a non-negative integer n representing the total number of bits in the
 * code, print the sequence of gray code. A gray code sequence must begin with
 * 0.
 *
 * For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:
 *
 * 00 - 0
 * 01 - 1
 * 11 - 3
 * 10 - 2
 *
 * Note:
 * For a given n, a gray code sequence is not uniquely defined.
 *
 * For example, [0,2,3,1] is also a valid gray code sequence according to the
 * above definition.
 *
 * For now, the judge is able to judge based on one instance of gray code
 * sequence. Sorry about that.
 *
 * Tags: Backtracking
 */

#include <vector>
#include <stdexcept>

class Solution {
public:
    std::vector< int > grayCode( const int n ) {
        return gray_code_convert( n );
    }
private:
    /**
     * O( n^(2^n) ) runtime - brute force backtracking search
     */
    std::vector< int > gray_code_backtracking( const int n ) {
        const int TOTAL_BITS = sizeof( int ) * 8;
        if ( n < 0 || n > TOTAL_BITS )
            throw std::out_of_range( "n is out of range" );

        std::vector< int > results( 1, 0 );
        std::vector< bool > flags( 1 << n, false );
        flags[ 0 ] = true;
        gray_code_backtracking_helper( n, 0, results, flags );
        return results;
    }
    bool gray_code_backtracking_helper( const int             n,
                           const int             i,
                           std::vector< int  > & results,
                           std::vector< bool > & flags ) {
        const int TOTAL_NUMS = 1 << n;
        if ( results.size() == TOTAL_NUMS ) {
            return results.back() != 0
                && ( ( results.back() & ( results.back() - 1 ) ) == 0 );
        }

        for ( int k = 0; k < n; ++k ) {
            int x = i ^ ( 1 << k );
            if ( flags[ x ] ) continue;
            flags[ x ] = true;
            results.push_back( x );
            if ( gray_code_backtracking_helper( n, x, results, flags ) )
                return true;
            results.pop_back();
            flags[ x ] = false;
        }

        return false;
    }

    /**
     * O( 2^n ) runtime - reflected method standard Gray Code definition
     *
     * n = 1    n = 2      n = 3
     * 0        0   00     00   000
     * 1        1   01     01   001
     *          1   11     11   011
     *          0   10     10   010
     *                     10   110
     *                     11   111
     *                     01   101
     *                     00   100
     */
    std::vector< int > gray_code_reflect( const int n ) {
        const int TOTAL_BITS = sizeof( int ) * 8;
        if ( n < 0 || n > TOTAL_BITS )
            throw std::out_of_range( "n is out of range" );

        std::vector< int > results( 1, 0 );
        for ( int i = 0; i < n; ++i )
            for ( int j = results.size() - 1; j >= 0; --j )
                results.push_back( results[ j ] + ( 1 << i ) );

        return results;
    }

    /**
     * O( 2^n ) runtime - convert binary number to its Gray code
     */
    std::vector< int > gray_code_convert( const int n ) {
        const int TOTAL_BITS = sizeof( int ) * 8;
        if ( n < 0 || n > TOTAL_BITS )
            throw std::out_of_range( "n is out of range" );

        std::vector< int > results;
        for ( int i = 0; i < ( 1 << n ); ++i )
            results.push_back( i ^ ( i >> 1 ) );

        return results;
    }

    /**
     * My extension to find all the possible Gray Codes
     */
    std::vector< std::vector< int > > get_all_gray_codes(
            const int n ) {
        const int TOTAL_BITS = sizeof( int ) * 8;
        if ( n < 0 || n > TOTAL_BITS )
            throw std::out_of_range( "n is out of range" );

        std::vector< std::vector< int > > results;
        std::vector< int > one_result( 1, 0 );
        std::vector< bool > flags( 1 << n, false );
        flags[ 0 ] = true;
        gray_code_searcher( n, 0, results, one_result, flags );

        return results;
    }
    void gray_code_searcher( const int                           n,
                             const int                           i,
                             std::vector< std::vector< int > > & results,
                             std::vector< int >                & one_result,
                             std::vector< bool >               & flags ) {
        const int TOTAL_NUMS = 1 << n;
        if ( one_result.size() == TOTAL_NUMS ) {
            if ( ( one_result.back() & ( one_result.back() - 1 ) ) == 0 ) {
                results.push_back( one_result );
            }
            return;
        }

        for ( int k = 0; k < n; ++k ) {
            int x = i ^ ( 1 << k );
            if ( flags[ x ] ) continue;
            flags[ x ] = true;
            one_result.push_back( x );
            gray_code_searcher( n, x, results, one_result, flags );
            one_result.pop_back();
            flags[ x ] = false;
        }
    }
};