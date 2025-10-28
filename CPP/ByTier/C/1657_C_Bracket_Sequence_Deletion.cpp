// Problem: CF 1657 C - Bracket Sequence Deletion
// https://codeforces.com/contest/1657/problem/C

/*
C. Bracket Sequence Deletion
Algorithm: Greedy approach with prefix matching
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(n) for storing the string and temporary variables

The algorithm processes the input string from left to right, trying to find 
the shortest "good" prefix at each step. A prefix is good if:
1. It forms a valid bracket sequence (e.g., "()()"), or
2. It is a palindrome of length >= 2 (e.g., "((", "))")

We use a greedy approach: for each position, we extend the current prefix 
and check if it's good. If so, we increment operation count and reset the prefix.

This greedy strategy works because:
- We always pick the shortest possible good prefix
- This ensures maximum number of operations
- We process each character only once in total
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long cnt(0), rem(n);
    std::string cur(""); // Current prefix being checked
    for (long p = 0; p < n; p++) {
      cur += s[p]; // Extend the current prefix with next character
      // Check if current prefix is good:
      // 1. It's a valid bracket sequence, or
      // 2. It's a palindrome of length >= 2
      if (cur == "()" || (cur.size() > 1 && cur.back() == cur[0])) {
        ++cnt;         // Increment operation count
        rem -= cur.size(); // Reduce remaining characters
        cur = "";      // Reset current prefix
      }
    }
    std::cout << cnt << " " << rem << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/