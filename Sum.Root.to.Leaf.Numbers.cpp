//Sum Root to Leaf Numbers 2013-02-18
//
//Given a binary tree containing digits from 0-9 only, each root-to-leaf path
//could represent a number.
//
//An example is the root-to-leaf path 1->2->3 which represents the number 123.
//
//Find the total sum of all root-to-leaf numbers.
//
//For example,
//
//    1
//   / \
//  2   3
//The root-to-leaf path 1->2 represents the number 12.
//The root-to-leaf path 1->3 represents the number 13.
//
//Return the sum = 12 + 13 = 25.

//Tags: Tree, Depth-first Search

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
    int sumNumbers( TreeNode * root ) {
        int sum = 0;

        if ( ! root )
            return sum;

        sum_root_to_leaf_numbers( root, sum, 0 );
        
        return sum;
    }
private:
    void sum_root_to_leaf_numbers( TreeNode * p, int & sum, int one_path_num )
    {
        one_path_num = one_path_num * 10 + p->val;
        //p is a leaf
        if ( ! p->left && ! p->right )
        {
            sum += one_path_num;
            return;
        }

        if ( p->left )
            sum_root_to_leaf_numbers( p->left, sum, one_path_num );

        if ( p->right )
            sum_root_to_leaf_numbers( p->right, sum, one_path_num );
    }
};
