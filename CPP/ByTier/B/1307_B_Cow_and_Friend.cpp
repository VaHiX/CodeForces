// Problem: CF 1307 B - Cow and Friend
// https://codeforces.com/contest/1307/problem/B

/*
B. Cow and Friend
Algorithms/Techniques: Greedy, Mathematical Analysis

Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem asks to find the minimum number of hops to reach point (x, 0) from (0, 0),
where each hop must have a distance equal to one of the given favorite numbers.
The key insight is:
- If x can be represented as a sum of some favorite numbers (i.e., there's a favorite number equal to x), then we need only 1 hop.
- If not, and x < max(a_i) for all favorite numbers a_i, then we need at least 2 hops (one to get close and one to cover the remaining distance).
- Otherwise, if x > max(a_i), it is always possible to make at most 2 hops. The minimum number of hops equals ceil(x / max(a_i)) in this case.

The solution determines:
1. Whether any favorite number equals x (f = 1)
2. Finds the maximum favorite number (maxx)
3. Based on these, outputs either:
   - 1 if x is a favorite number
   - 2 if x < maxx
   - ceil((x-1) / maxx) + 1 for x >= maxx
*/

#include <stdio.h>
int n, x, maxx, f, t;
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &x);
    f = 0;
    maxx = 1;
    for (int i = 1; i <= n; i++) {
      int p;
      scanf("%d", &p);
      if (p == x)   // Check if x is a favorite number
        f = 1;
      if (p > maxx) // Track the maximum favorite number
        maxx = p;
    }
    printf("%d\n", f ? 1 : (maxx < x ? (x - 1) / maxx + 1 : 2));
  }
}


// https://github.com/VaHiX/codeForces/