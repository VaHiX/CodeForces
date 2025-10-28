// Problem: CF 1891 B - Deja Vu
// https://codeforces.com/contest/1891/problem/B

/*
B. Deja Vu
Algorithms/Techniques: Simulation with preprocessing of queries
Time Complexity: O(n * q + n * log(max(a[i]))) where n*q is for processing queries and n*log(max(a[i])) for applying modifications.
Space Complexity: O(q + n) where q is for storing query results and n for the result array.

Problem Description:
You are given an array 'a' of length n, consisting of positive integers, and an array 'x' of length q, also consisting of positive integers.
There are q modification queries. On the i-th modification, for each j (1≤j≤n), such that a[j] is divisible by 2^x[i], you add 2^(x[i]-1) to a[j].
Note that x[i] (1≤x[i]≤30) is a positive integer not exceeding 30.
After all modification queries, output the final array.

Input:
- The first line contains t (1≤t≤10^4) — the number of test cases.
- For each test case:
   - First line: n and q (1≤n,q≤10^5)
   - Second line: n integers a[1], ..., a[n] (1≤a[i]≤10^9)
   - Third line: q integers x[1], ..., x[q] (1≤x[i]≤30)

Output:
For each test case, output the array after all modifications.
*/

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, q;
    scanf("%lld %lld", &n, &q);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    std::vector<ll> b; // Stores unique query values in decreasing order
    for (ll p = 0; p < q; p++) {
      ll x;
      scanf("%lld", &x);
      if (b.empty() || b.back() > x) { // Only add if not already present or larger than last element
        b.push_back(x);
      }
    }
    std::vector<ll> w(b.size()); // Precompute the value to add for each query
    ll prev(0);
    for (ll p = w.size() - 1; p >= 0; p--) {
      w[p] = (1 << (b[p] - 1)) + prev; // w[p] stores cumulative effect of all higher powers
      prev = w[p];
    }
    for (ll p = 0; p < a.size(); p++) {
      for (ll u = 0; u < b.size(); u++) {
        if (a[p] % (1 << b[u]) == 0) { // Check divisibility by 2^b[u]
          a[p] += w[u]; // Apply the precomputed increment
          break; // Once applied, no need to process further larger powers
        }
      }
    }
    for (ll p = 0; p < n; p++) {
      printf("%lld ", a[p]);
    }
    puts(""); // Print new line after each test case
  }
}


// https://github.com/VaHiX/codeForces/