// Problem: CF 2107 F1 - Cycling (Easy Version)
// https://codeforces.com/contest/2107/problem/F1

/*
F1. Cycling (Easy Version)
time limit per test2 seconds
memory limit per test256 megabytes

Algorithms/Techniques: 
- Preprocessing with prefix sums and min arrays
- Greedy approach to minimize cost by choosing optimal swapping positions
- Dynamic programming concept with optimized state transitions

Time Complexity: O(N^2) per test case, where N is the size of input array.
Space Complexity: O(N), for storing arrays a, b, s.

This problem involves finding the minimum cost for Leo to move from behind the last cyclist to in front of the first cyclist, 
by performing swaps and moving operations with specific costs. The key insight is to preprocess the minimum elements to the right
and use prefix sums for efficient computation.

The approach uses:
1. Precomputing `b[i]` which stores minimum value from index i to n.
2. Using prefix sum array `s` to keep track of cumulative cost.
3. Iterating over possible positions to find optimal cost.
4. The main logic checks if a[i] == b[i], in which case it computes a potential optimal path.

*/

#include <algorithm>
#include <iostream>
#define int long long
using namespace std;
const int N = 5e3 + 5;
int T, n, a[N], b[N], s[N], ans;

void solve() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  b[n + 1] = 1e18; // Initialize with large value to ensure correct min computation
  for (int i = n; i > 0; --i)
    b[i] = min(b[i + 1], a[i]); // Precompute minimum from right to left
  
  for (int i = 1; i <= n; ++i)
    s[i] = s[i - 1] + b[i] + (a[i] != b[i]); // Build prefix sum of costs including moves and differences

  ans = s[n]; // Initial answer assuming we go through everything
  for (int i = 1; i <= n; ++i)
    if (a[i] == b[i]) // Only consider positions where a[i] is the minimum element in suffix starting at i
      ans = min(ans, s[i] + (n - i) * (a[i] + 1) + n - i); // Compute cost for moving all remaining behind fixed element
  cout << ans << "\n";
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  for (cin >> T; T; T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/