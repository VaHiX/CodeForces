// Problem: CF 1419 C - Killjoy
// https://codeforces.com/contest/1419/problem/C

/*
C. Killjoy
Algorithms/Techniques: Simulation, Greedy
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem involves infecting all accounts on Codeforces with a virus originating from Killjoy's account.
Each contest allows changing ratings such that the sum of changes is zero. An infected account can infect others if their ratings are equal.
We determine the minimal number of contests needed to infect all accounts.

Key observations:
- If all accounts have the same rating as Killjoy (x), no contests needed (0).
- If any account has rating x, we need at least 1 contest unless sum of differences is zero.
- If sum of differences is not zero and no account has rating x, we need 2 contests.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    long cnt(0), sum(0); // cnt counts how many accounts have rating x; sum tracks total difference from x
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      cnt += (a == x); // Increment if account has the same rating as Killjoy
      sum += (a - x);  // Accumulate difference from Killjoy's rating
    }
    if (cnt == n) {
      puts("0");       // All accounts are already infected (same rating as Killjoy)
    } else if (cnt > 0 || sum == 0) {
      puts("1");       // At least one account can be infected in 1 contest, or we don't need more
    } else {
      puts("2");       // Requires two contests to spread the infection
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/