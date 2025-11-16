// Problem: CF 2039 F1 - Shohag Loves Counting (Easy Version)
// https://codeforces.com/contest/2039/problem/F1

/*
 * Problem: F1. Shohag Loves Counting (Easy Version)
 *
 * Purpose:
 *   This code counts the number of "good" arrays of arbitrary length where each element is between 1 and m,
 *   such that for an array of length n, f(k) = gcd of max values of all subarrays of length k are all distinct
 *   for k = 1 to n. The result is returned modulo 998244353.
 *
 * Techniques Used:
 *   - Mobius inversion and inclusion-exclusion principles
 *   - Precomputation using factor enumeration and dynamic programming
 *   - Fast modular exponentiation
 *   - Number theory functions like GCD
 *
 * Time Complexity: O(N log N) where N = 1e5
 * Space Complexity: O(N) where N = 1e5
 */

#include <algorithm>
#include <iostream>
#include <stddef.h>
#include <vector>
#define ll long long
#define vt vector
#define pb push_back
#define mp make_pair
using namespace std;

// Fast modular exponentiation
int fastexp(int b, int e, int mod) {
  int ans = 1;
  while (e) {
    if (e & 1)
      ans = (1ll * ans * b) % mod;
    b = (1ll * b * b) % mod;
    e >>= 1;
  }
  return ans;
}

// Euclidean GCD
int gcd(int a, int b) {
  if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}

const int N = 1e5 + 1;
const int mod = 998244353;
const int INF = 2e9;
const ll INFLL = 2e18;

vt<int> factors[N]; // For storing divisors of each number up to N
ll dp_mobius_sum[N], dp_multiple_sum[N], temp[N], ans[N];

void precomp() {
  // Precompute all divisors for numbers from 1 to N
  for (int i = 1; i < N; i++) {
    for (int j = i; j < N; j += i)
      factors[j].pb(i);
  }

  // Main DP computation loop using inversion techniques and factor-based logic
  for (int i = 1; i < N; i++) {
    // Compute temp values based on current state and previous dp values
    for (int j : factors[i]) {
      for (int k : factors[j])
        temp[j] += dp_mobius_sum[k];
      temp[j] -= dp_multiple_sum[j];
      temp[j] *= 2;
      temp[j]++;
      temp[j] %= mod;
      if (temp[j] < 0)
        temp[j] += mod;
      dp_multiple_sum[j] += temp[j];
    }

    // Update answer array with prefix sum
    ans[i] = (temp[i] + ans[i - 1]) % mod;

    // Update mobius-like sums using inversion on factors
    for (int j : factors[i]) {
      for (int k = factors[j].size() - 2; k >= 0; k--)
        temp[j] += (mod - temp[factors[j][k]]);
      temp[j] %= mod;
      dp_mobius_sum[j] += temp[j];
    }

    // Reset temp array for next iteration
    for (int j : factors[i])
      temp[j] = 0;
  }
}

void solve() {
  int n;
  cin >> n;
  cout << ans[n] << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  precomp();
  int t = 1;
  cin >> t;
  for (int tc = 1; tc <= t; tc++) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/