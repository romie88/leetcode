/**
 * Algorithms 57 Insert Interval                                           Hard
 * 
 * Given a set of non-overlapping intervals, insert a new interval into the
 * intervals (merge if necessary).
 * 
 * You may assume that the intervals were initially sorted according to their
 * start times.
 * 
 * Example 1:
 * Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
 * 
 * Example 2:
 * Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as
 * [1,2],[3,10],[12,16].
 * 
 * This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
 * 
 * Tags: Array, Sort
 * Similar Problems: (H) Merge Intervals
 */

#include <vector>
#include <algorithm>

 /**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    std::vector< Interval > insert( const std::vector< Interval > & intervals,
                                    const Interval                  newInterval ) {
        return insert_impl_3( intervals, newInterval );
    }
private:
    /**
     * O( n ) runtime, O( n ) space - my implementation
     */
    std::vector< Interval > insert_impl(
            const std::vector< Interval > & intervals,
            const Interval                  newInterval ) {
        std::vector< Interval > results;
        const int n = intervals.size();
 #if 0
        int i = 0;
        for ( ; i < n; ++i )
            if ( newInterval.start <= intervals[ i ].start ) break;
        
        int j = i == 0 ? 0 : i - 1;
        for ( ; j < n; ++j )
            if ( newInterval.end < intervals[ j ].start ) break;
#endif
        if ( n == 0 ) {
            results.push_back( newInterval );
            return results;
        }
        int i = binary_search_left( intervals, newInterval.start, 0, n - 1 );
        int j = binary_search_right( intervals, newInterval.end, i == 0 ? 0 : i - 1, n - 1 );
        
        Interval merged;
        //to analyze all the cases:
        //i == 0
        //i == n
        //0 < i < n
        //we can reduce all the three cases into the follow if-else logic
        if ( i > 0 && newInterval.start <= intervals[ i - 1 ].end ) {
            merged.start = intervals[ i - 1 ].start;
            --i;
        } else
            merged.start = newInterval.start;
        //all the intervals whose index < i do not involve in the merging
        //with the newInternval
        //j == 0
        //j == n
        //0 < j < n
        //similar as before we can reduce all the three cases into the if-else
        if ( j == 0 ) merged.end = newInterval.end;
        else {
            if ( newInterval.end <= intervals[ j - 1 ].end )
                merged.end = intervals[ j - 1 ].end;
            else
                merged.end = newInterval.end;
        }
        
        for ( int k = 0; k < i; ++k ) results.push_back( intervals[ k ] );
        results.push_back( merged );
        for ( int k = j; k < n; ++k ) results.push_back( intervals[ k ] );
        
        return results;
    }
    int binary_search_left( const std::vector< Interval > & intervals,
                            const int x,
                            int L, int R ) {
        while ( L <= R ) {
            int M = ( L + R ) / 2;
            if ( x <= intervals[ M ].start )
                R = M - 1;
            else
                L = M + 1;
        }
        return L;
    }
    int binary_search_right( const std::vector< Interval > & intervals,
                             const int x,
                             int L, int R ) {
        while ( L <= R ) {
            int M = ( L + R ) / 2;
            if ( x < intervals[ M ].start )
                R = M - 1;
            else
                L = M + 1;
        }
        return L;
    }
    
    /**
     * O( n ) runtime, O( n ) space - linear scan and merge
     */
    std::vector< Interval > insert_impl_2(
            const std::vector< Interval > & intervals,
            const Interval                  newInterval ) {
        std::vector< Interval > results;
        const int n = intervals.size();
        int i = 0;
        Interval iv( newInterval );
        bool iv_pushed = false;
        for ( ; i < n; ++i ) {
            if ( is_overlapping( iv, intervals[ i ] ) ) {
                iv.start = std::min( iv.start, intervals[ i ].start );
                iv.end   = std::max( iv.end,   intervals[ i ].end   );
            } else if ( iv.end < intervals[ i ].start ) {
                results.push_back( iv );
                iv_pushed = true;
                break;
            } else {
                results.push_back( intervals[ i ] );
            }
        }
        if ( ! iv_pushed ) results.push_back( iv );
        else {
            for ( int k = i; k < n; ++k )
                results.push_back( intervals[ k ] );
        }
        return results;
    }
    bool is_overlapping( const Interval & iv1, const Interval & iv2 ) {
        if ( iv1.start <= iv2.start )
            return iv2.start <= iv1.end;
        else
            return iv1.start <= iv2.end;
        //return iv1.start <= iv2.end && iv2.start <= iv1.end;
    }
    
    /**
     * O( n ) runtime, O( n ) space - one pass linear scan
     */
    std::vector< Interval > insert_impl_3(
            const std::vector< Interval > & intervals,
            const Interval                  newInterval ) {
        std::vector< Interval > results;
        const int n = intervals.size();
        if ( n == 0 ) {
            results.push_back( newInterval );
            return results;
        }
        
        int i = 0;
        Interval iv( newInterval );
        while ( i < n && intervals[ i ].end < iv.start ) {
            results.push_back( intervals[ i ] );
            ++i;
        }
        if ( i < n ) iv.start = std::min( iv.start, intervals[ i ].start );
        while ( i < n && intervals[ i ].start <= iv.end ) {
            iv.end = std::max( intervals[ i ].end, iv.end );
            ++i;
        }
        results.push_back( iv );
        while ( i < n ) {
            results.push_back( intervals[ i ] );
            ++i;
        }
        
        return results;
    }
};

