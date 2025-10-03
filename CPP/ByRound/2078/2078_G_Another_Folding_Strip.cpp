// Problem: CF 2078 G - Another Folding Strip
// https://codeforces.com/contest/2078/problem/G

/*
 * Problem: G. Another Folding Strip
 * 
 * Purpose:
 *   Computes the sum of f(a_l, ..., a_r) for all subarrays of array a,
 *   where f(b) is defined as the minimum number of dyeing operations
 *   required to achieve darkness configuration b on a 1x|m| strip.
 *   Each operation allows folding and dropping dye at one position.
 *
 * Algorithms/Techniques:
 *   - Use prefix sums of alternating signs to transform problem.
 *   - Monotonic stack to compute contribution of each element in all subarrays.
 *   - Two-pass monotonic stack technique: once for strictly increasing,
 *     once for non-increasing to handle min/max appropriately.
 *
 * Time Complexity:
 *   O(n) per test case, amortized over all test cases due to the constraint
 *   on total n and use of stack-based processing.
 *
 * Space Complexity:
 *   O(n) for arrays st, L, R, b, a.
 */

#include <iostream>

#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i++)
#define Rof(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
const int N = 2e5 + 5, mod = 998244353;
int n, a[N], b[N];
int top, ans, st[N], L[N], R[N];

// Modular addition
inline void add(int &x, int y) {
  x += y;
  if (x >= mod)
    x -= mod;
}

// Modular subtraction
inline void sub(int &x, int y) {
  x += mod - y;
  if (x >= mod)
    x -= mod;
}

void Solve() {
  cin >> n;
  For(i, 1, n) cin >> a[i];
  
  // Compute prefix sum of b[i] = b[i-1] + a[i] when i is odd, or b[i-1] - a[i] when i is even
  For(i, 1, n) {
    if (i & 1)
      b[i] = b[i - 1] + a[i];
    else
      b[i] = b[i - 1] - a[i];
  }
  
  top = ans = 0;
  
  // Initialize right boundaries for monotonic stack (strictly increasing)
  For(i, 1, n) R[i] = n;
  
  // Process strictly increasing monotonic stack
  For(i, 1, n) {
    while (top && b[st[top]] < b[i])
      R[st[top]] = i - 1, top--;
    L[i] = !top ? 0 : st[top] + 1;
    st[++top] = i;
  }
  
  // Compute contribution using increasing stack
  For(i, 1, n)
    (ans += (R[i] - i + 1) * (i - L[i] + 1) % mod * (b[i] % mod) % mod) %= mod;

  top = 0;
  
  // Again initialize R array for non-increasing monotonic stack
  For(i, 1, n) R[i] = n;
  
  // Process non-increasing monotonic stack (with equal values handled)
  For(i, 0, n) {
    while (top && b[st[top]] >= b[i])
      R[st[top]] = i - 1, top--;
    L[i] = !top ? 0 : st[top] + 1;
    st[++top] = i;
  }
  
  // Subtract contribution from non-increasing stack
  For(i, 1, n)
    (ans -= (R[i] - i + 1) * (i - L[i] + 1) % mod * (b[i] % mod) % mod) %= mod;

  ans = (ans % mod + mod) % mod;
  cout << ans << '\n';
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int T = 1;
  cin >> T;
  while (T--)
    Solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/