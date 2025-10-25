// Problem: CF 1906 H - Twin Friends
// https://codeforces.com/contest/1906/problem/H

/*
 * Problem: H. Twin Friends
 * Algorithm: Dynamic Programming with Combinatorics
 * 
 * Purpose:
 *   Given two strings A and B (lengths N and M respectively, where N <= M),
 *   we need to count the number of valid pairs (A', B') where:
 *   - A' is a permutation of A
 *   - B' is obtained by removing exactly (M - N) characters from any permutation of B
 *   - For each i, B'[i] is either A'[i] or the next letter in alphabet after A'[i]
 * 
 * Time Complexity: O(N * 26) = O(N)
 * Space Complexity: O(26 * M) = O(M)
 * 
 * Techniques:
 *   - Precomputed factorials and inverse factorials for combinations
 *   - Dynamic Programming with states representing how many letters of type i can be used
 *   - Modular arithmetic to prevent overflow
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
constexpr int mod = 998244353;

// Function to perform modular addition
void mpl(int &x, int y) {
  x += y;
  if (x >= mod)
    x -= mod;
}

// Precompute factorials and inverse factorials for combinations
long long fac[200200], finv[200200], inv[200200];
void COMinit() {
  fac[0] = fac[1] = finv[0] = finv[1] = inv[1] = 1;
  for (int i = 2; i < 200200; i++) {
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = mod - inv[mod % i] * (mod / i) % mod;
    finv[i] = finv[i - 1] * inv[i] % mod;
  }
}

// Function to compute combination C(n, k)
long long COM(int n, int k) {
  if (n < k)
    return 0;
  if (n < 0 || k < 0)
    return 0;
  return fac[n] * (finv[k] * finv[n - k] % mod) % mod;
}

// DP table: dp[i][j] represents number of ways to assign j letters of type i
int dp[27][200200];

int main() {
  COMinit(); // Initialize factorials and inverse factorials
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int N, M;
  cin >> N >> M;
  string A, B;
  cin >> A >> B;
  
  // Count frequency of each character in both strings
  vector<int> a(26), b(26);
  for (int i = 0; i < N; i++)
    a[A[i] - 'A']++;
  for (int i = 0; i < M; i++)
    b[B[i] - 'A']++;
  
  // Calculate the number of ways to select permutations of A from all letters in A
  int res = N;
  int sum = 1;
  for (int i = 0; i < 26; i++) {
    sum = 1ll * sum * COM(res, a[i]) % mod;
    res -= a[i];
  }
  
  // Dynamic Programming to count valid ways to assign characters
  for (int i = 0; i < 26; i++) {
    if (i == 0) {
      // Base case: for first character type, all possibilities are valid
      for (int j = 0; j <= min(a[i], b[i]); j++) {
        mpl(dp[i][j], 1);
      }
    } else {
      // Create temporary array to store transitions
      vector<int> tmp(b[i] + 1);
      for (int j = 0; j <= a[i - 1]; j++) {
        if (a[i - 1] - j <= b[i])
          tmp[a[i - 1] - j] = 1ll * COM(a[i - 1], j) * dp[i - 1][j] % mod;
      }

      // Update DP table for current character based on previous state
      for (int j = 0; j <= b[i]; j++) {
        mpl(dp[i][0], tmp[j]);
        mpl(dp[i][min(a[i], b[i] - j) + 1], mod - tmp[j]);
      }

      // Prefix sum to get cumulative probabilities
      for (int j = 0; j <= b[i]; j++) {
        mpl(dp[i][j + 1], dp[i][j]);
      }
    }
  }

  // Output final result: multiply the number of valid assignments with sum
  cout << 1ll * dp[25][a[25]] * sum % mod << "\n";
}


// https://github.com/VaHiX/CodeForces/