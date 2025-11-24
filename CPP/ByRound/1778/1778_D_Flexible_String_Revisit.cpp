// Problem: CF 1778 D - Flexible String Revisit
// https://codeforces.com/contest/1778/problem/D

/*
 * Problem: Flexible String Revisit
 * Algorithm: Dynamic Programming with Inclusion-Exclusion Principle
 * 
 * Approach:
 * - This problem models the expected number of steps to make two binary strings equal
 *   by randomly flipping one bit of string 'a' at each step.
 * - The key insight is to define dp[i] as the expected number of steps to reduce the
 *   number of mismatched bits from i to 0.
 * - Using linearity of expectation and recurrence relations, we derive:
 *   x[i] = (n - i) / n * (1 + x[i+1]) + i / n * (1 + x[i-1])
 *   Simplified form leads to recurrence:
 *   x[i+1] = (n * (x[i] - i * x[i-1] / n - 1) ) / (n - i)
 * - For final answer, we use x[cnt] where cnt is number of matching bits initially.
 * 
 * Time Complexity: O(n) per test case, overall O(sum(n))
 * Space Complexity: O(n)
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define fast_io ios::sync_with_stdio(0), cin.tie(0)
typedef long long ll;
const int MOD = 998244353, N = 1e6 + 1;
vector<ll> inv(N);  // Precomputed modular inverses

// Precompute modular inverses using extended Euclidean algorithm
void make() {
  inv[1] = 1;
  for (int i = 2; i < N; i++)
    inv[i] = (MOD + (-1 * (MOD / i) * inv[MOD % i]) % MOD) % MOD;
}

int main() {
  fast_io;
  make();
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    
    // Count number of matching bits
    int cnt = 0;
    for (int i = 0; i < n; i++)
      if (s[i] == t[i])  // If characters match
        cnt++;
    
    // DP array to store expected steps to make 'i' mismatches become 0
    vector<ll> x(n + 1);
    x[0] = 1;  // Base case: if there is no mismatch, steps needed = 0
    x[1] = 0;  // One mismatch, so we need exactly one step with probability 1
    
    // Fill the DP table using recurrence relation
    for (int i = 1; i < n; i++) {
      // Compute x[i+1] based on previous values
      x[i + 1] = ((x[i] - ((i * x[i - 1]) % MOD) * inv[n] - 1) % MOD);
      x[i + 1] = (((x[i + 1] * n) % MOD) * inv[n - i]) % MOD;
    }
    
    // Final answer is calculated from x[n] and x[cnt]
    ll a = -x[n];
    ll ans = (a + x[cnt]) % MOD;
    ans = (MOD + ans) % MOD;
    cout << ans << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/