// Problem: CF 1659 C - Line Empire
// https://codeforces.com/contest/1659/problem/C

/*
C. Line Empire
Algorithm: Dynamic Programming with Prefix Sums
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

Problem:
We have a number line with n kingdoms at positions x_1 < x_2 < ... < x_n.
The capital starts at 0. Two operations:
1. Move capital from current position c1 to kingdom at position c2, cost = a * |c1 - c2|
2. Conquer an unconquered kingdom at position c2 from capital at c1, cost = b * |c1 - c2|

We want to conquer all kingdoms with minimum total cost.
Capital can only be at 0 or one of the kingdom positions.

Approach:
- Precompute prefix sums for efficient range sum queries.
- For each possible final capital position (positions 0 to n), calculate the minimum cost.
- The cost consists of:
  - Moving capital to a chosen position.
  - Conquering all kingdoms to the right of that position.
  - Conquering all kingdoms to the left of that position.

Key idea:
We try all possible positions where our final capital could be (from 0 to n).
For each such position p (representing kingdom index), we calculate cost:
- Move from 0 to x[p]: a * x[p]
- Then conquer all kingdoms right of x[p] starting from x[p+1]: b * sum of distances
- Conquer all kingdoms left of x[p]: b * sum of distances

We simplify the expression:
cost = (a + b) * x[p] + b * (sum of kingdoms to the right - (n-p) * x[p])
*/

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, a, b;
    scanf("%lld %lld %lld", &n, &a, &b);
    std::vector<ll> x(n + 1, 0), cs(n + 1, 0);
    for (ll p = 1; p <= n; p++) {
      scanf("%lld", &x[p]);
      cs[p] = cs[p - 1] + x[p]; // prefix sum of positions
    }
    ll mincost((a + b) * cs[n]); // initial cost if capital stays at 0 and conquers everything
    for (ll p = 0; p <= n; p++) {
      // cost of moving to position x[p] and conquering all unvisited kingdoms after it
      ll tst = (a + b) * x[p] + b * (cs[n] - cs[p] - (n - p) * x[p]);
      mincost = (mincost < tst ? mincost : tst);
    }
    printf("%lld\n", mincost);
  }
}


// https://github.com/VaHiX/codeForces/