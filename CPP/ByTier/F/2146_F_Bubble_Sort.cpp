// Problem: CF 2146 F - Bubble Sort
// https://codeforces.com/contest/2146/problem/F

/*
F. Bubble Sort

Algorithm/Techniques:
- Dynamic Programming with Coordinate Compression
- Fast Exponentiation
- Binary Search (lower_bound, unique)
- Modular Arithmetic

Time Complexity: O(n * m * log n + n * log^2 n + sum(m^2))
Space Complexity: O(n + m)

This problem involves counting permutations of length n that satisfy certain constraints on the number of rounds required for bubble sort at each prefix. The solution uses dynamic programming over coordinate-compressed positions, where transitions are computed using prefix sums and modular arithmetic.
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>

void Freopen() {
  freopen("", "r", stdin);
  freopen("", "w", stdout);
}
using namespace std;
const int N = 1e6 + 10, M = 1e3 + 10, inf = 1e9, mod = 998244353;
int add(int x, int v) {
  x += v;
  return x >= mod ? x - mod : x;
}
int n, m;
struct lim {
  int k, l, r;
} q[M];
int ind[2 * M], tot; // Coordinate compression array
int fac[N], inv[N];   // Precomputed factorials and their modular inverses
int f[2 * M], g[2 * M]; // DP arrays for current and next states
int ID(int x) { return lower_bound(ind + 1, ind + tot + 1, x) - ind; } // Map value to compressed index

// Fast exponentiation with modular arithmetic
int ksm(int a, int b, int res = 1) {
  while (b) {
    if (b & 1)
      res = 1ll * res * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return res;
}

// Calculate combinations or powers based on given parameters
int cal(int l, int r, int k) {
  if (k >= r) {
    // If k is large enough, return factorial ratio
    return 1ll * fac[r] * inv[l] % mod;
  } else if (k <= l) {
    // If k is small, compute base^exponent directly
    return ksm(k, r - l);
  } else {
    // General case using modular arithmetic
    return 1ll * ksm(k, r - k) * fac[k] % mod * inv[l] % mod;
  }
}

void solve() {
  cin >> n >> m;
  tot = 0, ind[++tot] = 0; // Initialize coordinate compression array

  for (int i = 1; i <= m; i++) {
    cin >> q[i].k >> q[i].l >> q[i].r, q[i].r += 1;
    ind[++tot] = q[i].l;
    if (q[i].r <= n)
      ind[++tot] = q[i].r;
  }

  sort(q + 1, q + m + 1, [&](lim a, lim b) { return a.k < b.k; }); // Sort queries by k

  sort(ind + 1, ind + tot + 1), tot = unique(ind + 1, ind + tot + 1) - ind - 1;
  
  f[1] = 1; // Base case: only one way to start with first element
  
  for (int o = 1; o <= m; o++) {
    int k = q[o].k, l = q[o].l, r = q[o].r;
    for (int i = 1; i <= tot; i++)
      g[i] = 0; // Reset next state
    
    int L = ID(l), R = ID(r);
    
    for (int i = 1; i <= tot; i++) {
      if (ind[i] < l)
        // Contribution if current position is before lower bound
        g[L] = add(g[L], 1ll * f[i] * cal(ind[i], l, k + 1) % mod);
      else
        g[i] = add(g[i], f[i]); // Direct contribution otherwise
        
      if (r > n)
        continue;
        
      if (ind[i] < r)
        // Contribute negative amount for positions before upper bound
        g[R] = add(g[R], add(-1ll * f[i] * cal(ind[i], r, k + 1) % mod, mod));
      else
        g[i] = add(g[i], mod - f[i]); // Negate contribution if past upper bound
    }
    
    for (int i = 1; i <= tot; i++)
      f[i] = g[i]; // Update DP state
  }
  
  int ans = 0;
  for (int i = 1; i <= tot; i++)
    ans = add(ans, 1ll * f[i] * cal(ind[i], n, n) % mod), f[i] = 0; 
  cout << ans << '\n';
}

signed main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  inv[0] = fac[0] = 1;
  for (int i = 1; i < N; i++)
    fac[i] = 1ll * fac[i - 1] * i % mod, inv[i] = ksm(fac[i], mod - 2);
  
  int T;
  cin >> T;
  while (T--)
    solve();
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/