// Problem: CF 1720 D1 - Xor-Subsequence (easy version)
// https://codeforces.com/contest/1720/problem/D1

/*
Problem: D1. Xor-Subsequence (easy version)

Algorithm: Dynamic Programming with Optimization
Time Complexity: O(n * sqrt(n)) per test case, where n is the size of the array
Space Complexity: O(n)

The problem asks for the length of the longest "beautiful" subsequence.
A beautiful subsequence satisfies:
For any two consecutive elements in the subsequence at indices p and p+1:
a[b_p] XOR b_{p+1} < a[b_{p+1}] XOR b_p

This is solved using dynamic programming where f[i] represents the longest
beautiful subsequence ending at index i. For optimization, we iterate through
only a subset of previous indices (specifically those in range [i >> 8 << 8, i)).
*/

#include <algorithm>
#include <iostream>
using namespace std;
const int N = 300100;
int f[N], a[N];

void solve() {
  int n;
  cin >> n;
  int ans = 0;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++) {
    f[i] = 1; // Every element forms a subsequence of length 1
    // Loop through specific range to optimize: from (i >> 8 << 8) to i
    for (int j = (i >> 8 << 8); j < i; j++)
      if ((a[j] ^ i) < (a[i] ^ j)) // Check the beautiful condition
        f[i] = max(f[i], f[j] + 1); // Update dp value
    ans = max(ans, f[i]); // Keep track of maximum length found
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/