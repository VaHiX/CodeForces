// Problem: CF 1704 A - Two 0-1 Sequences
// https://codeforces.com/contest/1704/problem/A

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::string a, b;
    std::cin >> a >> b;
    long lag = n - m;
    bool ans(true);
    // Check if the suffix of 'a' matches 'b' from index 1 onwards
    for (long p = 1; ans && p < m; p++) {
      if (b[p] != a[lag + p]) {
        ans = false;
      }
    }
    // If suffix matches, check if the prefix of 'a' can be adjusted to match b[0]
    if (ans && a[lag] != b[0]) {
      ans = false;
      // Look for b[0] in the prefix of 'a' to see if it's reachable
      for (long p = 0; p < lag; p++) {
        if (a[p] == b[0]) {
          ans = true;
          break;
        }
      }
    }
    std::cout << (ans ? "YES" : "NO") << std::endl;
  }
}
/*
Flowerbox:
Code purpose: Determines whether a binary sequence 'a' can be transformed into another binary sequence 'b' using two specific operations:
Operation 1: Change a[1] to min(a[0], a[1]) and remove the first element.
Operation 2: Change a[1] to max(a[0], a[1]) and remove the first element.

Algorithms/Techniques:
- String matching and prefix/suffix comparison
- Greedy approach with checks on reachable elements

Time Complexity: O(n * m) per test case, where n and m are the lengths of sequences a and b respectively.
Space Complexity: O(1) excluding input storage.

This is because for each test case we perform linear comparisons and iterations over parts of strings.
*/

// https://github.com/VaHiX/codeForces/