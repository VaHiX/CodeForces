// Problem: CF 1416 A - k-Amazing Numbers
// https://codeforces.com/contest/1416/problem/A

/*
 * Problem: A. k-Amazing Numbers
 * Algorithms/Techniques: Two-pointer technique, preprocessing, sliding window
 * Time Complexity: O(n) amortized per test case
 * Space Complexity: O(n)
 *
 * For each k from 1 to n, we compute the minimum element that appears in every subsegment of length k.
 * The approach uses a two-pass method:
 *   1. Preprocess the maximum gap between occurrences of each value.
 *   2. Use a sweep line technique to assign values to answer array.
 */

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--) {
    int n;
    std::cin >> n;
    std::vector<int> p(n, -1), k(n); // p: last seen position of each value; k: max gap for each value
    for (int i = 0; i < n; ++i) {
      int x;
      std::cin >> x;
      --x; // Convert to 0-based indexing
      k[x] = std::max(k[x], i - p[x]); // Update max gap for this value
      p[x] = i; // Update last seen position of this value
    }
    for (int i = 0; i < n; ++i)
      k[i] = std::max(k[i], n - p[i]); // Handle the final segment from last occurrence to end
    
    std::vector<int> ans(n + 1, -1); // ans[i] will hold the k-amazing number for k=i
    for (int x = 0, i = n; x < n; ++x)
      while (i >= k[x]) // While we haven't assigned this value's k to all segments
        ans[i--] = x + 1; // Assign the value (incremented for 1-based output)
    
    for (int i = 1; i <= n; ++i)
      std::cout << ans[i] << " \n"[i == n]; // Output result in one line per test case
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/