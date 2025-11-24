// Problem: CF 2172 D - Divisor Card Game
// https://codeforces.com/contest/2172/problem/D
//
// Notes & overview:
// - This program computes, for each card value x in [1..m], the number of ways
//   certain sequences of picks (defined by divisibility and markers b[i]) can
//   lead to contributions counted at index b[i].
// - It uses combinatorics with factorials/inverses, dynamic programming (dp),
//   and a heuristic "jump" condition to prune branches based on divisibility
//   structure between a[i] values.
// - All arithmetic is modulo MOD = 998244353.
//
// Main components:
// - power(a,n): modular exponentiation for computing modular inverses.
// - rand_int: deterministic helper seeded with steady_clock (unused by core
// logic).
// - solve(): reads a, b arrays, computes factorials and inverse factorials,
//   runs the DP over indices using divisibility transitions, and outputs
//   result.
//
// Implementation details and inline comments are added below.

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
const int mod = 998244353;

// Modular exponentiation: computes a^n mod mod (n >= 0).
int power(int a, int n) {
  int res = 1;
  while (n) {
    if (n & 1) res = res * a % mod;
    a = a * a % mod;
    n >>= 1;
  }
  return res;
}

const int maxn = 2e5 + 5;
const int inf = 1e18;

// Random generator (seeded once). Present but not essential to core DP.
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l, int r) { return l + abs((int)rng()) % (r - l + 1); }

// Solve single test instance.
// Input: n m
//        arrays a[0..n-1], b[0..n-1]
// Output: for each x in 1..m, number of contributions modulo mod.
void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];

  // jmp[i] = true if there exists some later index j > i such that a[j] is
  // divisible by a[i] and b[j] is non-zero. This is used as a pruning hint.
  vector<bool> jmp(n);
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      if (a[j] % a[i] == 0 && b[j]) jmp[i] = true;

  // Precompute factorials (fac), inverse factorials (dfac),
  // and inv[k] = modular inverse of k (computed via dfac * fac).
  vector<int> fac(n + 1), dfac(n + 1), inv(n + 1);
  fac[0] = dfac[0] = inv[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
  dfac[n] = power(fac[n], mod - 2);  // modular inverse of fac[n]
  for (int i = n; i >= 1; i--) {
    dfac[i - 1] = dfac[i] * i % mod;
    inv[i] = dfac[i] * fac[i - 1] % mod;  // inv[i] = 1/i mod
  }

  // res[x] accumulates contributions for output index x (1..m)
  vector<int> res(m + 1);

  // dp[i][k] = number of ways to reach index i carrying parameter k (k is
  // used to control combinatorial weighting via inv[j+k]).
  // dp is sized n x n; entries remain small for typical n in constraints.
  vector<vector<int>> dp(n, vector<int>(n, 0));

  for (int i = 0; i < n; i++) {
    // base: staying at i with k=0
    dp[i][0]++;

    if (!b[i]) {
      // When b[i] == 0, we attempt to propagate "chains" forward
      // through indices x > i where a[x] is divisible by a[i].
      int k = 1;
      for (int x = i + 1; x < n; x++) {
        if (a[x] % a[i] != 0) continue;  // only follow divisibility
        if (!b[x] && !jmp[x]) continue;  // prune dead branches
        // For each existing j up to i, extend dp[x][j+k] using dp[i][j]
        // weighted by inv[j+k] (modular inverse for combinatorial factor)
        for (int j = 0; j <= i; j++) {
          dp[x][j + k] = (dp[x][j + k] + dp[i][j] * inv[j + k]) % mod;
        }
        k++;
        if (b[x]) break;  // stop chain when encountering non-zero b[x]
      }
    } else {
      // If b[i] != 0, this index contributes to res[b[i]]: sum over all k
      // possibilities stored in dp[i][j].
      for (int j = 0; j <= i; j++) res[b[i]] = (res[b[i]] + dp[i][j]) % mod;
    }
  }

  // Print results for 1..m
  for (int i = 1; i <= m; i++) cout << res[i] << ' ';
  cout << '\n';
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int test = 1;
  while (test--) solve();
  return 0;
}

// https://github.com/VaHiX/CodeForces/