// Problem: CF 2124 H - Longest Good Subsequence
// https://codeforces.com/contest/2124/problem/H

/*
H. Longest Good Subsequence

Purpose:
This code finds the length of the longest "good" subsequence in a given array.
A subsequence is considered "good" if:
1. Each element b[i] satisfies 1 ≤ b[i] ≤ i.
2. There exists a permutation p such that for each i, b[i] is the smallest integer
   where min(p[b[i]], ..., p[i]) = p[i].

Algorithm/Techniques:
- Dynamic Programming with memoization
- Sparse table or segment tree-like processing of intervals and values
- Efficient preprocessing using positions of elements

Time Complexity: O(n^2) per test case in worst-case due to nested loops and the way dp is filled.
Space Complexity: O(n^2 + n) for memoization and preprocessed arrays.

*/

#pragma GCC optimize("O3,unroll-loops")
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;
#define int long long
#define pii pair<int, int>
#define F first
#define S second
#define all(x) begin(x), end(x)
#define smn(v, x) (v = min(v, x))
#define smx(v, x) (v = max(v, x))
int tests = 1;
const int MOD = 998244353;
const int INF = 2e18;

struct mod {
  int x;
  mod(int a = 0) : x(a % MOD) {}
  mod &operator+=(const mod &y) {
    x += y.x;
    if (x >= MOD) {
      x -= MOD;
    }
    return *this;
  }
  mod &operator-=(const mod &y) {
    x -= y.x;
    if (x < 0) {
      x += MOD;
    }
    return *this;
  }
  mod &operator*=(const mod &y) {
    x = (x * y.x) % MOD;
    return *this;
  }
  static mod exp(mod b, int e) {
    mod res = 1;
    for (; e; e >>= 1) {
      if (e & 1) {
        res *= b;
      }
      b *= b;
    }
    return res;
  }
  mod inv() const { return exp(*this, MOD - 2); }
  mod &operator/=(const mod &y) { return *this *= y.inv(); }
  friend mod operator+(mod a, const mod &b) { return a += b; }
  friend mod operator-(mod a, const mod &b) { return a -= b; }
  friend mod operator*(mod a, const mod &b) { return a *= b; }
  friend mod operator/(mod a, const mod &b) { return a /= b; }
  friend bool operator==(const mod &a, const mod &b) { return a.x == b.x; }
  friend bool operator!=(const mod &a, const mod &b) { return a.x != b.x; }
  friend mod operator<<(int a, const mod &b) { return mod(a << b.x); }
};

const int N = 15003;
int n, m;
int a[N];
vector<int> pos[N]; // Stores positions of each value a[i]
short dp[N][N]; // Memoization table for dynamic programming states

// Recursively solve subproblem starting from index i
void solve(int i) {
  if (dp[i][i]) { // If already computed, return
    return;
  }
  
  dp[i][i] = a[i]; // Base case: first element contributes to DP value

  for (int p = i; p;) { // Loop through possible endpoints
    if (p != i) {
      dp[i][p] = dp[i][p - 1] + 1; // Propagate up the values
    }

    int j = 0;
    // Find next position of value a[i]
    for (int k = p + 1; k <= n; k++) {
      if (a[k] == a[i]) {
        j = k;
        break;
      }
      smx(dp[i][k], dp[i][p]); // Update if needed
    }

    int val = dp[i][p] + 1; // Next required value
    if (!pos[val].empty() && pos[val].back() > p) {
      int idx = *upper_bound(all(pos[val]), p); // Find next occurrence
      solve(idx);
      for (int k = idx; k <= n; k++) {
        smx(dp[i][k], dp[idx][k]); // Merge results from recursive call
      }
    }

    p = j; // Move pointer forward to next occurrence of a[i]
  }
}

void run() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], pos[a[i]].push_back(i); // Record positions of elements
  }

  if (pos[1].empty()) {
    cout << 0 << '\n'; // No valid good subsequence exists
  } else {
    solve(pos[1][0]); // Start solving from first occurrence of 1
    cout << dp[pos[1][0]][n] << '\n';
  }

  // Reset memoization and preprocessing arrays
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      dp[i][j] = 0;
    }
  }
  for (int i = 0; i <= n; i++) {
    pos[i].clear();
  }
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> tests;
  while (tests--) {
    run();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/