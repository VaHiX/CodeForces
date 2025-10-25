// Problem: CF 2123 G - Modular Sorting
// https://codeforces.com/contest/2123/problem/G

/*
G. Modular Sorting
Algorithms/Techniques: 
    - Modular arithmetic
    - Optimized iteration over divisors
    - Preprocessing for GCD-based grouping
    - Lazy evaluation with caching

Time Complexity:
    - For each query of type 1: O(cnt), where cnt is the number of unique GCDs processed so far.
    - For each query of type 2: O(cnt + n), where cnt is at most log(m) due to unique divisors, and n is the size of array.
Space Complexity:
    - O(N + M), where N = 500005, M = 205. This accounts for arrays a, c, to, d.

*/
#include <algorithm>
#include <iostream>

#pragma GCC optimize("O3")
#define N 500005
#define M 205
using namespace std;
int n, m, q, cnt, a[N], c[M], to[N], d[N];

void solve() {
  cin >> n >> m >> q;
  // Reset the tracking arrays for each test case
  for (int i = 1; i <= cnt; i++)
    to[d[i]] = 0;
  cnt = 0;
  // Read input array elements
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  while (q--) {
    int op, x, y;
    cin >> op >> x;
    if (op == 1) {  // Update value at index x to y
      cin >> y;
      // For each processed divisor group, update the count of inversions
      for (int i = 1; i <= cnt; i++) {
        if (x > 1)
          if (a[x - 1] % d[i] > a[x] % d[i])
            c[i]--;
        if (x < n)
          if (a[x] % d[i] > a[x + 1] % d[i])
            c[i]--;
        if (x > 1)
          if (a[x - 1] % d[i] > y % d[i])
            c[i]++;
        if (x < n)
          if (y % d[i] > a[x + 1] % d[i])
            c[i]++;
      }
      a[x] = y;
    } else {  // Check if array can be made non-decreasing with operation of step size x
      int num = __gcd(m, x), len = m / num;   // GCD to compute cycle length
      if (!to[num]) {  // If this divisor group hasn't been seen before
        to[num] = ++cnt;
        d[cnt] = num;
        c[cnt] = 1;
        for (int i = 2; i <= n; i++)   // Count inversions in current grouping
          if (a[i - 1] % d[cnt] > a[i] % d[cnt])
            c[cnt]++;
      }
      if (c[to[num]] <= len)   // If inversion count is within bounds, it's possible
        cout << "YES\n";
      else if (c[to[num]] == len + 1) {   // Check special condition for exactly one extra inversion
        if (a[n] % d[to[num]] < m % num)
          cout << "YES\n";   // If last element can be corrected, it's possible
        else
          cout << "NO\n";
      } else
        cout << "NO\n";  // Too many inversions for any valid transformation
    }
  }
  return;
}

int main() {
  ios::sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/