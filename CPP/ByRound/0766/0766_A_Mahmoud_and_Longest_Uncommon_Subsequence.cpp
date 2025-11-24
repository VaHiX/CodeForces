// Problem: CF 766 A - Mahmoud and Longest Uncommon Subsequence
// https://codeforces.com/contest/766/problem/A

/*
 * Problem: Mahmoud and Longest Uncommon Subsequence
 * 
 * Purpose: Find the length of the longest subsequence that is present in one string
 *          but not in the other.
 * 
 * Algorithm/Technique:
 * - If the two strings are identical, then all subsequences of one are also
 *   subsequences of the other, so there is no uncommon subsequence. Return -1.
 * - If the two strings are different, then the longer string itself is a
 *   subsequence of itself but not of the shorter string (since they are different),
 *   so the length of the longer string is the answer.
 * 
 * Time Complexity: O(n), where n is the length of the shorter string (due to string comparison).
 * Space Complexity: O(1), no extra space used apart from input strings.
 */

#include <iostream>
#include <string>

int main() {
  std::string s, t;
  std::cin >> s >> t;
  if (s == t) {  // If strings are equal, no uncommon subsequence exists
    std::cout << "-1" << std::endl;
  } else {
    // Otherwise, the longer string's length is the answer
    std::cout << ((s.size() > t.size()) ? s.size() : t.size()) << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/