/**
 * Algorithms 18 4Sum                                                    Medium
 * 
 * Given an array S of n integers, are there elements a, b, c, and d in S such
 * that a + b + c + d = target? Find all unique quadruplets in the array which
 * gives the sum of target.
 * 
 * Note:
 * * Elements in a quadruplet (a,b,c,d) must be in non-descending order.
 *   (ie, a <= b <= c <= d)
 * * The solution set must not contain duplicate quadruplets.
 * 
 * For example, given array S = {1 0 -1 0 -2 2}, and target = 0.
 * 
 * A solution set is:
 * (-1,  0, 0, 1)
 * (-2, -1, 1, 2)
 * (-2,  0, 0, 2)
 * 
 * Tags: Array, Hash Table, Two Pointers
 */

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>

class Solution {
public:
    std::vector< std::vector< int > >
    fourSum( std::vector< int > & nums, int target ) {
        return four_sum_3( nums, target );
    }
private:
    /**
     * O( n^2 ) runtime, O( n^2 ) space
     */
    std::vector< std::vector< int > >
    four_sum_1( std::vector< int > & nums, int target ) {
        std::vector< std::vector< int > > results;
        std::sort( nums.begin(), nums.end() );
        std::unordered_map< int, std::vector< std::pair< int, int > > >
            hash_table;
        const int n = nums.size();
        for ( int i = 0; i < n - 1; ++i ) {
            for ( int j = i + 1; j < n; ++j ) {
                int two_sum = nums[ i ] + nums[ j ];
                hash_table[ two_sum ].push_back( std::make_pair( i, j ) );
            }
        }
        
        for ( int i = 0; i < n - 3; ++i ) {
            //skip duplicates
            if ( i > 0 && nums[ i - 1 ] == nums[ i ] )
                continue;
            
            for ( int j = i + 1; j < n - 2; ++j ) {
                //skip duplicates
                if ( j > i + 1 && nums[ j - 1 ] == nums[ j ] )
                    continue;
                
                int rest = target - nums[ i ] - nums[ j ];
                const auto it = hash_table.find( rest );
                if ( it != hash_table.end() ) {
                    const std::vector< std::pair< int, int > > & v = it->second;
                    bool first_pair = false;
                    for ( const auto & p : v ) {
                        if ( p.first > j ) {
                            if ( first_pair == false ) {
                                results.push_back(
                                    std::vector< int >{
                                        nums[ i ], nums[ j ], nums[ p.first ], nums[ p.second ] } );
                                first_pair = true;
                            } else if ( results.back()[ 2 ] != nums[ p.first ] ) {
                                results.push_back(
                                    std::vector< int >{
                                        nums[ i ], nums[ j ], nums[ p.first ], nums[ p.second ] } );
                            }
                        }
                    }
                }
            }
        }
        
        return results;
    }
    
    /**
     * O( n^2 ) runtime, O( n^2 ) space
     */
    std::vector< std::vector< int > >
    four_sum_2( std::vector< int > & nums, int target ) {
        std::vector< std::vector< int > > results;
        std::sort( nums.begin(), nums.end() );
        std::unordered_map< int, std::vector< std::pair< int, int > > >
            hash_table;
        const int n = nums.size();
        for ( int i = 0; i < n - 1; ++i ) {
            for ( int j = i + 1; j < n; ++j ) {
                int two_sum = nums[ i ] + nums[ j ];
                hash_table[ two_sum ].push_back( std::make_pair( i, j ) );
            }
        }
        
        std::set< std::vector< int > > results_set;
        for ( const auto h : hash_table ) {
            const auto it = hash_table.find( target - h.first );
            if ( it != hash_table.end() ) {
                const std::vector< std::pair< int, int > > & v1 = h.second;
                const std::vector< std::pair< int, int > > & v2 = it->second;
                
                
                for ( int i1 = 0; i1 < v1.size(); ++i1 ) {
                    for ( int i2 = 0; i2 < v2.size(); ++i2 ) {
                        const std::pair< int, int > & p1 = v1[ i1 ];
                        const std::pair< int, int > & p2 = v2[ i2 ];
                        if ( p1.first == p2.first || p1.first == p2.second
                          || p1.second == p2.first || p1.second == p2.second )
                            continue;
                        std::vector< int > index_result{ p1.first, p2.first, p1.second, p2.second };
                        std::sort( index_result.begin(), index_result.end() );
                        results_set.insert( std::vector< int >{ nums[ index_result[ 0 ] ], nums[ index_result[ 1 ] ], nums[ index_result[ 2 ] ], nums[ index_result[ 3 ] ] } );
                    }
                }
            }
        }
        
        results.insert( results.begin(), results_set.begin(), results_set.end() );
        return results;
    }
    
    /**
     * Generally recursive solution for k-Sum
     */
    std::vector< std::vector< int > >
    four_sum_3( std::vector< int > & nums, int target ) {
        std::vector< std::vector< int > > results;
        std::vector< int > one_result;
        std::sort( nums.begin(), nums.end() );
        k_sum( nums, 0, nums.size() - 1, target, 4, one_result, results );
        return results;
    }
    
    void k_sum( std::vector< int > & nums, int start, int end, int target,
                int k, std::vector< int > & one_result,
                std::vector< std::vector< int > > & results ) {
        if ( k <= 0 ) return;
        else if ( k == 1 ) {
            for ( int i = start; i <= end; ++i ) {
                if ( nums[ i ] == target ) {
                    one_result.push_back( target );
                    results.push_back( one_result );
                    one_result.pop_back();
                    return;
                }
            }
        } else if ( k == 2 ) {
            two_sum( nums, start, end, target, one_result, results );
            return;
        }
        
        for ( int i = start; i <= end - k + 1; ++i ) {
            if ( i > start && nums[ i ] == nums[ i - 1 ] ) continue;
            one_result.push_back( nums[ i ] );
            k_sum( nums, i + 1, end, target - nums[ i ], k - 1, one_result, results );
            one_result.pop_back();
        }
    }
    
    void two_sum( std::vector< int > & nums, int start, int end, int target,
                  std::vector< int > & one_result,
                  std::vector< std::vector< int > > & results ) {
        while ( start < end ) {
            int sum = nums[ start ] + nums[ end ];
            if ( sum == target ) {
                one_result.push_back( nums[ start ] );
                one_result.push_back( nums[ end   ] );
                results.push_back( one_result );
                one_result.pop_back();
                one_result.pop_back();
                ++start;
                --end;
                while ( nums[ start ] == nums[ start - 1 ] ) ++start;
                while ( nums[ end   ] == nums[ end   + 1 ] ) --end;
            } else if ( sum < target )
                ++start;
            else
                --end;
        }
    }
};
