// Problem: CF 1967 E2 - Again Counting Arrays (Hard Version)
// https://codeforces.com/contest/1967/problem/E2

/*
Algorithm: Dynamic Programming with Inclusion-Exclusion and Difference Array
Time Complexity: O(n + m)
Space Complexity: O(n)

The problem requires counting valid arrays 'a' such that there exists a non-negative continuous array 'b' with b[0] = b0 and b[i] = a[i] for at least one i.
We use inclusion-exclusion and difference arrays to efficiently compute valid transitions for b values based on a values.

The core idea is:
1. For each possible value of a[i], we determine which values of b[i] can be valid.
2. We construct difference arrays to handle range updates for b values.
3. We use inclusion-exclusion to subtract invalid cases.
4. Finally, we compute contribution of each prefix and apply combinatorics.

Key techniques:
- Difference array technique for efficient range updates
- Inclusion-exclusion principle
- Modular arithmetic with precomputed inverses
- Efficient DP using prefix sums
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int MOD = 998244353;
const int N = 2e6 + 5;
int inv[N];
int inversemod(int p, int q) {
  return (p > 1 ? q - 1LL * inversemod(q % p, p) * q / p : 1);
}
void add(int &x, int y) {
  x += y;
  if (x >= MOD)
    x -= MOD;
}
void sub(int &x, int y) {
  x -= y;
  if (x < 0)
    x += MOD;
}
int solve(int n, int m, int b0) {
  vector<int> pw(n + 1);
  pw[0] = 1;
  for (int i = 1; i <= n; i++)
    pw[i] = 1LL * pw[i - 1] * (m - 1) % MOD;
  vector<int> a(n + 2);
  auto work = [&](int c, int pw_coeff, int sgn_x) -> bool {
    int l = 0;
    if (sgn_x == 1)
      l = max(l, (n + c + 1) >> 1);
    int r = n;
    if (sgn_x == -1)
      r = min(r, (n + c - 1) >> 1);
    if (l > r)
      return 0;
    add(a[l], 1LL * pw_coeff * pw[l - (b0 + c) / 2] % MOD);
    sub(a[r + 1], 1LL * pw_coeff * pw[r + 1 - (b0 + c) / 2] % MOD);
    return 1;
  };
  int ans = 0;
  for (int k = 0; work(2 * (m + 1) * k - b0, 1, 1); k++)
    ;
  for (int k = 0; work(2 * (m + 1) * k + 2 + b0, MOD - 1, 1); k++)
    ;
  for (int k = 0; work(-2 * m - 2 * (m + 1) * k + b0, 1, -1); k++)
    ;
  for (int k = 1; work(-2 * (m + 1) * k - b0, MOD - 1, -1); k++)
    ;
  for (int i = 1; i <= n; i++) {
    add(a[i], 1LL * a[i - 1] * (m - 1) % MOD);
  }
  int coeff = 1;
  for (int i = 0; i <= n; i++) {
    add(ans, 1LL * coeff * a[i] % MOD);
    coeff = 1LL * coeff * (n - i) % MOD * inv[i + 1] % MOD;
  }
  return ans;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  inv[1] = 1;
  for (int i = 2; i < N; i++)
    inv[i] = 1LL * (MOD - MOD / i) * inv[MOD % i] % MOD;
  int T;
  cin >> T;
  while (T--) {
    int n, m, b0;
    cin >> n >> m >> b0;
    if (b0 >= m) {
      int ans = 1;
      for (int i = 0; i < n; i++)
        ans = 1LL * ans * m % MOD;
      cout << ans << '\n';
      continue;
    }
    cout << solve(n, m, b0) << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/