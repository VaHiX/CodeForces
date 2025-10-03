// Problem: CF 2061 C - Kevin and Puzzle
// https://codeforces.com/contest/2061/problem/C

/*
C. Kevin and Puzzle
Algorithms/Techniques: Dynamic Programming with state tracking based on validity of liars and honesty constraints.

Time Complexity: O(n) per test case
Space Complexity: O(n) for the DP array and input storage

The problem involves determining how many valid configurations exist such that:
- Each person claims there are 'a[i]' liars to their left.
- Honest people always tell the truth.
- Liars may lie or tell the truth, so their statements are unreliable.
- No two liars can be adjacent.

We use dynamic programming where f[p] represents the number of ways to assign honesty/liar status to the first p people such that:
- The constraints up to position p are satisfied.
- We track the valid arrangements by checking if a person's claim about liars to their left is consistent with previous assignments.
*/

#include <cstdio>
#include <vector>
int main() {
  const long MOD = 998244353;
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n + 1), f(n + 1, 0);  // a stores input, f is DP array
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &a[p]);
    }
    f[0] = 1;  // Base case: one way to arrange zero people
    for (long p = 1; p <= n; p++) {
      // If the current person's claim is consistent with previous setup,
      // we can add ways where they are honest (a[p-1] == a[p])
      // or consider them part of a valid chain where they follow a prior person who said truthfully
      f[p] = (a[p - 1] == a[p]) * f[p - 1] +
             (p > 1 && a[p - 2] + 1 == a[p]) * f[p - 2];
      f[p] %= MOD;
    }
    long ans = (f[n - 1] + f[n]) % MOD;  // Final answer is sum of last two states
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/