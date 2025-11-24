// Problem: CF 1063 A - Oh Those Palindromes
// https://codeforces.com/contest/1063/problem/A

/*
 * Problem: A. Oh Those Palindromes
 * 
 * Purpose: 
 *   Given a string, rearrange its characters to maximize the palindromic count.
 *   The palindromic count is the number of substrings that are palindromes.
 *   
 * Algorithm:
 *   To maximize palindromic count, we can sort the characters.
 *   When characters are sorted, we are more likely to form palindromic substrings
 *   because similar characters are grouped together.
 *   
 *   The idea is based on the observation that a string with repeated characters
 *   forms more palindromic substrings than a randomly ordered string.
 *   
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(1) if we ignore the space used by the input string, 
 *                   otherwise O(n) for storing the string.
 * 
 * Techniques:
 *   - Sorting to optimize palindromic count
 *   - Greedy approach (sorting maximizes chances of palindrome substrings)
 */
#include <algorithm>
#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  sort(s.begin(), s.end());  // Sort characters to maximize palindromic count
  std::cout << s << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/