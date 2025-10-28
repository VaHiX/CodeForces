// Problem: CF 1915 F - Greetings
// https://codeforces.com/contest/1915/problem/F

/*
F. Greetings
Algorithm: Merge Sort-based Inversion Count
Time Complexity: O(n log n) per test case
Space Complexity: O(n) per test case

This problem computes the number of intersections (greetings) between intervals [a_i, b_i].
Each person starts at 'a_i' and moves to 'b_i'. Two people greet if their paths intersect,
which happens when one starts before another and ends after the other starts.
We use coordinate compression and then count inversions in the compressed array,
using a modified merge sort algorithm.

*/
#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;
std::pair<std::vector<ll>, ll> mergesort(std::vector<ll> w) {
  const ll n = w.size();
  if (n <= 1) {
    return std::make_pair(w, 0);
  }
  ll xsz = n / 2;
  ll ysz = n - n / 2;
  std::vector<ll> x(xsz);
  for (ll p = 0; p < xsz; p++) {
    x[p] = w[p];
  }
  std::vector<ll> y(ysz);
  for (ll p = 0; p < ysz; p++) {
    y[p] = w[xsz + p];
  }
  std::pair<std::vector<ll>, ll> rmx, rmy;
  rmx = mergesort(x);   // Recursively sort left half
  x = rmx.first;
  rmy = mergesort(y);   // Recursively sort right half
  y = rmy.first;
  ll a(0), b(0), cnt(0);
  std::vector<ll> out(n);
  for (ll p = 0; p < n; p++) {
    if (a < xsz && b < ysz) {
      if (y[b] < x[a]) {
        out[p] = y[b++];
        cnt += (xsz - a); // Count inversions: all elements in left array after 'a' are greater
      } else if (x[a] < y[b]) {
        out[p] = x[a++];
      }
    } else if (a == xsz) {
      out[p] = y[b++];
      cnt += (xsz - a); // All remaining elements in left array contribute to inversion count
    } else if (b == ysz) {
      out[p] = x[a++];  // Just copy from left array
    }
  }
  return std::make_pair(out, rmx.second + rmy.second + cnt); // Return merged array and inversion count
}
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<std::pair<ll, ll>> v(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld %lld", &v[p].first, &v[p].second);
    }
    sort(v.begin(), v.end());
    std::vector<ll> w(n);
    for (ll p = 0; p < n; p++) {
      w[p] = v[p].second;
    }
    printf("%lld\n", mergesort(w).second); // Output inversion count which equals number of greetings
  }
}


// https://github.com/VaHiX/codeForces/