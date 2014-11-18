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

        if ( ! root )
            return;

        std::queue< TreeLinkNode * > q;
        q.push( root );
        q.push( 0 );
        while ( ! q.empty() )
        {
            TreeLinkNode * p = q.front();
            q.pop();
            if ( p )
            {
                p->next = q.front();
                
                if ( p->left )
                    q.push( p->left );
                if ( p->right )
                    q.push( p->right );
            }
            else
            {
                if ( ! q.empty() )
                    q.push( 0 );
            }
        }
    }
};
