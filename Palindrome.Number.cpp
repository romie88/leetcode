//Palindrome Number
//
//Determine whether an integer is a palindrome.
//
//Do this without extra space.
//
//click to show spoilers.
//
//Some hints:
//Could negative integers be palindromes? (ie, -1)
//
//If you are thinking of converting the integer to string,
//note the restriction of using extra space.
//
//You could also try reversing an integer. However, if you have
//solved the problem "Reverse Integer", you know that the reversed
//integer might overflow. How would you handle such case?
//
//There is a more generic way of solving this problem.

class Solution {
public:
    bool isPalindrome(int x) {
		
		//add this logic because it seems OJ decides all negative numbers
		//are NOT palindrome numbers
		if ( x < 0 )
			return false;
		
        int n = x < 0 ? -x : x;//overflow if x == INT_MIN
		
		int d = 0;//number of digits of x
		while ( n )
		{
			n /= 10;
			++d;
		}

		int p = 1;//10^(d-1) if d > 0
		for ( int i = 1; i < d; ++i )
			p *= 10;
		
		bool is_palindrome = true;
		n = x < 0 ? -x : x;
		int n2 = n;
		for ( int i = 0; i < d / 2; ++i )
		{
			int high_d = n / p;
			n %= p;
			p /= 10;
			int low_d = n2 % 10;
			n2 /= 10;
			if ( high_d != low_d )
			{
				is_palindrome = false;
				break;
			}
		}

		return is_palindrome;
    }
};
