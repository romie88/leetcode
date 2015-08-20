/**
 * Algorithms 98 Validate Binary Search Tree                             Medium
 *
 * Given a binary tree, determine if it is a valid binary search tree (BST).
 *
 * Assume a BST is defined as follows:
 *
 * * The left subtree of a node contains only nodes with keys less than the
 *   node's key.
 * * The right subtree of a node contains only nodes with keys greater than the
 *   node's key.
 * * Both the left and right subtrees must also be binary search trees.
 *
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
 *     5
 * The above binary tree is serialized as "{1,2,3,#,#,4,#,#,5}".
 *
 * Tags: Tree, Depth-first Search
 * Similar Problems: (M) Binary Tree Inorder Traversal
 */

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
    bool isValidBST( const TreeNode * root ) {
        return is_valid_BST_inorder( root );
    }
private:
    /**
     * O( n^2 ) runtime, O( n ) stack space - Brute force
     * The worst case runtime complexity is O( n^2 ) when the tree
     * degenerates into a linked list with n nodes.
     */
    bool is_valid_BST_bf( TreeNode * root ) {
        if ( root == nullptr ) return true;
        return is_subtree_less_than( root->left, root->val )
            && is_subtree_greater_than( root->right, root->val )
            && is_valid_BST_bf( root->left )
            && is_valid_BST_bf( root->right );
    }
    bool is_subtree_less_than( TreeNode * root, int val ) {
        if ( root == nullptr ) return true;
        return root->val < val
            && is_subtree_less_than( root->left, val )
            && is_subtree_less_than( root->right, val );
    }
    bool is_subtree_greater_than( TreeNode * root, int val ) {
        if ( root == nullptr ) return true;
        return root->val > val
            && is_subtree_greater_than( root->left, val )
            && is_subtree_greater_than( root->right, val );
    }

    /**
     * O( n ) runtime, O( n ) stack space - Top-down recursion
     * More general than using std::numeric_limits< int >::min() and max()
     */
    bool is_valid_BST_td( const TreeNode * root ) {
        return is_valid_BST_td_impl( root, false, false, 0, 0 );
    }
    bool is_valid_BST_td_impl( const TreeNode * root,
                               const bool has_lower_bound,
                               const bool has_upper_bound,
                               const int lower_bound,
                               const int upper_bound ) {
        if ( root == nullptr ) return true;
        return ( ! has_lower_bound || lower_bound < root->val )
            && ( ! has_upper_bound || root->val < upper_bound )
            && is_valid_BST_td_impl( root->left, has_lower_bound, true, lower_bound, root->val )
            && is_valid_BST_td_impl( root->right, true, has_upper_bound, root->val, upper_bound );
    }

    /**
     * O( n ) runtime, O( n ) stack space - In-order traversal
     */
    bool is_valid_BST_inorder( const TreeNode * root ) {
        const TreeNode * prev = nullptr;
        return is_valid_BST_inorder_impl( root, prev );
    }
    bool is_valid_BST_inorder_impl( const TreeNode * p, const TreeNode * & prev ) {
        if ( p == nullptr ) return true;
        if ( is_valid_BST_inorder_impl( p->left, prev ) ) {
            if ( prev != nullptr && prev->val >= p->val )
                return false;
            prev = p;
            return is_valid_BST_inorder_impl( p->right, prev );
        }
        return false;
    }
};
