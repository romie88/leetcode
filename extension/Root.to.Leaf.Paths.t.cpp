#include <cstddef>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

#include "Root.to.Leaf.Paths.cpp"
#include <iostream>

void print_paths( const std::vector< std::vector< int > > & paths )
{
    for ( const auto & p : paths )
    {
        for ( const auto & n : p )
            std::cout << n << ", ";
        std::cout << std::endl;
    }
}

int main()
{
    //construct a test tree
    //     1
    //    / \
    //   2   3
    //    \   \
    //     4   5
    //    / \
    //   6   7
    TreeNode n1( 1 );
    TreeNode n2( 2 );
    TreeNode n3( 3 );
    TreeNode n4( 4 );
    TreeNode n5( 5 );
    TreeNode n6( 6 );
    TreeNode n7( 7 );

    n1.left  = &n2;
    n1.right = &n3;
    n2.right = &n4;
    n3.right = &n5;
    n4.left  = &n6;
    n4.right = &n7;

    std::vector< std::vector< int > > paths;
    Solution sln;
    sln.rootToLeafPaths( &n1, paths );

    print_paths( paths );

    return 0;
}
