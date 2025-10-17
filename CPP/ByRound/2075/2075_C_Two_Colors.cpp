// Problem: CF 2075 C - Two Colors
// https://codeforces.com/contest/2075/problem/C

/*
C. Two Colors
Algorithm: Dynamic Programming + Prefix Sum
Time Complexity: O(n + m) per test case
Space Complexity: O(n) per test case

The problem is about painting a fence with exactly two colors such that:
- Each plank is painted with exactly one color.
- All planks of the same color form a continuous sequence.
- Each color can be used at most `a_i` times.

Approach:
1. For each color, compute how many planks can be painted with it using prefix sums.
2. Enumerate all possible positions where the split between two colors occurs.
3. For each split position, count valid combinations of painting both sides such that:
   - Left side uses one color, right side uses another.
   - Each color doesn't exceed its limit `a_i`.
4. Use a prefix sum array `v` to precompute how many planks can be colored with at least `i` colors.
5. Multiply valid combinations for each split and accumulate the result.

*/
#include <algorithm>
#include <iostream>
#include <vector>

#define int long long
using namespace std;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<int> v(n + 2); // v[i] will store number of colors with at least i planks
    for (int i = 0; i < m; ++i) {
      int x;
      cin >> x;
      v[x]++; // Count how many colors can cover at least x planks
    }
    // Compute prefix sum: v[i] now stores count of colors that can paint >= i planks
    for (int i = n; i; --i)
      v[i] += v[i + 1];
    
    int ans = 0;
    // Try all possible splits of the fence into two parts (left and right)
    for (int i = 1; i <= n / 2; ++i) {
      // Number of ways to paint left part with color 1, right part with color 2
      // v[n - i] gives count of colors that can cover at least (n - i) planks
      // max(0LL, v[i] - 1) gives number of colors that can cover at least i planks, minus one for symmetry
      // ((i != n - i) + 1) handles double-counting when both parts are equal
      ans += (v[n - i] * max(0LL, v[i] - 1) * ((i != n - i) + 1));
    }
    cout << ans << '\n';
  }
}


// https://github.com/VaHiX/codeForces/