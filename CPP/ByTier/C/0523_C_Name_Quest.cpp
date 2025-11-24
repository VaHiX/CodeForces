// Problem: CF 523 C - Name Quest
// https://codeforces.com/contest/523/problem/C

/*
 * Problem: C. Name Quest
 * 
 * Algorithm/Techniques:
 * - Two-pass scanning to find the earliest and latest possible split points in string t
 *   such that the prefix up to split point and suffix starting from split point both
 *   contain the string s as a subsequence.
 * 
 * Time Complexity: O(n + m), where n is the length of s and m is the length of t
 * Space Complexity: O(1), only using a few variables for tracking
 * 
 * Approach:
 * - First pass from left to right: find the earliest position where s can be a subsequence
 *   of the prefix of t ending at that position.
 * - Second pass from right to left: find the latest position where s can be a subsequence
 *   of the suffix of t starting at that position.
 * - Count valid splits where left < right.
 */

#include <iostream>
#include <string>

int main() {
  std::string name;
  getline(std::cin, name);
  std::string target;
  getline(std::cin, target);
  long x = 0;
  long left(target.size());
  for (long p = 0; p < target.size(); p++) {
    if (name[x] == target[p]) {
      ++x;
    }
    if (x >= name.size()) {
      left = p;   // Mark the earliest position where s is a subsequence of prefix
      break;
    }
  }
  x = name.size() - 1;
  long right(-1);
  for (long p = target.size() - 1; p >= 0; p--) {
    if (name[x] == target[p]) {
      --x;
    }
    if (x < 0) {
      right = p;  // Mark the latest position where s is a subsequence of suffix
      break;
    }
  }
  std::cout << ((left < right) ? (right - left) : 0) << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/