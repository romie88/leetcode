//Populating Next Right Pointers in Each Node 2012-10-28
//
//Given a binary tree
//
//    struct TreeLinkNode {
//      TreeLinkNode *left;
//      TreeLinkNode *right;
//      TreeLinkNode *next;
//    }
//
//Populate each next pointer to point to its next right node.
//If there is no next right node, the next pointer should be set to NULL.
//
//Initially, all next pointers are set to NULL.
//
//Note:
//
//You may only use constant extra space.
//You may assume that it is a perfect binary tree (ie, all leaves are at
//the same level, and every parent has two children).
//
//For example,
//Given the following perfect binary tree,
//         1
//       /  \
//      2    3
//     / \  / \
//    4  5  6  7
//After calling your function, the tree should look like:
//         1 -> NULL
//       /  \
//      2 -> 3 -> NULL
//     / \  / \
//    4->5->6->7 -> NULL

//Tags: Tree, Depth-first Search

#include <queue>

/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect( TreeLinkNode * root ) {

        if ( ! root || ! root->left )
            return;
        
        TreeLinkNode * parent = root;
        TreeLinkNode * left_child = parent->left;
        while ( left_child )
        {
            TreeLinkNode * copy_left_child = left_child;
            
            while ( left_child )
            {
                left_child->next = parent->right;
                parent->right->next = parent->next
                                    ? parent->next->left
                                    : 0;

                left_child = parent->right->next;
                parent = parent->next;
            }

            parent = copy_left_child;
            left_child = parent->left;
        }
    }
};
