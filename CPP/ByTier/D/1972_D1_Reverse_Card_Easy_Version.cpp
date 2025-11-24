// Problem: CF 1972 D1 - Reverse Card (Easy Version)
// https://codeforces.com/contest/1972/problem/D1

#include <cstdio>
typedef long long ll;

/*
D1. Reverse Card (Easy Version)
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

The problem asks to count the number of ordered pairs (a, b) such that:
1 <= a <= n, 1 <= b <= m
and (a + b) is divisible by b * gcd(a, b).

This can be rewritten as: (a + b) % (b * gcd(a, b)) == 0.
To simplify the logic further, we observe that we can iterate over all possible values of b from 1 to m,
and for each b, count how many valid a values exist under the constraint.

In this approach:
- For each b in [1, m]
- We compute sum of (n + b) / (b * b) for a given range of b
- But we actually iterate over p from 1 to m where p represents possible gcd values.
- The formula (n + p) / (p * p) gives us the number of valid pairs for current p.

Algorithm:
We loop from p = 1 to m, and compute res += (n + p) / (p * p). This is based on transforming the gcd condition
into a simplified counting formula in terms of divisors.

Time Complexity: O(m)
Space Complexity: O(1)

*/

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    ll res(-1); // Initialize result to -1 since we add first iteration
    for (ll p = 1; p <= m; p++) {
      res += (n + p) / (p * p); // Add count of valid a's for current b = p
    }
    printf("%lld\n", res);
  }
}

// https://github.com/VaHiX/codeForces/