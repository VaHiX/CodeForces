// Problem: CF 2056 E - Nested Segments
// https://codeforces.com/contest/2056/problem/E

/*
E. Nested Segments

Algorithms/Techniques: 
- Preprocessing combinatorial numbers (factorials and inverse factorials) using modular arithmetic
- Segment processing with stack-based interval merging logic
- Dynamic programming approach based on Catalan-like formula for counting valid segment additions

Time Complexity: O(n log n + n)
Space Complexity: O(n)

*/
#include <algorithm>
#include <cstdio>

#define mod 998244353
using namespace std;
int n = 200000, m, ans;
int inv[400005], fac[400005], invfac[400005];
int f[200005], stk[200005], top;
struct seg {
  int l, r;
} s[200005];
bool operator<(seg x, seg y) {
  if (x.r == y.r)
    return x.l > y.l; // If right endpoints are same, order by left endpoint descending
  return x.r < y.r;   // Order segments by right endpoint ascending
}
inline int sub(int x, int y) {
  if ((x -= y) < 0)
    x += mod;
  return x;
}
inline int C(int x, int y) {
  // Compute combination C(x, y) = x! / (y! * (x - y)!)
  return 1ll * fac[x] * invfac[y] % mod * invfac[x - y] % mod;
}
void init() {
  // Initialize factorials and inverse factorials
  fac[0] = invfac[0] = inv[1] = fac[1] = invfac[1] = f[1] = 1;
  for (int i = 2; i <= 2 * n; i += 1) {
    inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod; // Modular inverse
    fac[i] = 1ll * fac[i - 1] * i % mod;                  // Factorial
    invfac[i] = 1ll * invfac[i - 1] * inv[i] % mod;       // Inverse factorial
  }
  // Precompute f[i] as the number of ways to add segments in a segment of length i
  for (int i = 1; i < n; i += 1) {
    f[i + 1] = sub(C(2 * i, i), C(2 * i, i - 1)); // Catalan number related formula
  }
  return;
}
void solve() {
  scanf("%d%d", &m, &n);
  ans = 1;
  for (int i = 1; i <= n; i += 1) {
    scanf("%d%d", &s[i].l, &s[i].r);
  }
  sort(s + 1, s + n + 1); // Sort segments by right endpoint ascending, then left descending
  top = 0;
  if (s[n].l != 1 || s[n].r != m)
    s[++n] = (seg){1, m}; // Add full range segment if not already present
  for (int i = 1, j; i <= n; i += 1) {
    int len = s[i].r - s[i].l + 1; // Length of current segment
    while (top) {
      j = stk[top];
      if (s[i].l <= s[j].l) { // If segment i contains stack top segment
        len -= (s[j].r - s[j].l); // Decrease length by contained segment size
        top -= 1;
      } else
        break;
    }
    ans = 1ll * ans * f[len] % mod; // Multiply result by number of valid segment arrangements in current interval
    stk[++top] = i;                 // Push index to stack
  }
  printf("%d\n", ans);
  return;
}
int main() {
  init();
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/