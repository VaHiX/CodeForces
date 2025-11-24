// Problem: CF 2013 B - Battle for Survive
// https://codeforces.com/contest/2013/problem/B

/*
B. Battle for Survive
Time Complexity: O(n) per test case
Space Complexity: O(1)

Algorithm/Techniques:
This problem involves a greedy strategy. We are to simulate a tournament where in each round,
two fighters battle, and one is eliminated while the other's rating decreases by the eliminated
fighter's rating. The goal is to maximize the final rating of the last remaining fighter.

The key insight is that we can treat this as a process where we accumulate ratings with alternating signs.
The last but one fighter contributes positively (we add their value), all others contribute negatively,
since they are eliminated in the order and reduce the score of the ones that follow them.

By processing the array from left to right and applying the sign rule on each element except for the
last two elements, we simulate the best possible outcome of the tournament.

The solution effectively computes:
s = a[0] - a[1] + a[2] - a[3] + ... + a[n-3] - a[n-2] + a[n-1]
but optimized by only adding/subtracting based on index position relative to n-2.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long long s(0); // Initialize sum
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s += (p == n - 2 ? -x : x); // Add x if not second last, otherwise subtract it
    }
    printf("%lld\n", s);
  }
}


// https://github.com/VaHiX/codeForces/