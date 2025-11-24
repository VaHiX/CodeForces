// Problem: CF 2013 E - Prefix GCD
// https://codeforces.com/contest/2013/problem/E

/*
E. Prefix GCD
Algorithm: Greedy + Prefix GCD computation
Time Complexity: O(n * sqrt(max_a) + n log n) per test case (due to GCD computations and sorting)
Space Complexity: O(n) for the array storage

The problem asks to minimize the sum of prefix GCDs after rearranging the array.
The greedy approach tries to keep the current GCD as small as possible by choosing
the element that minimizes the new GCD at each step.
*/

#include <algorithm>
#include <iostream>
#include <numeric>
int a[100001];
int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  int t;
  std::cin >> t;
  while (t--) {
    int n, ga = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++)
      std::cin >> a[i], ga = std::gcd(ga, a[i]); // Compute overall GCD of the array
    long long ans = 0;
    int g = 0;
    for (int i = 0; i < n; i++) {
      int x = 1e9;
      for (int j = 0; j < n; j++)
        x = std::min(x, std::gcd(g, a[j])); // Find minimum GCD when adding a[j] to current prefix
      ans += g = x; // Add the new GCD to answer and update current GCD
      if (g == ga) { // If current GCD equals overall GCD, remaining elements will also contribute ga
        ans += (n - i - 1ll) * g; // Add remaining GCDs directly as they are all equal to ga
        break;
      }
    }
    std::cout << ans << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/