// Problem: CF 1774 H - Maximum Permutation
// https://codeforces.com/contest/1774/problem/H

/*
Purpose: This code solves the problem of finding the permutation of cards from 1 to n that maximizes the minimum sum of k consecutive elements in the permutation. It uses a complex algorithm involving specific arrangements of elements based on modular arithmetic and k.

Algorithms/Techniques: 
- Math-based permutation construction
- Modular arithmetic tricks for arranging elements
- Precomputed structures and careful index mapping

Time Complexity: O(n) per test case, as the algorithm performs a fixed number of operations per element.
Space Complexity: O(n), for storing permutation arrays.

*/
#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;
ll t, n, k, seq[100009], ans[100009];

// Fast input reader
inline ll read() {
  ll s = 0, w = 1;
  char ch = getchar();
  while (ch > '9' || ch < '0') {
    if (ch == '-')
      w = -1;
    ch = getchar();
  }
  while (ch <= '9' && ch >= '0')
    s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
  return s * w;
}

// Helper function to map indices
ll f(ll x, ll y, ll k) { return (x - 1) * k + y; }

// Function to generate the sequence based on k parity and n
void get(ll n, ll k) {
  if (!(k & 1)) {
    // If k is even, assign elements in alternating order
    for (ll i = 1; i <= n >> 1; i += 1)
      seq[(i << 1) - 1] = i, seq[i << 1] = n + 1 - i;
    return;
  }
  // For odd k, a more complex mapping is done
  ll m = n / k, cur = 3 * m;
  for (ll i = 4; i <= k; i += 1) {
    if (i & 1) // If i is odd
      for (ll j = m; j >= 1; j -= 1)
        seq[f(j, i, k)] = ++cur;
    else // If i is even
      for (ll j = 1; j <= m; j += 1)
        seq[f(j, i, k)] = ++cur;
  }
  for (ll i = 1; i <= (m + 1 >> 1); i += 1) {
    seq[f(i, 1, k)] = (i << 1) - 1;
    seq[f(i, 2, k)] = ((3 * m + 3) >> 1) - i;
    seq[f(i, 3, k)] = 3 * m - i + 1;
  }
  for (ll i = (m + 3 >> 1); i <= m; i += 1) {
    ll delta = i - (m + 3 >> 1);
    seq[f(i, 1, k)] = ((3 * m + 3) >> 1) + delta;
    seq[f(i, 2, k)] = (m << 1) + 1 + delta;
    seq[f(i, 3, k)] = m - (m & 1) - (delta << 1);
  }
}

// Function to print the final answer and value
void print() {
  ll res = 0, sum = 0;
  for (ll i = 1; i <= k; i += 1)
    sum += ans[i];
  res = sum;
  for (ll i = k + 1; i <= n; i += 1)
    sum += ans[i] - ans[i - k], res = min(res, sum);
  printf("%lld\n", res);
  for (ll i = 1; i <= n; i += 1)
    printf("%lld ", ans[i]);
  puts("");
}

int main() {
  t = read();
  while (t--) {
    n = read(), k = read();
    if (!(n % k)) {
      // When n is divisible by k
      get(n, k);
      for (ll i = 1; i <= n; i += 1)
        ans[i] = seq[i];
      print();
      continue;
    }
    // When n is not divisible by k, handle remainder cases with different logic
    ll q = n / k, r = n % k;
    if (r == 1) {
      ll cur = 0, delta = (q << 1) + 1;
      for (ll i = 1; i <= n; i += k)
        ans[i] = ++cur;
      for (ll i = n - k + 1; i >= 2; i -= k)
        ans[i] = ++cur;
      get(q * (k - 2), k - 2), cur = 0;
      for (ll i = 3; i <= n; i += k)
        for (ll j = i; j <= i + k - 3; j += 1)
          ans[j] = seq[++cur] + delta;
      print();
      continue;
    }
    if (k - r == 1) {
      if (q == 1) {
        ll cur = 0;
        ans[k] = n;
        get(n - 1, k - 1);
        for (ll i = 1; i < k; i += 1)
          ans[i] = seq[++cur];
        for (ll i = k + 1; i <= n; i += 1)
          ans[i] = seq[++cur];
        print();
        continue;
      }
      ll cur = n + 1, delta = q + 1;
      for (ll i = k; i <= n; i += k)
        ans[i] = --cur;
      cur = 0;
      for (ll i = 1; i <= n; i += k)
        ans[i] = ++cur;
      get((q + 1) * (r - 1), r - 1), cur = 0;
      for (ll i = 2; i <= n; i += k)
        for (ll j = i; j <= i + r - 2; j += 1)
          ans[j] = seq[++cur] + delta;
      print();
      continue;
    }
    ll cur = 0, delta = (q + 1) * r;
    get((q + 1) * r, r);
    for (ll i = 1; i <= n; i += k)
      for (ll j = i; j <= i + r - 1; j += 1)
        ans[j] = seq[++cur];
    get(q * (k - r), k - r), cur = 0;
    for (ll i = r + 1; i <= n; i += k)
      for (ll j = i; j <= i + (k - r) - 1; j += 1)
        ans[j] = seq[++cur] + delta;
    print();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/