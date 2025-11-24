// Problem: CF 932 A - Palindromic Supersequence
// https://codeforces.com/contest/932/problem/A

/*
 * Problem: Palindromic Supersequence
 * Algorithm: Greedy Construction
 * Approach: 
 *   - Take the given string s
 *   - Append the reverse of s to it
 *   - This ensures the result is a palindrome and contains s as a subsequence
 * 
 * Time Complexity: O(n), where n is the length of string s
 * Space Complexity: O(n), for storing the result string
 * 
 * The constructed string is always a palindrome because:
 *   - s + reverse(s) is symmetric
 *   - s is a subsequence of s + reverse(s) as it appears in the first half
 * 
 * Example:
 *   Input: "ab" -> Output: "aba" (not correct, but the code outputs "abba")
 *   The code outputs s + reverse(s) which is always a palindrome.
 *   For "ab", the output is "abba", which is a palindrome and contains "ab" as subsequence.
 * 
 * Note: This is a simple solution, not necessarily minimal.
 * The length of output will never exceed 2 * |s|, which is acceptable (<= 10^4).
 */

#include <algorithm>
#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  std::cout << s;  // Print original string
  std::reverse(s.begin(), s.end());  // Reverse the string
  std::cout << s << std::endl;  // Print reversed string
  return 0;
}


// https://github.com/VaHiX/CodeForces/