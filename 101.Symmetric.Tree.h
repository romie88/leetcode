/**
 * Algorithms 101 Symmetric Tree                                           Easy
 *
 * Given a binary tree, check whether it is a mirror of itself (ie, symmetric
 * around its center).
 *
 * For example, this binary tree is symmetric:
 *
 *     1
 *    / \
 *   2   2
 *  / \ / \
 * 3  4 4  3
 *
 * But the following is not:
 *
 *     1
 *    / \
 *   2   2
 *    \   \
 *    3    3
 *
 * Note:
 * Bonus points if you could solve it both recursively and iteratively.
 *
 * confused what "{1,#,2,3}" means? > read more on how binary tree is
 * serialized on OJ.
 *
 * OJ's Binary Tree Serialization:
 * The serialization of a binary tree follows a level order traversal, where
 * '#' signifies a path terminator where no node exists below.
 *
 * Here's an example:
 *
 *    1
 *   / \
 *  2   3
 *     /
 *    4
 *     \
 *      5
 *
 * The above binary tree is serialized as "{1,2,3,#,#,4,#,#,5}".
 *
 * Tags: Array, Depth-first Search
 */

#include <stack>
#include <queue>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSymmetric( TreeNode * root ) {
        return is_symmetric_iterative_bfs2( root );
    }
private:
    /**
     * O( n ) runtime, O( n ) space - recursive preorder DFS
     */
    bool is_symmetric_recursive( TreeNode * root1, TreeNode * root2 ) {
        if ( root1 == nullptr && root2 == nullptr ) return true;
        if ( root1 == nullptr || root2 == nullptr ) return false;
        if ( root1->val != root2->val ) return false;
        return is_symmetric_recursive( root1->left, root2->right )
            && is_symmetric_recursive( root1->right, root2->left );
    }
    bool is_symmetric_recursive_wrapper( TreeNode * root ) {
        return root == nullptr
            || is_symmetric_recursive( root->left, root->right );
    }

    /**
     * O( n ) runtime, O( n ) space - iterative preorder DFS
     */
    bool is_symmetric_iterative_dfs( TreeNode * root ) {
        std::stack< TreeNode * > s1;
        std::stack< TreeNode * > s2;
        if ( root == nullptr ) return true;
        s1.push( root );
        s2.push( root );
        while ( ! s1.empty() && ! s2.empty() ) {
            TreeNode * p1 = s1.top();
            s1.pop();
            TreeNode * p2 = s2.top();
            s2.pop();
            if ( p1->val != p2->val ) return false;
            if ( p1->left != nullptr && p2->right == nullptr
              || p1->left == nullptr && p2->right != nullptr )
                return false;
            if ( p1->right != nullptr && p2->left == nullptr
              || p1->right == nullptr && p2->left != nullptr )
                return false;
            if ( p1->right ) s1.push( p1->right );
            if ( p1->left ) s1.push( p1->left );
            if ( p2->left ) s2.push( p2->left );
            if ( p2->right ) s2.push( p2->right );
        }
        return s1.empty() && s2.empty();
    }

    /**
     * O( n ) runtime, O( n ) space - queue based BFS
     *
     * Only not-nullptr TreeNode pointers are enqueued.
     */
    bool is_symmetric_iterative_bfs1( TreeNode * root ) {
        if ( root == nullptr ) return true;
        std::queue< TreeNode * > q1;
        std::queue< TreeNode * > q2;
        if ( root->left == nullptr && root->right == nullptr )
            return true;
        if ( root->left == nullptr && root->right != nullptr
          || root->left != nullptr && root->right == nullptr )
            return false;

        q1.push( root->left );
        q2.push( root->right );
        while ( ! q1.empty() && ! q2.empty() ) {
            TreeNode * p1 = q1.front();
            TreeNode * p2 = q2.front();
            q1.pop();
            q2.pop();

            if ( p1->val != p2->val ) return false;
            if ( p1->left == nullptr && p2->right != nullptr
              || p1->left != nullptr && p2->right == nullptr )
                return false;
            if ( p1->left != nullptr && p2->right != nullptr ) {
                q1.push( p1->left );
                q2.push( p2->right );
            }

            if ( p1->right == nullptr && p2->left != nullptr
              || p1->right != nullptr && p2->left == nullptr )
                return false;
            if ( p1->right != nullptr && p2->left != nullptr ) {
                q1.push( p1->right );
                q2.push( p2->left );
            }
        }
        return true;
    }

    /**
     * O( n ) runtime, O( n ) space - queue based BFS
     *
     * All TreeNode pointers are enqueued
     */
    bool is_symmetric_iterative_bfs2( TreeNode * root ) {
        if ( root == nullptr ) return true;
        std::queue< TreeNode * > q1;
        std::queue< TreeNode * > q2;
        q1.push( root->left );
        q2.push( root->right );
        while ( ! q1.empty() && ! q2.empty() ) {
            TreeNode * p1 = q1.front();
            TreeNode * p2 = q2.front();
            q1.pop();
            q2.pop();
            if ( p1 == nullptr && p2 != nullptr
              || p1 != nullptr && p2 == nullptr )
                return false;
            if ( p1 == nullptr && p2 == nullptr )
                continue;
            if ( p1->val != p2->val )
                return false;
            q1.push( p1->left );
            q1.push( p1->right );
            q2.push( p2->right );
            q2.push( p2->left );
        }
        return true;
    }
};