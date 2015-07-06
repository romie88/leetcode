/**
 * Algorithms 9 Palindrome Number                                          Easy
 * 
 * Determine whether an integer is a palindrome.
 * 
 * Do this without extra space.
 * 
 * click to show spoilers.
 * 
 * Some hints:
 * Could negative integers be palindromes? (ie, -1)
 * 
 * If you are thinking of converting the integer to string,
 * note the restriction of using extra space.
 * 
 * You could also try reversing an integer. However, if you have
 * solved the problem "Reverse Integer", you know that the reversed
 * integer might overflow. How would you handle such case?
 * 
 * There is a more generic way of solving this problem.
 * 
 * Tags: Math
 */

class Solution {
public:
    bool isPalindrome( int x ) {
		
		//add this logic because it seems OJ decides all negative numbers
		//are NOT palindrome numbers
		if ( x < 0 ) return false;
		
        int p = 1;
        int x2 = x;
        while ( x2 ) {
            p *= 10;
            x2 /= 10;
        }
        if ( x ) p /= 10;
        
        while ( p != 1 ) {
            if ( x / p != x % 10 ) return false;
            x %= p;
            x /= 10;
            p /= 100;
        }
        return true;
    }
private:
    /**
     * A better implementation from CleanCodeHandbook
     */
    bool is_palindrome_impl( int x ) {
        if ( x < 0 ) return false;
        int div = 1;
        while ( x / div >= 10 ) div *= 10;
        while ( x ) {
            if ( x / div != x % div ) return false;
            x = ( x % div ) / 10;
            div /= 100;
        }
        return true;
    }
};
