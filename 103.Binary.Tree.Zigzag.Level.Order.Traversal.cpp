//103 Binary Tree Zigzag Level Order Traversal [ Medium ]
//
//Given a binary tree, return the zigzag level order traversal of its nodes'
//values. (ie, from left to right, then right to left for the next level and
//alternate between).
//
//For example:
//Given binary tree {3,9,20,#,#,15,7},
//    3
//   / \
//  9  20
//    /  \
//   15   7
//return its zigzag level order traversal as:
//[
//  [3],
//  [20,9],
//  [15,7]
//]
//confused what "{1,#,2,3}" means? > read more on how binary tree is
//serialized on OJ.
//
//OJ's Binary Tree Serialization:
//The serialization of a binary tree follows a level order traversal, where
//'#' signifies a path terminator where no node exists below.
//
//Here's an example:
//   1
//  / \
// 2   3
//    /
//   4
//    \
//     5
//The above binary tree is serialized as "{1,2,3,#,#,4,#,#,5}".

//Tags: Tree, Breath-first Search, Stack

#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

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
    std::vector< std::vector< int > > zigzagLevelOrder( TreeNode * root ) {

        std::vector< std::vector< int > > levels;
        zigzag_level_order_queue( root, levels );
        return levels;
    }

private:
    
    //Use a queue. To seperate the levels, use nullptr as the end indicator
    //of one level.
    void zigzag_level_order_queue(
            TreeNode * root,
            std::vector< std::vector< int > > & levels ) {
        
        if ( ! root ) return;
        
        bool left_to_right = true;
        std::queue< TreeNode * > q;
        q.push( root );
        q.push( nullptr );
        std::vector< int > one_level;
        while ( ! q.empty() ) {
            TreeNode * p = q.front();
            q.pop();
            if ( p ) {
                one_level.push_back( p->val );
                if ( p->left ) q.push( p->left );
                if ( p->right ) q.push( p->right );
            } else {
                if ( ! left_to_right ) {
                    std::reverse( one_level.begin(), one_level.end() );
                }
                left_to_right = ! left_to_right;
                levels.push_back( one_level );
                one_level.clear();
                if ( ! q.empty() ) {
                    q.push( nullptr );
                }
            }
        }
    }
    
    //DFS
    void zigzag_level_order_DFS(
            TreeNode * root,
            std::vector< std::vector< int > > & levels ) {
        level_order_DFS_impl( root, levels, 0 );
        for ( std::vector< std::vector< int > >::size_type i = 1;
              i < levels.size(); i += 2 ) {
            std::reverse( levels[ i ].begin(), levels[ i ].end() );
        }
    }

    void level_order_DFS_impl( TreeNode * root,
                               std::vector< std::vector< int > > & levels,
                               int level ) {
        if ( ! root ) return;
        if ( levels.size() <= level ) levels.push_back( std::vector< int >() );
        levels[ level ].push_back( root->val );
        level_order_DFS_impl( root->left, levels, level + 1 );
        level_order_DFS_impl( root->right, levels, level + 1 );
    }
    
    //Annie Kim github
    void zigzag_level_order_two_stacks(
            TreeNode * root,
            std::vector< std::vector< int > > & levels ) {
        
        if ( ! root ) return;
        
        bool left_to_right = true;
        std::stack< TreeNode * > s[ 2 ];
        int last = 0;
        int curr = 1;

        s[ last ].push( root );
        std::vector< int > one_level;
        while ( ! s[ last ].empty() ) {
            TreeNode * p = s[ last ].top();
            s[ last ].pop();
            if ( p ) {
                one_level.push_back( p->val );
                if ( left_to_right ) {
                    if ( p->left )  s[ curr ].push( p->left );
                    if ( p->right ) s[ curr ].push( p->right );
                } else {
                    if ( p->right ) s[ curr ].push( p->right );
                    if ( p->left )  s[ curr ].push( p->left );
                }
            }
            if ( s[ last ].empty() ) {
                left_to_right = ! left_to_right;
                levels.push_back( one_level );
                one_level.clear();
                std::swap( last, curr );
            }
        }
    }
};
