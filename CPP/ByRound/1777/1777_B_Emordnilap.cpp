// Problem: CF 1777 B - Emordnilap
// https://codeforces.com/contest/1777/problem/B

/*
B. Emordnilap
Given a permutation p of length n, we create an array a by concatenating p with its reverse.
The beauty of p is the number of inversions in a.
We need to find the sum of beauties for all n! permutations modulo 10^9 + 7.

Algorithms/Techniques: Mathematical analysis, modular arithmetic, combinatorics

Time complexity: O(n) per test case
Space complexity: O(1)

The key insight is that for each pair of positions (i, j) in the concatenated array,
we can compute how many times a[i] > a[j] across all permutations.
Since half of the pairs will be inverted in expectation due to symmetry,
the formula simplifies to n * (n-1) * (2*n-1) / 6 when considering all valid inversions.

However, the actual formula derived for this problem is:
Sum = n! * (n * (n - 1) / 2) * (n + 1) / 2
But to compute it efficiently and avoid overflows, we use modular arithmetic.
We simplify as follows in code:
- First term: n * (n - 1) % MOD gives the base for inversion count.
- Multiply by factorial of n to account for all permutations.
*/
#include <cstdio>
typedef long long ll;

int main() {
  const ll MOD = 1000000007;
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    // Calculate base value for inversions in concatenated array
    ll cnt((n * (n - 1)) % MOD);
    // Multiply by factorial of n, computing modulo at each step to prevent overflow
    for (long p = 1; p <= n; p++) {
      cnt *= p;
      cnt %= MOD;
    }
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/