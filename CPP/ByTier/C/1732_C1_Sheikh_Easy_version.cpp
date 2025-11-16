// Problem: CF 1732 C1 - Sheikh (Easy version)
// https://codeforces.com/contest/1732/problem/C1

/*
Algorithm: 
This code solves the problem of finding a subsegment [l, r] within a given range [L, R] 
that maximizes the function f(l, r) = sum(l, r) - xor(l, r), where sum and xor are the 
sum and XOR of elements in the subsegment respectively. If there are multiple optimal 
subsegments with the same maximum value, it chooses the one with the minimum length.

Approach:
1. Precompute prefix sums and prefix XORs for efficient range queries.
2. Use a two-pointer technique to find the optimal subsegment:
   - For each starting point 'll', we expand the ending point 'rr' until the value of f(ll, rr) exceeds the current maximum.
   - Update the answer if we find a better (larger f value) or a shorter subsegment with same f value.

Time Complexity:
- Preprocessing (prefix sums and XORs): O(n)
- Two-pointer search: O(n)
- Overall: O(n) per test case

Space Complexity:
- O(n) for storing prefix arrays
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define int long long
signed main() {
  int T;
  cin >> T;
  while (T--) {
    int n, q, l, r;
    cin >> n >> q;
    vector<int> a(n + 1), sum(n + 1), xo(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      sum[i] = sum[i - 1] + a[i];       // Compute prefix sum
      xo[i] = xo[i - 1] ^ a[i];         // Compute prefix XOR
    }
    cin >> l >> r;
    int ans = sum[n] - xo[n], ll, rr = 1;
    for (ll = 1; ll <= n; ll++) {
      if (rr < ll)
        rr = ll;
      while (rr <= n && (sum[rr] - sum[ll - 1]) - (xo[rr] ^ xo[ll - 1]) < ans)
        rr++;  // Expand rr until we get a better f value
      if (rr > n)
        break;
      if (rr - ll < r - l) {  // Update answer if current subsegment is shorter
        r = rr;
        l = ll;
      }
    }
    cout << l << ' ' << r << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/