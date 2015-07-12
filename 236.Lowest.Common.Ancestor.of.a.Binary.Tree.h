/**
 * Algorithms 236 Lowest Common Ancestor of a Binary Tree                Meidum
 * 
 * Given a binary tree, find the lowest common ancestor (LCA) of two given
 * nodes in the tree.
 * 
 * According to the definition of LCA on Wikipedia: "The lowest common ancestor
 * is defined between two nodes v and w as the lowest node in T that has both v
 * and w as descendants (where we allow a node to be a descendant of itself)."
 * 
 *        _______3______
 *       /              \
 *    ___5__          ___1__
 *   /      \        /      \
 *   6      _2       0       8
 *         /  \
 *         7   4
 * 
 * For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another
 * example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of
 * itself according to the LCA definition.
 * 
 * Tags: Tree
 * Similar Problems: (E) Lowest Common Ancestor of a Binary Search Tree
 */

#include <stdexcept>
#include <vector>

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
    TreeNode * lowestCommonAncestor( TreeNode * root, TreeNode * p, TreeNode * q ) {
        return lowest_common_ancestor_2( root, p, q );
    }
private:
    /**
     * O( n ) runtime, O( n ) space worst case, O( lg n ) space average case
     */
    TreeNode * lowest_common_ancestor(
            TreeNode * root, TreeNode * p, TreeNode * q ) {
        std::vector< TreeNode * > path1;
        std::vector< TreeNode * > path2;
        
        if ( ! find_path( root, p, path1 ) )
            throw std::invalid_argument( "p is not in the tree" );
        if ( ! find_path( root, q, path2 ) )
            throw std::invalid_argument( "q is not in the tree" );
        
        int i = 0;
        for ( ; i < path1.size() && i < path2.size(); ++i ) {
            if ( path1[ i ] != path2[ i ] ) break;
        }
        return path1[ i - 1 ];
    }
    bool find_path( TreeNode * root, TreeNode * p,
                    std::vector< TreeNode * > & path ) {
        if ( root == nullptr ) return false;
        path.push_back( root );
        if ( root == p )       return true;
        if ( find_path( root->left, p, path ) ) return true;
        if ( find_path( root->right, p, path ) ) return true;
        path.pop_back();
        return false;
    }
    /**
     * O( n ) runtime - a way much better implementation from leetcode articles
     */
    TreeNode * lowest_common_ancestor_2(
            TreeNode * root, TreeNode * p, TreeNode * q ) {
        if ( root == nullptr ) return nullptr;
        if ( root == p || root == q ) return root;
        TreeNode * left  = lowest_common_ancestor_2( root->left,  p, q );
        TreeNode * right = lowest_common_ancestor_2( root->right, p, q );
        if ( left && right ) return root;
        return left ? left : right;
    }
};
