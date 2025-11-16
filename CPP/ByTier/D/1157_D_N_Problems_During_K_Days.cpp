// Problem: CF 1157 D - N Problems During K Days
// https://codeforces.com/contest/1157/problem/D

// Problem: Distribute n problems over k days such that:
// 1. Each day at least 1 problem is solved.
// 2. If day i has x problems, then day i+1 has y problems where x < y <= 2*x.
// 3. Total problems solved is exactly n.
//
// Algorithm:
// - Start with a minimal sequence: 1, 2, 3, ..., k (sum = k*(k+1)/2)
// - Distribute remaining problems while maintaining constraints.
// - Greedily add extra problems to the end of the sequence, respecting the constraint.
//
// Time Complexity: O(k)
// Space Complexity: O(k)

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n, d;
  scanf("%lld %lld", &n, &d);
  if (n < d * (d + 1) / 2) {
    puts("NO");
    return 0;
  }
  std::vector<ll> a(d);
  const ll base = d * (d + 1) / 2;
  ll x = (n - base) / d;
  n -= base + x * d;
  for (ll p = 0; p < d; p++) {
    a[p] = x + p + 1;
  }
  for (ll p = d - 1; n > 0 && p > 0; p--) {
    ll diff = 2 * a[p - 1] - a[p];
    diff = (diff < n) ? diff : n;
    a[p] += diff;
    n -= diff;
  }
  if (n <= 0) {
    puts("YES");
    for (ll p = 0; p < d; p++) {
      printf("%lld ", a[p]);
    }
    puts("");
  } else {
    puts("NO");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/