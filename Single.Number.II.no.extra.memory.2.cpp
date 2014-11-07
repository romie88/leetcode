//Single Number II
//
//Given an array of integers, every element appears three times except for one.
//Find that single one.
//
//Note:
//
//Your algorithm should have a linear runtime complexity.
//Could you implement it without using extra memory?

//Tags: Bit Manipulation

class Solution {
public:
    int singleNumber( int A[], int n ) {
		
		//Based on the idea of adding up the k-th bit of
		//all the numbers then mod 3 to get the k-th bit of
		//the result
		int ones = 0;//save the mod 3 == 1 on the k-th bit
		int twos = 0;//save the mod 3 == 2 on the k-th bit
		int threes = 0;//save the mod 3 == 0 on the k-th bit
		//think about this:
		//two bits a and b
		//a & b = ( a + b ) / 2
		//a ^ b = ( a + b ) % 2
		for ( int i = 0; i < n; ++i )
		{
			twos |= ones & A[ i ];
			ones ^= A[ i ];
			threes = ones & twos;
			ones &= ~threes;
			twos &= ~threes;
		}
		
		return ones;
    }
};
