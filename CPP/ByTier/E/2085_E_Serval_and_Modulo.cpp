// Problem: CF 2085 E - Serval and Modulo
// https://codeforces.com/contest/2085/problem/E

/*
E. Serval and Modulo

This problem involves finding a magic number k such that when each element of array `a` is taken modulo k,
the resulting array (after shuffling) matches the given array `b`.

Key Idea:
- We know b is a shuffled version of [a[1]%k, a[2]%k,..., a[n]%k]
- Let s = sum(a[i]) - sum(b[i]). For any valid k, s must be divisible by k (as all elements of a are reduced modulo k).
- So we test divisors of s to find potential k values.
- Additionally, since c[i] = count of i in b, for each element of a, we can check if a[i]%k exists in the counts.

Approach:
1. For each test case, calculate s = sum(a[i]) - sum(b[i]).
2. Find all divisors up to sqrt(s) and test both d and s/d.
3. Use a function `chk(x)` which verifies if x is valid:
    - Ensures x > max(b)
    - Compares frequencies of mod values in a with those in b
4. Special case: If s == 0, we need to check if all elements of a are equal to corresponding elements modulo k; for that, we directly try k = N.

Time Complexity: O(n * sqrt(s)) per test case where s = sum(a) - sum(b)
Space Complexity: O(N) where N is max constraint value (1e6 + 2)

*/

#include <assert.h>
#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;
const ll N = 1e6 + 2;
ll a[N], b[N], c[N], sc[N], n, mxB;

// Function to check if k = x is valid
bool chk(ll x) {
  if (x <= mxB || x > N) // If x is small or too large, skip
    return 0;
  bool ok = 1;
  for (int i = 1; i <= n; ++i)
    if (--c[a[i] % x] < 0) // Decrease count of modulus result from a[i]
      ok = 0; // If count goes negative, invalid
  for (int i = 1; i <= n; ++i)
    c[a[i] % x] = 0; // Reset counts after use
  for (int i = 1; i <= n; ++i)
    c[b[i]] = sc[b[i]]; // Restore original counts from sc
  return ok;
}

void solve() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 1; i <= n; ++i)
    cin >> b[i];
  ll s = 0;
  for (int i = 1; i <= n; ++i)
    s += a[i] - b[i], ++c[b[i]]; // Compute difference and count frequencies in b
  for (int i = 1; i <= n; ++i)
    sc[b[i]] = c[b[i]];
  mxB = *max_element(b + 1, b + n + 1); // Max element in b
  ll ans = -1;
  for (ll x = 1; x * x <= s; ++x) { // Loop through divisors of s
    if (s % x)
      continue;
    if (chk(x)) {
      ans = x;
      break;
    }
    if (chk(s / x)) {
      ans = s / x;
      break;
    }
  }
  assert(ans != 1 || !mxB); // Special edge case handling
  cout << (chk(N) ? N : ans) << '\n'; // If no answer found, check large value N as fallback
  for (int i = 1; i <= n; ++i)
    c[b[i]] = sc[b[i]] = 0; // Clear arrays after use
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  ll T;
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/codeForces/