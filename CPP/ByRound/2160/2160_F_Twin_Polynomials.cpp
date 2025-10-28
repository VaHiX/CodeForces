// Problem: CF 2160 F - Twin Polynomials
// https://codeforces.com/contest/2160/problem/F

/*
 * Problem: Twin Polynomials
 * 
 * Purpose: 
 *   Given a polynomial f(x) of degree n with some coefficients determined,
 *   determine how many "cool" polynomials can be formed by filling in
 *   the undetermined coefficients. A cool polynomial satisfies f(x) = g(x),
 *   where g(x) is the twin polynomial defined as g(x) = sum_{i=0}^{n} i * x^{a_i}.
 * 
 * Approach:
 *   1. Parse input to understand which coefficients are given or undetermined.
 *   2. Use the constraint f(x) == g(x) to derive a relationship between coefficients.
 *   3. For each undetermined coefficient, if it's linked to other undetermined ones
 *      through this relation, they must be equal.
 *   4. Count valid ways to assign values to undetermined coefficients using dynamic programming.
 *   5. Apply modular arithmetic to handle large numbers.
 * 
 * Time Complexity: O(n)
 *   - Linear scan to process coefficients
 *   - Dynamic programming for counting valid assignments
 * 
 * Space Complexity: O(n)
 *   - Storage for input, processing arrays, and DP table
 * 
 * Algorithms/Techniques:
 *   - Graph theory (detecting cycles and components)
 *   - Dynamic Programming for combinatorial counting
 *   - Modular arithmetic for large number handling
 * 
 * Note: The core insight from the constraint f(x) = g(x) is that for a valid polynomial,
 *       if we have a_{i} = j, then we must have a_{j} = i (or both are undetermined
 *       and can be chosen freely).
 */

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define x first
#define n second
#define INF1 1000000007
#define int long long
#define mod 1000000007
void nie() { cout << "0\n"; }
void sol() {
  int n;
  cin >> n;
  vector<int> v(n + 1);
  for (auto &x : v)
    cin >> x;
  for (int i = 0; i < n + 1; i++) {
    if (v[i] < 1) {
      continue;
    }
    if (v[i] > n)
      return nie();
    if (v[i] == i)
      continue;
    if (v[v[i]] == -1)
      v[v[i]] = i;
    if (v[v[i]] != i)
      return nie();
  }
  int m = 0;
  for (int i = 0; i < n + 1; i++) {
    if (v[i] == -1) {
      m++;
      continue;
    }
  }
  vector<int> dp = {0, 1};
  for (int i = 2; i <= m; i++) {
    dp.push_back((2 * dp[i - 1] + (i - 2) * dp[i - 2]) % mod);
  }
  if (m < 2) {
    cout << dp[m] << '\n';
    return;
  }
  if (v[n] == -1 && v[0] == -1)
    cout << (dp[m - 1] + (m - 2) * dp[m - 2]) % mod << '\n';
  else
    cout << dp[m] << '\n';
}
int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    sol();
}


// https://github.com/VaHiX/CodeForces/