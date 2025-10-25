// Problem: CF 2045 E - Narrower Passageway
// https://codeforces.com/contest/2045/problem/E

/*
E. Narrower Passageway
Algorithms/Techniques: Monotonic stack, inclusion-exclusion principle, modular arithmetic
Time Complexity: O(N)
Space Complexity: O(N)

This problem asks to compute the expected strength of a deployment on a 2-row grid with fog.
Each column has 50% chance of being foggy, meaning soldiers are either deployed or not.
We define connected areas as maximal consecutive columns without fog.
For each such area [u,v], we calculate:
- m1 = max power in row 1 across columns u to v
- m2 = max power in row 2 across columns u to v
If m1 == m2, strength is 0. Else, strength is min(m1, m2).
The result is the sum over all such areas of their expected strengths.
We use monotonic stacks to find left/right boundaries for max elements,
combined with inclusion-exclusion on contributions to compute final answer in modular arithmetic.
*/

#include <stdio.h>
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <utility>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int N = 1e5 + 5, MOD = 998244353;
int n, a[3][N], L[3][N], R[3][N], ans;
int P2[N], *p2 = P2 + 1;
int A(int x, int y) { return x + y >= MOD ? x + y - MOD : x + y; }
int A(initializer_list<int> t) {
  int res = 0;
  for (auto i : t)
    res = A(res, i);
  return res;
}
void SA(int &x, int y) { x = A(x, y); }
int S(int x, int y) { return A(x, MOD - y); }
int W(int x, int y) { return 1ll * x * y % MOD; }
int W(initializer_list<int> t) {
  int res = 1;
  for (auto i : t)
    res = W(res, i);
  return res;
}
void SW(int &x, int y) { x = W(x, y); }
int P(int x, int y) {
  int res = 1, t = x % MOD;
  while (y) {
    if (y & 1)
      res = W(res, t);
    t = W(t, t);
    y >>= 1;
  }
  return res;
}
int D(int x, int y) { return W(x, P(y, MOD - 2)); }
int Q(int x) { return W(x, x); }
int tp, stk[N];
void monostack(int *a, int *L, int *R, bool flag) {
  tp = 0, stk[0] = 0;
  for (int i = 1; i <= n; i++) {
    while (tp > 0 && a[stk[tp]] <= a[i])
      tp--;
    L[i] = stk[tp] + 1;
    stk[++tp] = i;
  }
  tp = 0, stk[0] = n + 1;
  for (int i = n; i >= 1; i--) {
    while (tp > 0 && a[stk[tp]] < a[i] + flag) // flag is used to handle strict inequality for right boundary
      tp--;
    R[i] = stk[tp] - 1;
    stk[++tp] = i;
  }
}
int main() {
#ifdef Aquizahv
  freopen("data.in", "r", stdin);
  freopen("data.out", "w", stdout);
#endif
  cin >> n;
  p2[0] = 1; // Precompute powers of 2 modulo MOD
  for (int i = 1; i <= n; i++)
    p2[i] = W(p2[i - 1], 2);
  for (int i = 1; i <= n; i++)
    scanf("%d", a[0] + i); // Read row 1
  for (int i = 1; i <= n; i++)
    scanf("%d", a[1] + i), a[2][i] = max(a[0][i], a[1][i]); // Also compute max of both rows
  for (int i = 0; i <= 1; i++)
    monostack(a[i], L[i], R[i], 0); // Left/right boundaries for rows 0 and 1
  monostack(a[2], L[2], R[2], 1); // For combined max row with strict comparison for right boundary calculation
  for (int i = 1; i <= n; i++) {
    for (int k = 0; k <= 1; k++) { // Iterate over both rows
      SA(ans, W(a[k][i], W(S(p2[i - 1], p2[L[k][i] - 2]),
                           S(p2[n - i], p2[n - R[k][i] - 1])))); // Add weighted contribution based on inclusion-exclusion principle
      if (a[k][i] == a[2][i]) // Special case for when current element is maximum in both rows
        ans = S(ans,
                W(a[k][i], W(S(p2[i - 1], p2[L[2][i] - 2]),
                             S(p2[n - i], p2[n - min(R[2][i], R[k][i]) - 1])))); // Adjust for overlapping regions
    }
  }
  cout << D(ans, p2[n]) << endl; // Divide by 2^N to get expected value (modular inverse)
  return 0;
}


// https://github.com/VaHiX/codeForces/