//107 Binary Tree Level Order Traversal II [ Easy ]
//
//Given a binary tree, return the bottom-up level order traversal of its
//nodes' values. (ie, from left to right, level by level from leaf to root).
//
//For example:
//Given binary tree {3,9,20,#,#,15,7},
//    3
//   / \
//  9  20
//    /  \
//   15   7
//return its bottom-up level order traversal as:
//[
//  [15,7],
//  [9,20],
//  [3]
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

//Tags: Tree, Breath-first Search

#include <vector>
#include <algorithm>

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
    std::vector< std::vector< int > > levelOrderBottom( TreeNode * root ) {

        std::vector< std::vector< int > > levels;
        level_order_bottom_queue( root, levels );
        return levels;
    }
    
private:
    
    //Use a queue. To seperate the levels, use nullptr as the end indicator
    //of one level.
    void level_order_bottom_queue(
            TreeNode * root,
            std::vector< std::vector< int > > & levels ) {

        if ( ! root ) return;

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
                levels.push_back( one_level );
                one_level.clear();
                if ( ! q.empty() ) {
                    q.push( nullptr );
                }
            }
        }

        std::reverse( levels.begin(), levels.end() );
    }
};

