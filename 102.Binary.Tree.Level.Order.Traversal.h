/**
 * Algorithms 102 Binary Tree Level Order Traversal                        Easy
 *
 * Given a binary tree, return the level order traversal of its nodes' values.
 * (ie, from left to right, level by level).
 *
 * For example:
 * Given binary tree {3,9,20,#,#,15,7},
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * return its level order traversal as:
 * [
 *   [3],
 *   [9,20],
 *   [15,7]
 * ]
 * confused what "{1,#,2,3}" means? > read more on how binary tree is
 * serialized on OJ.
 *
 * OJ's Binary Tree Serialization:
 * The serialization of a binary tree follows a level order traversal, where
 * '#' signifies a path terminator where no node exists below.
 *
 * Here's an example:
 *    1
 *   / \
 *  2   3
 *     /
 *    4
 *     \
 *      5
 * The above binary tree is serialized as "{1,2,3,#,#,4,#,#,5}".
 *
 * Tags: Tree, Breath-first Search
 * Similar Problems: (M) Binary Tree ZigZag Level Order Traversal,
 *                   (E) Binary Tree Level Order Traversal II
 *                   (E) Minimum Depth of Binary Tree
 */

#include <vector>
#include <queue>

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    std::vector< std::vector< int > > levelOrder( TreeNode * root ) {

        std::vector< std::vector< int > > levels;
        level_order_BFS_3( root, levels );
        return levels;
    }

private:

    /**
     * O( n ) runtime, O( n ) space - BFS by queue
     *
     * Use a queue. To seperate the levels, use nullptr as the end indicator
     * of one level.
     */
    void level_order_BFS_1( TreeNode                          * root,
                            std::vector< std::vector< int > > & levels ) {

        if ( ! root ) return;

        std::queue< TreeNode * > q;
        q.push( root );
        q.push( nullptr );//nullptr marks the end of a level
        std::vector< int > one_level;
        while ( ! q.empty() ) {
            TreeNode * p = q.front();
            q.pop();
            if ( p ) {
                one_level.push_back( p->val );
                if ( p->left ) q.push( p->left );
                if ( p->right ) q.push( p->right );
            } else {
                levels.push_back( one_level );
                one_level.clear();
                if ( ! q.empty() ) {//check to prevent the infinite loop
                    q.push( nullptr );
                }
            }
        }
    }

    /**
     * Another implementation of BFS by two containers and swapping them
     * level by level.
     */
    void level_order_BFS_2( TreeNode                          * root,
                            std::vector< std::vector< int > > & levels ) {

        if ( ! root ) return;

        std::vector< TreeNode * > curr_level;
        std::vector< TreeNode * > next_level;
        curr_level.push_back( root );
        std::vector< int > one_level;
        while ( ! curr_level.empty() ) {
            one_level.clear();
            for ( int i = 0; i < curr_level.size(); ++i ) {
                TreeNode * p = curr_level[ i ];
                one_level.push_back( p->val );
                if ( p->left  ) next_level.push_back( p->left );
                if ( p->right ) next_level.push_back( p->right );
            }
            levels.push_back( one_level );
            curr_level.swap( next_level );
            next_level.clear();
        }
    }

    /**
     * Yet another implementation of BFS by one queue and count.
     */
    void level_order_BFS_3( TreeNode                          * root,
                            std::vector< std::vector< int > > & levels ) {

        if ( ! root ) return;

        std::queue< TreeNode * > q;
        q.push( root );
        int curr_count = 1;
        int next_count = 0;
        std::vector< int > one_level;
        while ( ! q.empty() ) {
            TreeNode * p = q.front();
            q.pop();
            --curr_count;
            one_level.push_back( p->val );
            if ( p->left  ) { q.push( p->left  ); ++next_count; }
            if ( p->right ) { q.push( p->right ); ++next_count; }
            if ( curr_count == 0 ) {
                curr_count = next_count;
                next_count = 0;
                levels.push_back( one_level );
                one_level.clear();
            }
        }
    }

    /**
     * O( n ) runtime, O( n ) space - DFS by level
     */
    void level_order_DFS( TreeNode                          * root,
                          std::vector< std::vector< int > > & levels ) {
        level_order_DFS_impl( root, levels, 0 );
    }

    void level_order_DFS_impl( TreeNode                          * root,
                               std::vector< std::vector< int > > & levels,
                               int                                 level ) {
        if ( ! root ) return;
        if ( levels.size() <= level ) levels.push_back( std::vector< int >() );
        levels[ level ].push_back( root->val );
        level_order_DFS_impl( root->left, levels, level + 1 );
        level_order_DFS_impl( root->right, levels, level + 1 );
    }
};