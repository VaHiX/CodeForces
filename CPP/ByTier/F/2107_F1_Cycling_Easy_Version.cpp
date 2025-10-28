// Problem: CF 2107 F1 - Cycling (Easy Version)
// https://codeforces.com/contest/2107/problem/F1

/*
F1. Cycling (Easy Version)
time limit per test2 seconds
memory limit per test256 megabytes

This is the easy version of the problem. The difference between the versions is that in this version,
1≤n≤5⋅10^3 and you don't need to output the answer for each prefix. You can hack only if you solved all versions of this problem.

Leo works as a programmer in the city center, and his lover teaches at a high school in the suburbs. Every weekend, Leo would ride his bike to the suburbs to spend a nice weekend with his lover.
There are n cyclists riding in front of Leo on this road right now. They are numbered 1, 2, ..., n from front to back. Initially, Leo is behind the n-th cyclist. The i-th cyclist has an agility value a_i.
Leo wants to get ahead of the 1-st cyclist. Leo can take the following actions as many times as he wants:
Assuming that the first person in front of Leo is cyclist i, he can go in front of cyclist i for a cost of a_i. This puts him behind cyclist i−1.
Using his super powers, swap a_i and a_j (1≤i<j≤n) for a cost of (j−i).
Leo wants to know the minimum cost to get in front of the 1-st cyclist.

Algorithms/Techniques:
- Preprocessing with prefix sums
- Greedy approach with optimal swapping points
- Dynamic programming idea using minimal cost calculation

Time Complexity: O(n^2) per test case (due to nested loops)
Space Complexity: O(n) for arrays b, s

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
  b[n + 1] = 1e18; // Initialize with large value to avoid overflow in min operation
  for (int i = n; i > 0; --i)
    b[i] = min(b[i + 1], a[i]); // Precompute minimum from i to end

  // s[i] stores prefix sum of cost if we move all elements forward up to position i
  for (int i = 1; i <= n; ++i)
    s[i] = s[i - 1] + b[i] + (a[i] != b[i]); // Cost includes moving past current element + potential swap
  ans = s[n]; // Default cost without any swaps

  // Try all positions where a[i] equals minimum value in suffix from i onwards
  for (int i = 1; i <= n; ++i)
    if (a[i] == b[i]) {
      // If current element is the minimum in its suffix, it can be part of cost calculation via swaps
      ans = min(ans, s[i] + (n - i) * (a[i] + 1) + n - i);
    }
  cout << ans << "\n";
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  for (cin >> T; T; T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/