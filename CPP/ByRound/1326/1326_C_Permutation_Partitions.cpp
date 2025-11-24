// Problem: CF 1326 C - Permutation Partitions
// https://codeforces.com/contest/1326/problem/C

/*
C. Permutation Partitions
Algorithm: Greedy approach with combinatorics
Time Complexity: O(n)
Space Complexity: O(1)

The problem asks to partition a permutation of integers 1..n into k disjoint segments,
maximizing the sum of maximum elements in each segment, and counting how many such
optimal partitions exist.

Key insight:
- To maximize the sum of max elements, we want the largest k numbers to be the maxima.
- The optimal strategy is to place these k largest numbers as segment boundaries,
  because placing larger numbers at the start increases their contribution more.
- We compute the maximum possible value by taking sum of k largest numbers (k-th largest to n).
- For counting valid partitions:
  - Identify positions where values >= k can be placed.
  - For each such valid position, we count how many choices there are for placing boundaries,
    using a running product.

The algorithm:
1. Compute max possible value as sum of k largest numbers in permutation.
2. Loop through the array to find valid segment boundaries.
3. Count combinations of ways this maximum can be achieved using modular arithmetic.
*/

#include <cstdio>
typedef long long ll;
int main() {
  const ll MOD = 998244353;
  ll n, k;
  scanf("%lld %lld", &n, &k);
  ll mx = k * n - k * (k - 1) / 2; // Sum of k largest values: n + (n-1) + ... + (n-k+1)
  ll prod(1);
  ll prev(-1);
  for (long p = 0; p < n; p++) {
    ll x;
    scanf("%lld", &x);
    if (x + k <= n) {
      continue; // Skip elements that cannot be maximum of a segment
    }
    prev = (prev >= 0) ? prev : (p - 1); // Initialize previous boundary index
    prod *= (p - prev); // Multiply by number of ways to place next segment boundary
    prod %= MOD;
    prev = p; // Update boundary position
  }
  printf("%lld %lld\n", mx, prod);
  return 0;
}


// https://github.com/VaHiX/codeForces/