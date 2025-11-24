// Problem: CF 1924 D - Balanced Subsequences
// https://codeforces.com/contest/1924/problem/D

/*
 * Problem: Count the number of bracket sequences with n '(' and m ')' such that
 * the longest balanced subsequence has length 2*k.
 *
 * Algorithm:
 * - The idea is to use the inclusion-exclusion principle.
 * - We calculate the total number of ways to arrange n '(' and m ')' brackets,
 *   then subtract the cases where the maximum balanced subsequence is less than 2*k.
 * - This reduces to computing C(n + m, k) - C(n + m, k - 1), which represents
 *   valid sequences that have a longest balanced subsequence of exactly 2*k.
 *
 * Time Complexity: O(N + T), where N = 4114 (precomputed factorials) and T is number of test cases.
 * Space Complexity: O(N), due to precomputed arrays for factorials and inverse factorials.
 */

#include <algorithm>
#include <iostream>

#define int long long
using namespace std;
const int N = 4114; // Maximum size for precomputation
const int mod = 1e9 + 7; // Modulo value
int T, n, m, k;
int jc[N + 10], inv[N + 10]; // Arrays for factorial and inverse factorial

// Fast exponentiation: computes (a^b) % mod
int qp(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1)
      (res *= a) %= mod;
    (a *= a) %= mod;
    b >>= 1;
  }
  return res;
}

// Precompute factorials and inverse factorials up to N
void pre() {
  jc[0] = 1;
  for (int i = 1; i <= N; i = i + 1)
    jc[i] = jc[i - 1] * i % mod;
  inv[N] = qp(jc[N], mod - 2);
  for (int i = N; i >= 1; i = i - 1)
    inv[i - 1] = inv[i] * i % mod;
}

// Compute combination C(n, m) = n! / (m! * (n - m)!)
int C(int n, int m) { return jc[n] * inv[m] % mod * inv[n - m] % mod; }

signed main() {
  pre(); // Precompute factorials
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> m >> k;
    if (k > min(n, m))
      cout << "0\n"; // No valid sequence if k exceeds min(n, m)
    else
      // The difference gives the count of sequences with longest balanced subsequence of length 2*k
      cout << (C(n + m, k) - C(n + m, k - 1) + mod) % mod << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/