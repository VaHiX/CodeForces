// Problem: CF 2155 C - The Ancient Wizards' Capes
// https://codeforces.com/contest/2155/problem/C

/*
C. The Ancient Wizards' Capes
Algorithm: Dynamic Programming with Range Constraints
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

This problem involves determining the number of valid cape arrangements for wizards
such that their visibility counts match a given array 'a'. Each wizard can wear
their cape on either left or right side. A wizard at position j is visible from
position i if:
- Wizard j wears cape on left and i >= j, or
- Wizard j wears cape on right and i <= j.

The approach treats the problem as a dynamic programming with range constraints.
We define v[i] = a[i] - i to transform visibility conditions into constraint equations.
By tracking the valid ranges for cumulative sums of these transformed values,
we compute how many valid arrangements exist for each test case modulo 676767677.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;
const i64 MOD = 676767677;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  if (!(cin >> T))
    return 0;
  while (T--) {
    int n;
    cin >> n;
    vector<i64> a(n + 1);
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    vector<i64> v(n + 1);
    for (int i = 1; i <= n; i++)
      v[i] = a[i] - i;
    i64 lo = 0, hi = n, A = 0;
    for (int i = 1; i <= n; i++) {
      if (i & 1) { // odd index
        lo = max(lo, v[i] + 2 * A);   // update lower bound
        hi = min(hi, v[i] + 2 * A + 1); // update upper bound
      } else { // even index
        lo = max(lo, -v[i] + 2 * A - 1); // update lower bound
        hi = min(hi, -v[i] + 2 * A);     // update upper bound
      }
      A += (i & 1) ? v[i] : -v[i]; // accumulate A based on parity
    }
    i64 An1 = A - ((n & 1) ? v[n] : -v[n]); // final accumulated value at n
    i64 ans = 0;
    if (n & 1) { // odd n
      if (An1 == -v[n]) {
        if (lo <= hi)
          ans = (hi - lo + 1) % MOD;
        else
          ans = 0;
      } else
        ans = 0;
    } else { // even n
      i64 L0 = An1 - v[n];
      if (lo <= L0 && L0 <= hi && 0 <= L0 && L0 <= n)
        ans = 1;
      else
        ans = 0;
    }
    cout << ans % MOD << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/