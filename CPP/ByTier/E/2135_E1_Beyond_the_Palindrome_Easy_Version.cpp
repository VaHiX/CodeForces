// Problem: CF 2135 E1 - Beyond the Palindrome (Easy Version)
// https://codeforces.com/contest/2135/problem/E1

/*
E1. Beyond the Palindrome (Easy Version)
Algorithm: Preprocessing with modular inverse and prefix sums
Time Complexity: O(MAXN) preprocessing + O(N^2) per test case
Space Complexity: O(MAXN)

The problem asks to count almost-palindromes — binary strings where f(s) = f(reverse(s)).
f(s) removes all "10" substrings simultaneously until none remain.
This is solved using inclusion-exclusion on valid symmetric configurations.
Uses modular arithmetic, precomputed inverses, and prefix sums for efficient range queries.

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

// Increment x by y mod MOD
inline void inc(int &x, int y) {
  x += y;
  if (x >= MOD)
    x -= MOD;
}

// Decrement x by y mod MOD
inline void dec(int &x, int y) {
  x -= y;
  if (x < 0)
    x += MOD;
}

int invv[MAXN], arr[MAXN], pref[MAXN]; // inverse array, recurrence values, prefix sum

// Build modular inverses for all numbers up to n using extended Euclidean algorithm
void buildInv(int n) {
  invv[1] = 1;
  for (int i = 2; i <= n; ++i)
    invv[i] = (ll)(MOD - MOD / i) * invv[MOD % i] % MOD;
}

int n;

// Compute range sum from l to r using prefix sums
inline int rangeSum(int l, int r) {
  l = max(l, 0);
  r = min(r, n);
  if (l > r)
    return 0;
  return l ? subm(pref[r], pref[l - 1]) : pref[r];
}

// Calculates contribution of a specific k and t
int calc(int k, int t) {
  int res = 0;
  int step = k + 2 - t;
  int L0 = (n - k) >> 1;   // L0 calculated as half-distance from left side
  int R0 = (n + k) >> 1;   // R0 calculated as half-distance from right side

  // Traverse forward intervals and accumulate sum
  for (int p = 0; R0 - p * step >= 0; ++p) {
    int L = L0 - p * step;
    int R = R0 - t - p * step;
    inc(res, rangeSum(L, R));
  }

  // Subtract leftmost part contributions
  for (int p = 0; L0 - 1 - p * step >= 0; ++p) {
    int idx = L0 - 1 - p * step;
    dec(res, (ll)(k + 1 - t) * arr[idx] % MOD);
  }

  // Traverse second forward intervals and accumulate sum
  for (int p = 1; L0 + p * step <= n; ++p) {
    int L = L0 + p * step;
    int R = R0 - t + p * step;
    inc(res, rangeSum(L, R));
  }

  // Subtract rightmost part contributions
  for (int p = 0; R0 + 1 - t + p * step <= n; ++p) {
    int idx = R0 + 1 - t + p * step;
    dec(res, (ll)(k + 1 - t) * arr[idx] % MOD);
  }
  
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // Precompute modular inverses
  buildInv(MAXN - 1);

  int T;
  if (!(cin >> T))
    return 0;

  while (T--) {
    cin >> n;
    
    // Recurrence: compute array elements with modular arithmetic
    arr[0] = 1;
    pref[0] = 1;
    for (int i = 1; i <= n; ++i) {
      arr[i] = (ll)arr[i - 1] * invv[i] % MOD * (n - i + 1) % MOD;
      pref[i] = addm(pref[i - 1], arr[i]);
    }

    int ans = 0;
    int x = 0, y = 0;

    // Iterate through all valid k values and accumulate result
    for (int k = 1; k <= n; ++k) {
      if (((n + k) & 1))   // Skip if sum is odd (not valid for symmetric strings)
        continue;
      inc(ans, x);         // Add previous contribution of x

      x = calc(k, 0);
      inc(ans, x);         // Add new value of x

      y = calc(k, 1);
      int twoY = addm(y, y);
      dec(ans, twoY);      // Subtract twice of y to apply inclusion-exclusion correction
    }

    cout << ans << '\n';
  }

  return 0;
}


// https://github.com/VaHiX/codeForces/