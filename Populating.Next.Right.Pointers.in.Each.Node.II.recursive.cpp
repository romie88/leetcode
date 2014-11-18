//Populating Next Right Pointers in Each Node II 2012-10-28
//
//Follow up for problem "Populating Next Right Pointers in Each Node".
//
//What if the given tree could be any binary tree? Would your previous
//solution still work?
//
//Note:
//
//You may only use constant extra space.
//
//For example,
//Given the following binary tree,
//         1
//       /  \
//      2    3
//     / \    \
//    4   5    7
//After calling your function, the tree should look like:
//         1 -> NULL
//       /  \
//      2 -> 3 -> NULL
//     / \    \
//    4-> 5 -> 7 -> NULL

//Tags: Tree, Depth-first Search

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
        
        //find the first child starting from parent root->next
        TreeLinkNode * p = root->next;
        TreeLinkNode * next_child = 0;
        while ( p )
        {
            if ( p->left )
            {
                next_child = p->left;
                break;
            }

            if ( p->right )
            {
                next_child = p->right;
                break;
            }
            
            p = p->next;
        }
            
        if ( root->right )
            root->right->next = next_child;
        if ( root->left )
            root->left->next = root->right ? root->right : next_child;

        connect( root->right );
        connect( root->left );
    }
};
