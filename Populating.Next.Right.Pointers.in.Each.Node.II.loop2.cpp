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
        
        TreeLinkNode * p = root;
        while ( p )
        {
            TreeLinkNode * prev_child = 0;
            TreeLinkNode * first_child = 0;
            while ( p )
            {
                if ( ! first_child )
                {
                    first_child = p->left ? p->left : p->right;
                }

                if ( p->left )
                {
                    if ( prev_child )
                        prev_child->next = p->left;

                    prev_child = p->left;
                }

                if ( p->right )
                {
                    if ( prev_child )
                        prev_child->next = p->right;

                    prev_child = p->right;
                }

                p = p->next;
            }
            
            p = first_child;
        }
    }
};
