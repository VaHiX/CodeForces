// Problem: CF 2041 H - Sheet Music
// https://codeforces.com/contest/2041/problem/H

// Problem: H. Sheet Music
// Task: Count the number of distinct songs of length n with notes in range [1,k], 
//       where two songs are equivalent if their adjacent pitch relationships are the same.
//       This problem uses dynamic programming with combinatorics and modular arithmetic.
//
// Algorithms/Techniques:
// - Dynamic Programming (DP)
// - Precomputed factorials and inverse factorials for combinations
// - Fast exponentiation for modular inverse
// - Modular arithmetic to avoid overflow
//
// Time Complexity: O(n)
// Space Complexity: O(n)

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
constexpr const int MD = 998'244'353;
constexpr const int mxN = 1'000'005;
int pw(int a, int b) {
  int ret = 1;
  while (b) {
    if (b & 1)
      ret = 1ll * ret * a % MD;
    a = 1ll * a * a % MD;
    b >>= 1;
  }
  return ret;
}
int F[mxN], iF[mxN];
int C(int n, int k) { return 1ll * F[n] * iF[k] % MD * iF[n - k] % MD; }
int main() {
  F[0] = 1;
  for (int i = 1; i < mxN; ++i)
    F[i] = 1ll * F[i - 1] * i % MD;
  iF[mxN - 1] = pw(F[mxN - 1], MD - 2);
  for (int i = mxN - 1; i; --i)
    iF[i - 1] = 1ll * iF[i] * i % MD;
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  vector<int> wh(n, 0); // Stores contribution of each position
  int ans = 1;          // Base case: one way to form sequence with no transitions
  int cu = 1;           // Current count of valid sequences (starts at 1 for base)
  if (k < n)
    wh[k] = 2;          // Special case when k < n, mark transition point
  for (int i = 1; i < n; ++i) {
    // Double current count and subtract contribution from previous state
    cu = (1ll * (cu << 1) - wh[i] + MD) % MD;
    if (i + k < n)
      wh[i + k] = cu;   // Update transition effect for future states
    ans = (ans + 1ll * C(n - 1, i) * cu) % MD; // Add weighted contribution to result
  }
  cout << ans << '\n';
}


// https://github.com/VaHiX/codeForces/