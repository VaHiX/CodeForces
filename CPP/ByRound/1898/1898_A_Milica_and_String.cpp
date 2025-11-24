// Problem: CF 1898 A - Milica and String
// https://codeforces.com/contest/1898/problem/A

/*
Algorithm: Greedy approach to transform string to have exactly k instances of 'B'
Time Complexity: O(n) per test case, where n is the length of the string
Space Complexity: O(n) for storing the input string

The approach works by:
1. Counting the current number of 'B's in the string
2. If the count equals k, no operations needed
3. Otherwise, determine the minimum number of operations needed:
   - If we need more 'B's, we replace some 'A's with 'B's from left to right
   - If we need fewer 'B's, we replace some 'B's with 'A's from left to right
4. The minimum operation required is to make a single replacement of a prefix of the string
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    long b(0);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == 'B') {
        ++b;
      }
    }
    if (b == k) {
      std::cout << "0" << std::endl;
      continue;
    }
    // Determine the character to change and the number of changes needed
    char c = (b < k ? 'A' : 'B');  // Character that needs to be replaced
    char d = (b < k ? 'B' : 'A');  // Character to replace it with
    long cnt(b < k ? (k - b) : (b - k)), idx(0);
    // Find the index where we need to stop changing
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == c) {
        --cnt;
      }
      if (!cnt) {
        idx = p + 1;
        break;
      }
    }
    std::cout << "1\n" << idx << " " << d << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/