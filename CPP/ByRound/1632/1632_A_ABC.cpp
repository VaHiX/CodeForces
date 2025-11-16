// Problem: CF 1632 A - ABC
// https://codeforces.com/contest/1632/problem/A

/*
 * Problem: Reorder a binary string such that no substring of length > 1 is a palindrome.
 *
 * Algorithm:
 * - For a string to avoid palindromes of length > 1, it must be arranged so that no two adjacent characters are same,
 *   and also no three characters form a palindrome (like "000" or "111").
 * - If n == 1, always YES.
 * - If n == 2, only "00" and "11" will have palindromic substrings of length 2, so if the string is not "00" or "11", YES.
 * - For n > 2:
 *   - If there are more than one distinct character, we can rearrange to avoid palindromes (e.g., alternate 0s and 1s).
 *   - But if all characters are same (i.e., string is "000...0" or "111...1"), it's impossible to reorder for no palindrome.
 *
 * Time Complexity: O(n) per test case, where n is the string length. We read and process once.
 * Space Complexity: O(1) - only using constant extra space (variables).
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Optimize I/O speed
  long t;
  std::cin >> t; // Read number of test cases
  while (t--) {
    long n;
    std::cin >> n; // Read length of string
    std::string s;
    std::cin >> s; // Read the binary string
    // Check if it's impossible to reorder without palindromes:
    // - If n > 2, we can always rearrange (as long as not all same)
    // - If n == 2, only "00" or "11" cause issues (can't be reordered)
    bool res = (n > 2) || (s == "00") || (s == "11");
    std::cout << (res ? "NO" : "YES") << std::endl; // Output result
  }
}


// https://github.com/VaHiX/codeForces/