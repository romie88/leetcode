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
        
        TreeLinkNode * parent = root;
        while ( parent )
        {
            TreeLinkNode * p = parent;
            TreeLinkNode * child = 0;
            find_next_child( p, child );
            TreeLinkNode * first_child = child;
            while ( child )
            {
                TreeLinkNode * next_child = child;
                find_next_child( p, next_child );
                child->next = next_child;
                child = next_child;
            }
            
            parent = first_child;
        }
    }
private:
    void find_next_child( TreeLinkNode * & p,
                          TreeLinkNode * & next_child )
    {
        while ( p )
        {
            if ( p->left && next_child != p->left )
            {
                next_child = p->left;
                return;
            }
            else if ( p->right && next_child != p->right )
            {
                next_child = p->right;
                p = p->next;
                return;
            }
            else
            {
                p = p->next;
            }
        }
        next_child = 0;
    }
};
