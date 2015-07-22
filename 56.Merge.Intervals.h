/**
 * Algorithms 56 Merge Intervals                                           Hard
 * 
 * Given a collection of intervals, merge all overlapping intervals.
 * 
 * For example,
 * Given [1,3],[2,6],[8,10],[15,18],
 * return [1,6],[8,10],[15,18].
 * 
 * Tags: Array, Sort
 * Similar Problems: (H) Insert Interval
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
    std::vector< Interval > merge( std::vector< Interval > & intervals ) {
        return merge_impl( intervals );
    }
private:
    struct IntervalComparator {
        bool operator() ( const Interval & lhs, const Interval & rhs ) const {
#if 0
            return lhs.start < rhs.start
                || ( lhs.start == rhs.start && lhs.end < rhs.end );
#endif
            if ( lhs.start < rhs.start ) return true;
            else if ( lhs.start == rhs.start ) return lhs.end < rhs.end;
            //note that the above < cannot be replaced with <= otherwise
            //there will be runtime error in sort()
            else return false;
        }
    };
    /**
     * O( n log n ) runtime, O( n ) space - sort and merge
     */
    std::vector< Interval > merge_impl( std::vector< Interval > & intervals ) {
        std::vector< Interval > results;
        std::sort( intervals.begin(), intervals.end(), IntervalComparator() );
        if ( intervals.empty() ) return results;
        results.push_back( intervals[ 0 ] );
        for ( int i = 1; i < intervals.size(); ++i ) {
            if ( results.back().end >= intervals[ i ].start )
                results.back().end = std::max( results.back().end,
                                               intervals[ i ].end );
            else
                results.push_back( intervals[ i ] );
        }
        return results;
    }
};
