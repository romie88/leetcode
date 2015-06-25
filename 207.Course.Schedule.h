/**
 * 207 Course Schedule II                                                Medium
 * 
 * There are a total of n courses you have to take, labeled from 0 to n - 1.
 * 
 * Some courses may have prerequisites, for example to take course 0 you have
 * to first take course 1, which is expressed as a pair: [0,1]
 * 
 * Given the total number of courses and a list of prerequisite pairs, return
 * the ordering of courses you should take to finish all courses.
 * 
 * There may be multiple correct orders, you just need to return one of them.
 * If it is impossible to finish all courses, return an empty array.
 * 
 * For example:
 * 
 * 2, [[1,0]]
 * 
 * There are a total of 2 courses to take. To take course 1 you should have
 * finished course 0. So it is possible.
 * 
 * 2, [[1,0],[0,1]]
 * 
 * There are a total of 2 courses to take. To take course 1 you should have
 * finished course 0, and to take course 0 you should also have finished course
 * 1. So it is impossible.
 * 
 * Note:
 * 
 * The input prerequisites is a graph represented by a list of edges, not
 * adjacency matrices. Read more about how a graph is represented.
 * https://www.khanacademy.org/computing/computer-science/algorithms/graph-representation/a/representing-graphs
 * 
 * click to show more hints.
 * 
 * Hints:
 * 
 * 1. This problem is equivalent to finding the topological order in a directed
 *    graph. If a cycle exists, no topological ordering exists and therefore it
 *    will be impossible to take all courses.
 * 2. Topological Sort via DFS - A great video tutorial (21 minutes) on
 *    Coursera explaining the basic concepts of Topological Sort.
 *    https://class.coursera.org/algo-003/lecture/52
 * 3. Topological sort could also be done via BFS.
 *    http://en.wikipedia.org/wiki/Topological_sorting#Algorithms
 * 
 * Tags: Depth-first Search, Breadth-first Search, Graph, Topological Sort
 */

#include <vector>
#include <queue>

class Solution {
public:
    bool canFinish(
            const int                                    numCourses,
            const std::vector< std::pair< int, int > > & prerequisites ) {
        return can_finish_dfs( numCourses, prerequisites );
    }
private:
    bool can_finish_bfs(
            const int                                    numCourses,
            const std::vector< std::pair< int, int > > & prerequisites ) {
        
        std::vector< std::vector< int > >
                adj( numCourses, std::vector< int >() );
        std::vector< int > indegree( numCourses, 0 );
        
        //process the input and populate adjacent list(vector) and indegree
        for ( int i = 0;  i < prerequisites.size(); ++i ) {
            adj[ prerequisites[ i ].second ].push_back( prerequisites[ i ].first );
            ++indegree[ prerequisites[ i ].first ];
        }
        
        std::queue< int > q;
        for ( int i = 0; i < indegree.size(); ++i ) {
            if ( indegree[ i ] == 0 )
                q.push( i );
        }
        
        int count = 0;
        while ( ! q.empty() ) {
            int k = q.front();
            q.pop();
            ++count;
            for ( int i = 0; i < adj[ k ].size(); ++i ) {
                if ( --indegree[ adj[ k ][ i ] ] == 0 )
                    q.push( adj[ k ][ i ] );
            }
        }
        
        return count == numCourses;
    }
    
    bool can_finish_dfs(
            const int                                    numCourses,
            const std::vector< std::pair< int, int > > & prerequisites ) {
        
        std::vector< std::vector< int > >
                adj( numCourses, std::vector< int >() );
        
        //process the input and populate adjacent list(vector)
        for ( int i = 0;  i < prerequisites.size(); ++i )
            adj[ prerequisites[ i ].second ].push_back( prerequisites[ i ].first );
        
        std::vector< int > status( numCourses, 0 );
        // 0 - unexplored
        // 1 - in discovery process
        // 2 - done
        for ( int i = 0; i < numCourses; ++i )
            if ( status[ i ] == 0 && ! can_finish_dfs_impl( i, adj, status ) )
                    return false;
        
        return true;
    }
    
    bool can_finish_dfs_impl(
            const int                                 i,
            const std::vector< std::vector< int > > & adj,
            std::vector< int >                      & status ) {
        
        if ( status[ i ] == 1 )
            return false;
        else if ( status[ i ] == 0 ) {
            status[ i ] = 1;
            for ( int k = 0; k < adj[ i ].size(); ++k )
                if ( ! can_finish_dfs_impl( adj[ i ][ k ], adj, status ) )
                    return false;
            status[ i ] = 2;
        }
        return true;
    }
};
