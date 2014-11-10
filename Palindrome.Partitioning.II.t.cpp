#include "Palindrome.Partitioning.II.cpp"
#include <iostream>

int main()
{
	std::string s( "apjesgpsxoeiokmqmfgvjslcjukbqxpsobyhjpbgdfruq"
			"dkeiszrlmtwgfxyfostpqczidfljwfbbrflkgdvtytbgqalguewn"
			"hvvmcgxboycffopmtmhtfizxkmeftcucxpobxmelmjtuzigsxnnc"
			"xpaibgpuijwhankxbplpyejxmrrjgeoevqozwdtgospohznkoyzo"
			"cjlracchjqnggbfeebmuvbicbvmpuleywrpzwsihivnrwtxcukwp"
			"lgtobhgxukwrdlszfaiqxwjvrgxnsveedxseeyeykarqnjrtlali"
			"yudpacctzizcftjlunlgnfwcqqxcqikocqffsjyurzwysfjmswvh"
			"brmshjuzsgpwyubtfbnwajuvrfhlccvfwhxfqthkcwhatktymgxo"
			"stjlztwdxritygbrbibdgkezvzajizxasjnrcjwzdfvdnwwqeyum"
			"kamhzoqhnqjfzwzbixclcxqrtniznemxeahfozp" );
//	std::string s( "aab" );
	std::cout << s.length() << std::endl;
	Solution sln;
	std::cout << sln.minCut( s ) << std::endl;
}
