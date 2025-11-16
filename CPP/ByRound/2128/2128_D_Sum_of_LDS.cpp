// Problem: CF 2128 D - Sum of LDS
// https://codeforces.com/contest/2128/problem/D

/*
D. Sum of LDS
Algorithms/Techniques: 
  - Observing that the given condition ensures a specific structure in permutations, allowing optimization.
  - For each element, we calculate how many subarrays have this element as part of their longest decreasing subsequence (LDS).
  - The key insight is to compute contribution of each element based on its neighbors and position.
  - Efficiently compute prefix/suffix contributions using a single pass with cumulative logic.

Time Complexity: O(n) per test case
Space Complexity: O(n) for the array storage

*/

#include <iostream>

using namespace std;
using ll = long long;
const int kMaxN = 5e5 + 100;
int t, n, a[kMaxN];
ll ans;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--;) {
    cin >> n, ans = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i]; 
      // If previous element is greater than current, 
      // we compute contribution of this drop to the answer
      a[i - 1] > a[i] && (ans += (n - i + 1ll) * (i - 1));
    }
    // Add base contribution from all single elements (each contributes 1)
    cout << ans + (1ll + n) * n / 2 << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/