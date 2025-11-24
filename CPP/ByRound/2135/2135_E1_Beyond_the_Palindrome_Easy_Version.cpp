// Problem: CF 2135 E1 - Beyond the Palindrome (Easy Version)
// https://codeforces.com/contest/2135/problem/E1

/*
E1. Beyond the Palindrome (Easy Version)
time limit per test3 seconds
memory limit per test1024 megabytes

Algorithms/Techniques: 
- Modular arithmetic with precomputed inverses for modular division
- Prefix sums for range queries
- Dynamic Programming and combinatorial counting with inclusion-exclusion principle
- Bit manipulation and binary string processing

Time Complexity: O(N^2) per test case, where N is the input length.
Space Complexity: O(N) for arrays storing prefix sums, inverses, and intermediate values.

For a binary string r, we define f(r) as the result of deleting all 10 substrings simultaneously from r,
until there are no more 10 substrings in r. This function essentially "reduces" the string by removing
pairs of 10 that can be deleted.

A binary string s is called an almost-palindrome if f(s) = f(reverse(s)).

We compute the number of such strings of length n using dynamic programming with modular arithmetic,
utilizing inclusion-exclusion on pairs of indices related to valid combinations under symmetry constraints.
*/

#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;
const int MOD = 998244353;
const int MAXN = 1000000 + 10;

// Modular addition
inline int addm(int x, int y) {
  x += y;
  return x >= MOD ? x - MOD : x;
}

// Modular subtraction
inline int subm(int x, int y) {
  x -= y;
  return x < 0 ? x + MOD : x;
}

// In-place modular addition
inline void inc(int &x, int y) {
  x += y;
  if (x >= MOD)
    x -= MOD;
}

// In-place modular subtraction
inline void dec(int &x, int y) {
  x -= y;
  if (x < 0)
    x += MOD;
}

int invv[MAXN], arr[MAXN], pref[MAXN]; // inverse precomputed values, array for DP, prefix sums

void buildInv(int n) {
  invv[1] = 1;
  for (int i = 2; i <= n; ++i)
    invv[i] = (ll)(MOD - MOD / i) * invv[MOD % i] % MOD; // Compute modular inverse using extended Euclidean algorithm
}

int n;

// Range sum from index l to r using prefix sum technique
inline int rangeSum(int l, int r) {
  l = max(l, 0);
  r = min(r, n);
  if (l > r)
    return 0;
  return l ? subm(pref[r], pref[l - 1]) : pref[r];
}

// Calculate contributions for a given k and t
int calc(int k, int t) {
  int res = 0;
  int step = k + 2 - t;        // Step size for index jumps
  int L0 = (n - k) >> 1;       // Base left pointer
  int R0 = (n + k) >> 1;       // Base right pointer

  // Iterate through valid intervals on the left side
  for (int p = 0; R0 - p * step >= 0; ++p) {
    int L = L0 - p * step;
    int R = R0 - t - p * step;
    inc(res, rangeSum(L, R));
  }

  // Subtract invalid values from left side (before base)
  for (int p = 0; L0 - 1 - p * step >= 0; ++p) {
    int idx = L0 - 1 - p * step;
    dec(res, (ll)(k + 1 - t) * arr[idx] % MOD);
  }

  // Iterate through valid intervals on the right side
  for (int p = 1; L0 + p * step <= n; ++p) {
    int L = L0 + p * step;
    int R = R0 - t + p * step;
    inc(res, rangeSum(L, R));
  }

  // Subtract invalid values from right side (after base)
  for (int p = 0; R0 + 1 - t + p * step <= n; ++p) {
    int idx = R0 + 1 - t + p * step;
    dec(res, (ll)(k + 1 - t) * arr[idx] % MOD);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  buildInv(MAXN - 1); // Precompute modular inverses up to MAXN

  int T;
  if (!(cin >> T))
    return 0;

  while (T--) {
    cin >> n;

    arr[0] = 1;                    // Base case for sequence
    pref[0] = 1;

    for (int i = 1; i <= n; ++i) {
      arr[i] = (ll)arr[i - 1] * invv[i] % MOD * (n - i + 1) % MOD; // Compute DP terms using inverse mod
      pref[i] = addm(pref[i - 1], arr[i]);                        // Build prefix sums
    }

    int ans = 0;
    int x = 0, y = 0;
    for (int k = 1; k <= n; ++k) {
      if (((n + k) & 1)) // Skip odd cases due to symmetry constraints
        continue;
      inc(ans, x);
      x = calc(k, 0);     // Compute contribution for t=0
      inc(ans, x);
      y = calc(k, 1);     // Compute contribution for t=1
      int twoY = addm(y, y);
      dec(ans, twoY);    // Apply inclusion-exclusion: subtract twice of y to correct overcounting
    }
    cout << ans << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/