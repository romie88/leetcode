#include "Find.Minimum.in.Rotated.Sorted.Array.cpp"

#include <iostream>

int main()
{
	Solution s;

    int arr1[] =  {5, 6, 1, 2, 3, 4};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);
	std::vector< int > v1( arr1, arr1 + n1 );
	std::cout << "The minimum element is " << s.findMin( v1 ) << std::endl;
 
    int arr2[] =  {1, 1, 0, 1};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
	std::vector< int > v2( arr2, arr2 + n2 );
	std::cout << "The minimum element is " << s.findMin( v2 ) << std::endl;
 
    int arr3[] =  {1, 1, 2, 2, 3};
    int n3 = sizeof(arr3)/sizeof(arr3[0]);
	std::vector< int > v3( arr3, arr3 + n3 );
	std::cout << "The minimum element is " << s.findMin( v3 ) << std::endl;
 
    int arr4[] =  {3, 3, 3, 4, 4, 4, 4, 5, 3, 3};
    int n4 = sizeof(arr4)/sizeof(arr4[0]);
	std::vector< int > v4( arr4, arr4 + n4 );
	std::cout << "The minimum element is " << s.findMin( v4 ) << std::endl;
 
    int arr5[] =  {2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 1, 2};
    int n5 = sizeof(arr5)/sizeof(arr5[0]);
	std::vector< int > v5( arr5, arr5 + n5 );
	std::cout << "The minimum element is " << s.findMin( v5 ) << std::endl;
 
    int arr6[] =  {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1};
    int n6 = sizeof(arr6)/sizeof(arr6[0]);
	std::vector< int > v6( arr6, arr6 + n6 );
	std::cout << "The minimum element is " << s.findMin( v6 ) << std::endl;
 
    int arr7[] =  {2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2};
    int n7 = sizeof(arr7)/sizeof(arr7[0]);
	std::vector< int > v7( arr7, arr7 + n7 );
	std::cout << "The minimum element is " << s.findMin( v7 ) << std::endl;
 
    return 0;
}

