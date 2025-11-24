// Problem: CF 1738 E - Balance Addicts
// https://codeforces.com/contest/1738/problem/E

/*
 * Problem: E. Balance Addicts
 *
 * Purpose: Count the number of ways to partition an integer sequence into
 *          non-empty continuous subsequences such that the sums of these
 *          subsequences form a balanced sequence (palindromic).
 *
 * Algorithm:
 *   - Use prefix sums to determine where to split the sequence.
 *   - For each possible split point, count how many times a prefix sum
 *     and its complement (with respect to total sum) appear.
 *   - Apply combinatorics to compute combinations of valid splits.
 *   - Handle special case for middle element when total sum is even.
 *
 * Time Complexity: O(n log n) per test case due to map operations.
 * Space Complexity: O(n) for prefix sums and maps.
 */

#include <iostream>
#include <map>

using ll = long long;
using namespace std;
const int N = 3e5 + 7, mod = 998244353;
void solve();
ll fc[N], ifc[N], pre[N], r;

// Fast exponentiation function to compute modular inverse
ll ksm(ll x, int y = mod - 2) {
  ll r = 1;
  for (; y; y >>= 1, x = x * x % mod)
    if (y & 1)
      r = r * x % mod;
  return r;
}

// Compute combination C(n, m) using precomputed factorials
ll c(int n, int m) { return fc[n] * ifc[m] % mod * ifc[n - m] % mod; }

int main() {
  ios::sync_with_stdio(0);
  fc[0] = 1;
  for (int i = 1; i < N; i++)
    fc[i] = fc[i - 1] * i % mod;
  ifc[N - 1] = ksm(fc[N - 1]);
  for (int i = N - 2; ~i; --i)
    ifc[i] = ifc[i + 1] * (i + 1) % mod;
  int T;
  cin >> T;
  while (T--)
    solve();
}

void solve() {
  int n;
  cin >> n;
  map<ll, int> mp;
  r = 1;
  for (int i = 1, x; i <= n; i++)
    cin >> x, pre[i] = pre[i - 1] + x, mp[pre[i]]++; // Compute prefix sums and store frequency
  mp[pre[n]]--; // Decrement the total sum as it's already counted once
  for (int i = 1; pre[i] * 2 < pre[n]; i++)
    if (pre[i] != pre[i + 1]) // Check for valid splits
      (r *= c(mp[pre[i]] + mp[pre[n] - pre[i]], mp[pre[i]])) %= mod; // Compute combinations
  if (pre[n] % 2 == 0) // Handle center element in palindrome
    (r *= ksm(2, mp[pre[n] / 2])) %= mod;
  cout << r << '\n';
}


// https://github.com/VaHiX/CodeForces/