// Problem: CF 1061 C - Multiplicity
// https://codeforces.com/contest/1061/problem/C

/*
C. Multiplicity
time limit per test
3 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Problem Description:
Given an integer array a_1, a_2, ..., a_n, find the number of "good" subsequences modulo 10^9 + 7.
A subsequence b_1, b_2, ..., b_k is called good if it is not empty and for every i (1 <= i <= k), b_i is divisible by i.

Algorithm:
The solution uses dynamic programming with a vector f where f[i] represents the number of good subsequences ending with length i.
For each element x in the array, we iterate through its divisors in descending order to update the dp states properly.

Time Complexity: O(n * sqrt(max(a)) + n * log(max(a)))
Space Complexity: O(sqrt(max(a)))

*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  const ll MOD = 1e9 + 7;
  ll n;
  scanf("%lld", &n);
  std::vector<ll> f(1, 1); // Initialize with 1 for empty prefix
  for (ll k = 0; k < n; k++) {
    ll x;
    scanf("%lld", &x);
    std::vector<ll> divs;
    for (ll u = 1; u * u <= x; u++) {
      if (x % u) {
        continue;
      }
      divs.push_back(u);
      if (x != u * u) {
        divs.push_back(x / u);
      }
    }
    sort(divs.rbegin(), divs.rend()); // Sort divisors in descending order
    for (ll r : divs) {
      if (r > f.size()) {
        continue; // Skip if divisor exceeds current size of f
      } else if (r == f.size()) {
        f.push_back(f.back()); // Extend f with the same value as last element
      } else {
        f[r] += f[r - 1]; // Add subsequences ending at r-1 to those ending at r
      }
      f[r] %= MOD; // Keep values within modulo
    }
  }
  ll total(0);
  for (ll p = 1; p < f.size(); p++) {
    total = (total + f[p]) % MOD; // Sum up all valid subsequences
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/codeForces/