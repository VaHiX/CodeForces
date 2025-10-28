// Problem: CF 2106 E - Wolf
// https://codeforces.com/contest/2106/problem/E

/*
E. Wolf
Algorithms/Techniques: Binary search simulation with precomputed positions and greedy adjustment.

Time Complexity: O(n * q) amortized over all test cases.
Space Complexity: O(n)

The code simulates binary search on a permutation array p to find value k in range [l, r].
It determines the minimal number of elements that need to be reordered (d) so that 
the binary search succeeds. The key idea is to adjust values around k in such a way 
that comparisons during binary search lead to success.

*/
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
typedef long long ll;
#define int long long
#define endl '\n'
typedef pair<int, int> PII;

void solve() {
  int n, q;
  cin >> n >> q;
  int p[n + 1], pos[n + 1]; // p: permutation array, pos: positions of values in p
  for (int i = 1; i <= n; i++) {
    cin >> p[i];
    pos[p[i]] = i; // Store position of each value
  }
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    int x = pos[k]; // Position of k in original array
    if (x < l || x > r) { // k not in range [l,r]
      cout << "-1 ";
      continue;
    }
    int cl = 0, cr = 0, ul = 0, ur = 0; // Counters for comparisons
    while (l <= r) {
      int m = (l + r) >> 1; // Midpoint
      if (m == x)
        break;
      else if (m < x) { // Midpoint is to the left of k
        if (p[m] > k) // Value at mid is greater than k
          cl++;
        else
          ul++; // Value at mid is less than or equal to k
        l = m + 1;
      } else { // Midpoint is to the right of k
        if (p[m] < k) // Value at mid is less than k
          cr++;
        else
          ur++; // Value at mid is greater than or equal to k
        r = m - 1;
      }
    }
    int ans = max(cl, cr) * 2; // Compute minimal swaps needed
    if (cl + ul > k - 1 || cr + ur > n - k) // Impossible to satisfy constraints
      ans = -1;
    cout << ans << " ";
  }
  cout << endl;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/