// Problem: CF 2086 D - Even String
// https://codeforces.com/contest/2086/problem/D

/*
D. Even String
Algorithm: Combinatorics + Dynamic Programming
Time Complexity: O(N) per test case, where N is the sum of c[i]
Space Complexity: O(N) for precomputed factorials and DP array

The problem requires constructing strings such that all occurrences of the same character have even differences in indices.
This means characters at even positions can only be matched with other characters at even positions,
and same for odd positions.

Approach:
1. Precompute factorials and their modular inverses up to 5e5.
2. For each test case:
   - Calculate total length n as sum of c[i].
   - Compute total arrangements using multinomial coefficients.
   - Use DP to count valid partitions of characters into even/odd positions.
   - Combine results to get final answer.

*/
#include <iostream>

using namespace std;
const int N = 5e5 + 5;
const int M = 27;
const int mod = 998244353;
#define int long long
int c[M], f[N], facny[N], fac[N];

// Fast exponentiation for modular inverse
int qpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) {
      res = (res * a) % mod;
    }
    a = (a * a) % mod, b >>= 1;
  }
  return res;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  // Precompute factorials
  fac[0] = facny[0] = 1;
  for (int i = 1; i < N; i++) {
    fac[i] = (fac[i - 1] * i) % mod;
  }
  
  // Precompute inverse factorials
  facny[N - 1] = qpow(fac[N - 1], mod - 2);
  for (int i = N - 2; i >= 1; i--) {
    facny[i] = (facny[i + 1] * (i + 1)) % mod;
  }
  
  int T;
  cin >> T;
  while (T--) {
    int n = 0, ans = 1;
    
    // Read character counts and compute multinomial coefficient
    for (int i = 1; i <= 26; i++) {
      cin >> c[i];
      n += c[i], ans = (ans * facny[c[i]]) % mod;
    }
    
    // Multiply by arrangements of half length elements (even/odd positions)
    ans = (ans * fac[n / 2] % mod * fac[(n + 1) / 2]) % mod;
    
    // Reset DP array
    for (int i = 1; i <= n / 2; i++)
      f[i] = 0;
    f[0] = 1;
    
    // Dynamic Programming: count valid ways to partition characters
    for (int i = 1; i <= 26; i++) {
      if (c[i] == 0) {
        continue;
      }
      for (int j = n / 2; j >= c[i]; j--) {
        f[j] += f[j - c[i]];  // Add ways to place this character count
      }
    }
    
    cout << (ans * f[n / 2]) % mod << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/