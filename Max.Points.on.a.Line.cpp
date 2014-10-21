//Max Points on a Line
//Given n points on a 2D plane, find the maximum number of
//points that lie on the same straight line.

#include <vector>
#include <unordered_map>
#include <limits>

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    int maxPoints( std::vector< Point > & points ) {
		
		if ( points.size() <= 1 )
			return points.size();

		int max_p = 0;
		//the maximum number of points that lie on the same straight line
        typedef std::unordered_map< double, int > SlopeMap;
		SlopeMap smap;
		for ( std::vector< Point >::size_type i = 0;
		      i < points.size() - 1; ++i )
		{
			//map from the slope to the number of points that lie on the same
			//straight line as points[ i ] which does not include points[ i ]
			//itself.
			smap.clear();
			int num_duplicates = 0;
			int max_p_for_i = 0;
			for ( std::vector< Point >::size_type j = i + 1;
			      j < points.size(); ++j )
			{
				if ( points[ j ].x == points[ i ].x )
				{
					if ( points[ j ].y == points[ i ].y )
					{
						++num_duplicates;
					}
					else
					{
						++smap[ std::numeric_limits< double >::infinity() ];
					}
				}
				else
				{
					double s = ( static_cast< double >( points[ j ].y ) - points[ i ]. y )
						     / ( static_cast< double >( points[ j ].x ) - points[ i ]. x );
					++smap[ s ];
				}
			}
			
			for ( const auto & si : smap )
			{
				//smap does not count points[ i ] itself
				if ( si.second + 1 > max_p_for_i )
					max_p_for_i = si.second + 1;
			}
			
			max_p_for_i += num_duplicates;
			if ( smap.empty() )
			{
				++max_p_for_i;
			}

			if ( max_p_for_i > max_p )
			{
				max_p = max_p_for_i;
			}
		}

		return max_p;
    }
};
