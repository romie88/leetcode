/**
 * Algorithms 104 Maximum Depth of Binary Tree                             Easy
 *
 * Given a binary tree, find its maximum depth.
 *
 * The maximum depth is the number of nodes along the longest path from the
 * root node down to the farthest leaf node.
 *
 * Tags: Tree, Depth-first Search
 * Similar Problems: (E) Balanced Binary Tree, (E) Minimum Depth of Binary Tree
 */

#include <algorithm>
#include <stack>
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
    int maxDepth( TreeNode * root ) {
        max_depth_iterative_postorder_traversal_2( root );
    }
private:
    /**
     * O( n ) runtime, O( n ) space - straightforward recursive solution
     */
    int max_depth_recursive( TreeNode * root ) {
        if ( root == nullptr ) return 0;
        return 1 + std::max( max_depth_recursive( root->left ),
                             max_depth_recursive( root->right ) );
    }

    /**
     * O( n ) runtime, O( n ) space - level order traversal
     */
    int max_depth_level_order_traversal( TreeNode * root ) {
        if ( root == nullptr ) return 0;
        std::queue< TreeNode * > q;
        q.push( root );
        int count = 1;
        int count2 = 0;
        int depth = 0;
        while ( ! q.empty() ) {
            TreeNode * p = q.front();
            q.pop();
            if ( p->left  ) { q.push( p->left  ); ++count2; }
            if ( p->right ) { q.push( p->right ); ++count2; }
            --count;
            if ( count == 0 ) {
                ++depth;
                count = count2;
                count2 = 0;
            }
        }
        return depth;
    }

    /**
     * O( n ) runtime, O( n ) space - iterative preorder traversal
     *
     * This requires the tracking of the depth with the TreeNode pointer.
     */
    int max_depth_iterative_preorder_traversal( TreeNode * root ) {
        if ( root == nullptr ) return 0;
        std::stack< std::pair< TreeNode *, int > > s;
        s.push( std::make_pair( root, 1 ) );
        int max_depth = 0;
        while ( ! s.empty() ) {
            TreeNode * p = s.top().first;
            int        d = s.top().second;
            s.pop();
            if ( d > max_depth ) max_depth = d;
            if ( p->left  ) s.push( std::make_pair( p->left, 1 + d ) );
            if ( p->right ) s.push( std::make_pair( p->right, 1 + d ) );
        }
        return max_depth;
    }

    /**
     * O( n ) runtime, O( n ) space - iterative postorder traversal
     */
    int max_depth_iterative_postorder_traversal( TreeNode * root ) {
        std::stack< TreeNode * > s;
        TreeNode * p    = root;
        TreeNode * prev = nullptr;
        int        max_depth = 0;
        while ( p || ! s.empty() ) {
            if ( p ) {
                s.push( p );
                if ( s.size() > max_depth )
                    max_depth = s.size();
                p = p->left;
            } else {
                p = s.top();
                if ( p->right == nullptr || p->right == prev ) {
                    //visit p
                    s.pop();
                    prev = p;
                    p = nullptr;
                } else {
                    p = p->right;
                }
            }
        }
        return max_depth;
    }

    /**
     * O( n ) runtime, O( n ) space - another iterative postorder traversal
     */
    int max_depth_iterative_postorder_traversal_2( TreeNode * root ) {
        if ( root == nullptr ) return 0;
        std::stack< TreeNode * > s;
        s.push( root );
        int max_depth = 0;
        TreeNode * prev = nullptr;
        while ( ! s.empty() ) {
            TreeNode * curr = s.top();
            if ( prev == nullptr || prev->left == curr || prev->right == curr ) {
                if ( curr->left )
                    s.push( curr->left );
                else if ( curr->right )
                    s.push( curr->right );
            } else if ( curr->left == prev ) {
                if ( curr->right )
                    s.push( curr->right );
            } else {
                s.pop();
            }
            prev = curr;
            if ( s.size() > max_depth )
                max_depth = s.size();
        }
        return max_depth;
    }
};

