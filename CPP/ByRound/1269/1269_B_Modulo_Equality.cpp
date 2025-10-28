// Problem: CF 1269 B - Modulo Equality
// https://codeforces.com/contest/1269/problem/B

/*
B. Modulo Equality
time limit per test
3 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Task:
Find the smallest non-negative integer x such that (a[i] + x) mod m can be rearranged to match b.

Algorithms/Techniques:
- Brute force over possible values of x (in this case, we iterate through all possible difference values)
- Sorting and comparison to check if arrays can be matched after transformation
- Using modular arithmetic to compute differences

Time Complexity: O(n^2 * log n)
Space Complexity: O(n)

*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

// Function to check if array a, after adding 'add' and taking mod 'mod', can be sorted to match array b
bool check(std::vector<ll> x, const std::vector<ll> &y, const ll &add,
           const ll &mod) {
  for (ll p = 0; p < x.size(); p++) {
    x[p] += add;
    x[p] %= mod;
  }
  sort(x.begin(), x.end());
  for (ll p = 0; p < x.size(); p++) {
    if (x[p] != y[p]) {
      return false;
    }
  }
  return true;
}

int main() {
  ll n, m;
  scanf("%lld %lld", &n, &m);
  std::vector<ll> a(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  std::vector<ll> b(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &b[p]);
  }
  sort(b.begin(), b.end());
  ll res(m + 1); // Initialize result to a value larger than possible x
  for (ll p = 0; p < n; p++) {
    // Compute difference that would make a[p] equal to b[0] after adding x and mod m
    ll diff = (2 * m + b[0] - a[p]) % m;
    if (diff > res) {
      continue; // Skip if this diff is already larger than current best
    }
    if (check(a, b, diff, m)) {
      res = diff; // Update result if valid
    }
  }
  printf("%lld\n", res);
  return 0;
}


// https://github.com/VaHiX/codeForces/