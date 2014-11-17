#include <cstddef>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

#include "Binary.Tree.Maximum.Path.Sum.cpp"
#include <iostream>

int main()
{
    TreeNode n1( -2 );
    TreeNode n2( 1 );
    //TreeNode n3( 3 );
    n1.left  = &n2;
    //n1.right = &n3;
    
    Solution sln;
    std::cout << sln.maxPathSum( &n1 ) << std::endl;

    return 0;
}

