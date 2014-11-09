//Clone Graph
//
//Clone an undirected graph. Each node in the graph contains a label and
//a list of its neighbors.
//
//
//OJ's undirected graph serialization:
//
//Nodes are labeled uniquely.
//
//We use # as a separator for each node, and , as a separator for node
//label and each neighbor of the node.
//
//As an example, consider the serialized graph {0,1,2#1,2#2,2}.
//
//The graph has a total of three nodes, and therefore contains three parts
//as separated by #.
//
//1. First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
//2. Second node is labeled as 1. Connect node 1 to node 2.
//3. Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
//
//Visually, the graph looks like the following:
//
//       1
//      / \
//     /   \
//    0 --- 2
//         / \
//         \_/

//Tags: Depth-first Search, Breath-first Search, Graph

#include <queue>
#include <unordered_map>
#include <utility>
#include <set>

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
       	
		if ( ! node )
			return node;
		
		std::queue< UndirectedGraphNode * > node_queue;
		std::unordered_map< UndirectedGraphNode *, UndirectedGraphNode * >
			old_new_map;
		
		UndirectedGraphNode * node_copy = new UndirectedGraphNode( node->label );
		node_queue.push( node );
		old_new_map.insert( std::make_pair( node, node_copy ) );
		while ( ! node_queue.empty() )
		{
			//pair p - p_copy must be in old_new_map
			//it is guaranteed by the way how node_queue is populated
			UndirectedGraphNode * p = node_queue.front();
			UndirectedGraphNode * p_copy = old_new_map[ p ];
			node_queue.pop();
			for ( const auto & n : p->neighbors )
			{
				auto it = old_new_map.find( n );
				if ( it == old_new_map.end() )
				{
					node_queue.push( n );
					UndirectedGraphNode * n_copy
						= new UndirectedGraphNode( n->label );
					old_new_map.insert( std::make_pair( n, n_copy ) );
					p_copy->neighbors.push_back( n_copy );
				}
				else
				{
					p_copy->neighbors.push_back( it->second );
				}
			}
		}

		return node_copy;
    }
};
