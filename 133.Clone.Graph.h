/**
 * 133 Clone Graph                                                       Medium
 * 
 * Clone an undirected graph. Each node in the graph contains a label and
 * a list of its neighbors.
 * 
 * 
 * OJ's undirected graph serialization:
 * 
 * Nodes are labeled uniquely.
 * 
 * We use # as a separator for each node, and , as a separator for node
 * label and each neighbor of the node.
 * 
 * As an example, consider the serialized graph {0,1,2#1,2#2,2}.
 * 
 * The graph has a total of three nodes, and therefore contains three parts
 * as separated by #.
 * 
 * 1. First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
 * 2. Second node is labeled as 1. Connect node 1 to node 2.
 * 3. Third node is labeled as 2. Connect node 2 to node 2 (itself), thus
 *    forming a self-cycle.
 * 
 * Visually, the graph looks like the following:
 * 
 *        1
 *       / \
 *      /   \
 *     0 --- 2
 *          / \
 *          \_/
 * 
 * Tags: Depth-first Search, Breath-first Search, Graph
 */

#include <set>
#include <map>
#include <utility>
#include <queue>

/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode * cloneGraph( UndirectedGraphNode * node ) {
        return clone_graph_dfs2( node );
    }
private:
    /**
     * DFS implementation
     */
    UndirectedGraphNode * clone_graph_dfs( UndirectedGraphNode * node ) {
        if ( node == nullptr ) return node;
        
        std::set< int > s;
        std::map< UndirectedGraphNode *, UndirectedGraphNode * > m;
        return clone_graph_dfs_impl( node, s, m );
    }
    UndirectedGraphNode * clone_graph_dfs_impl(
            UndirectedGraphNode                                      * p,
            std::set< int >                                          & s,
            std::map< UndirectedGraphNode *, UndirectedGraphNode * > & m ) {
        
        if ( s.find( p->label ) != s.end() ) return m[ p ];
        
        UndirectedGraphNode * p2 = nullptr;
        auto it = m.find( p );
        if ( it == m.end() ) {
            p2 = new UndirectedGraphNode( p->label );
            m.insert( std::make_pair( p, p2 ) );
        } else {
            p2 = it->second;
        }
        
        s.insert( p->label );
        for ( auto n : p->neighbors ) {
            UndirectedGraphNode * n2 = clone_graph_dfs_impl( n, s, m );
            p2->neighbors.push_back( n2 );
        }
        
        return p2;
    }
    
    /**
     * DFS implementation without using a std::set< int >
     */
    UndirectedGraphNode * clone_graph_dfs2( UndirectedGraphNode * node ) {
        if ( node == nullptr ) return node;
        
        std::map< UndirectedGraphNode *, UndirectedGraphNode * > m;
        UndirectedGraphNode * node2 = new UndirectedGraphNode( node->label );
        m.insert( std::make_pair( node, node2 ) );
        return clone_graph_dfs_impl2( node, m );
    }
    UndirectedGraphNode * clone_graph_dfs_impl2(
            UndirectedGraphNode                                      * p,
            std::map< UndirectedGraphNode *, UndirectedGraphNode * > & m ) {
        UndirectedGraphNode * p2 = m[ p ];
        for ( auto n : p->neighbors ) {
            UndirectedGraphNode * n2 = nullptr;
            auto it = m.find( n );
            if ( it == m.end() ) {
                n2 = new UndirectedGraphNode( n->label );
                m.insert( std::make_pair( n, n2 ) );
                clone_graph_dfs_impl2( n, m );
            } else {
                n2 = it->second;
            }
            p2->neighbors.push_back( n2 );
        }
        return p2;
    }
    
    /**
     * BFS implementation
     * actually queue can be replaced with stack but it is still BFS
     */
    UndirectedGraphNode * clone_graph_bfs( UndirectedGraphNode * node ) {
        if ( node == nullptr ) return node;
        
        //no need to have a set< int > to mark the status of visiting node
        //this map is sufficient to decide if a node should be enqueued or not
        std::map< UndirectedGraphNode *, UndirectedGraphNode * > m;
        std::queue< UndirectedGraphNode * > q;
        q.push( node );
        UndirectedGraphNode * node2 = new UndirectedGraphNode( node->label );
        m.insert( std::make_pair( node, node2 ) );
        while ( ! q.empty() ) {
            UndirectedGraphNode * p = q.front();
            UndirectedGraphNode * p2 = m[ p ];
            q.pop();
            for ( auto n : p->neighbors ) {
                UndirectedGraphNode * n2 = nullptr;
                auto it = m.find( n );
                if ( it == m.end() ) {
                    n2 = new UndirectedGraphNode( n->label );
                    m.insert( std::make_pair( n, n2 ) );
                    q.push( n );
                } else {
                    n2 = it->second;
                }
                p2->neighbors.push_back( n2 );
            }
        }
        return node2;
    }
};
