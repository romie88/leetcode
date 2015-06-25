/**
 * 210 Course Schedule II                                                Medium
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
 * finished course 0. So the correct course order is [0,1]
 * 
 * 4, [[1,0],[2,0],[3,1],[3,2]]
 * 
 * There are a total of 4 courses to take. To take course 3 you should have
 * finished both courses 1 and 2. Both courses 1 and 2 should be taken after
 * you finished course 0. So one correct course order is [0,1,2,3]. Another
 * correct ordering is[0,2,1,3].
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
#include <list>

class Solution {
public:
    std::vector< int > findOrder(
            const int                                    numCourses,
            const std::vector< std::pair< int, int > > & prerequisites ) {
        std::vector< int > orders;
        find_order_dfs2( numCourses, prerequisites, orders );
        return orders;
    }
private:
    void find_order_bfs(
            const int                                    numCourses,
            const std::vector< std::pair< int, int > > & prerequisites,
            std::vector< int >                         & orders ) {
        
        std::vector< std::vector< int > >
                adj( numCourses, std::vector< int >() );
        std::vector< int > indegree( numCourses, 0 );
        
        for ( int i = 0; i < prerequisites.size(); ++i ) {
            adj[ prerequisites[ i ].second ].push_back( prerequisites[ i ].first );
            ++indegree[ prerequisites[ i ].first ];
        }
        
        std::queue< int > q;
        for ( int i = 0; i < indegree.size(); ++i )
            if ( indegree[ i ] == 0 )
                q.push( i );
        
        while ( ! q.empty() ) {
            int k = q.front();
            q.pop();
            orders.push_back( k );
            for ( int j = 0; j < adj[ k ].size(); ++j ) {
                --indegree[ adj[ k ][ j ] ];
                if ( indegree[ adj[ k ][ j ] ] == 0 )
                    q.push( adj[ k ][ j ] );
            }
        }
        
        if ( orders.size() != numCourses ) orders.clear();
    }
    
    /**
     * This DFS implement is based on
     * https://en.wikipedia.org/wiki/Topological_sorting
     */
    void find_order_dfs(
            const int                                    numCourses,
            const std::vector< std::pair< int, int > > & prerequisites,
            std::vector< int >                         & orders ) {
        
        std::vector< std::vector< int > >
                adj( numCourses, std::vector< int >() );
        
        for ( int i = 0; i < prerequisites.size(); ++i )
            adj[ prerequisites[ i ].second ].push_back( prerequisites[ i ].first );
        
        bool is_DAG = true;
        std::list< int > orders_list;
        //unfortunately boolean visited flag vector is not enough
        //consider the G = ( V, E ) where V = { 0, 1 } and E = { ( 1, 0 ) }
        //we first visit 0 then visit 1. When we visit 1, 0 is already visited.
        std::vector< int > status( numCourses, 0 );
        //0 - unexplored
        //1 - in DFS processing
        //2 - done
        for ( int i = 0; i < numCourses; ++i ) {
            if ( status[ i ] == 0 )
                if ( ! find_order_dfs_impl( i, adj, status, orders_list ) ) {
                    is_DAG = false;
                    break;
                }
        }
        
        if ( is_DAG ) {
            for ( std::list< int >::const_iterator cit = orders_list.cbegin();
                  cit != orders_list.end(); ++cit )
                orders.push_back( *cit );
        }
    }
    
    bool find_order_dfs_impl(
            const int                                 i,
            const std::vector< std::vector< int > > & adj,
            std::vector< int >                      & status,
            std::list< int >                        & orders_list ) {
        
        if ( status[ i ] == 1 )//Not a DAG
            return false;
        else if ( status[ i ] == 0 ) {
            status[ i ] = 1;
            for ( int k = 0; k < adj[ i ].size(); ++k ) {
                if ( ! find_order_dfs_impl( adj[ i ][ k ],
                                            adj,
                                            status,
                                            orders_list ) )
                    return false;
            }
            status[ i ] = 2;
            orders_list.push_front( i );
        }
        return true;
    }
    
    /**
     * Very similar to previous DFS implementation without using
     * list< int >.
     */
    void find_order_dfs2(
            const int                                    numCourses,
            const std::vector< std::pair< int, int > > & prerequisites,
            std::vector< int >                         & orders ) {
        
        std::vector< std::vector< int > >
                adj( numCourses, std::vector< int >() );
        
        for ( int i = 0; i < prerequisites.size(); ++i )
            adj[ prerequisites[ i ].second ].push_back( prerequisites[ i ].first );
        
        bool is_DAG = true;
        //unfortunately boolean visited flag vector is not enough
        //consider the G = ( V, E ) where V = { 0, 1 } and E = { ( 1, 0 ) }
        //we first visit 0 then visit 1. When we visit 1, 0 is already visited.
        std::vector< int > status( numCourses, 0 );
        //0 - unexplored
        //1 - in DFS processing
        //2 - done
        int index = numCourses;
        orders.resize( numCourses, 0 );
        for ( int i = 0; i < numCourses; ++i ) {
            if ( status[ i ] == 0 )
                if ( ! find_order_dfs_impl2( i, adj, status, orders, index ) ) {
                    is_DAG = false;
                    break;
                }
        }
        
        if ( ! is_DAG ) orders.clear();
    }
    
    bool find_order_dfs_impl2(
            const int                                 i,
            const std::vector< std::vector< int > > & adj,
            std::vector< int >                      & status,
            std::vector< int >                      & orders,
            int                                     & index ) {
        
        if ( status[ i ] == 1 )//Not a DAG
            return false;
        else if ( status[ i ] == 0 ) {
            status[ i ] = 1;
            for ( int k = 0; k < adj[ i ].size(); ++k ) {
                if ( ! find_order_dfs_impl2( adj[ i ][ k ],
                                             adj,
                                             status,
                                             orders,
                                             index ) )
                    return false;
            }
            status[ i ] = 2;
            orders[ --index ] = i;
        }
        return true;
    }
};
