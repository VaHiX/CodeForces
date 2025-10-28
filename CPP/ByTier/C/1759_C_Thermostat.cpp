// Problem: CF 1759 C - Thermostat
// https://codeforces.com/contest/1759/problem/C

/*
C. Thermostat
Algorithm: Greedy + Case Analysis
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem requires finding the minimum number of operations to change the thermostat from temperature 'a' to 'b'.
Each operation allows changing temperature by at least 'x' units, within range [l, r].

Approach:
1. If a == b: 0 operations needed.
2. If |a - b| >= x: 1 operation is sufficient (direct move).
3. Else if we can reach from both ends using two steps:
   - Try to use intermediate values at l+x or r-x.
4. Otherwise, it's impossible.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r, x;
    scanf("%ld %ld %ld", &l, &r, &x);
    long a, b;
    scanf("%ld %ld", &a, &b);
    if (a == b) {
      puts("0");
    } else if (a >= b + x || b >= a + x) {
      puts("1");
    } else if (a >= l + x && b >= l + x) {
      puts("2");
    } else if (r >= a + x && r >= b + x) {
      puts("2");
    } else if (a >= l + x && r >= b + x) {
      puts("3");
    } else if (r >= a + x && b >= l + x) {
      puts("3");
    } else {
      puts("-1");
    }
  }
}


// https://github.com/VaHiX/codeForces/