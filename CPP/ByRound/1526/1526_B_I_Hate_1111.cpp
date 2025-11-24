// Problem: CF 1526 B - I Hate 1111
// https://codeforces.com/contest/1526/problem/B

/*
B. I Hate 1111
Algorithm: Dynamic Programming with precomputation
Time Complexity: O(1111 + t) = O(t)
Space Complexity: O(1111) = O(1)

The problem asks whether a number x can be represented as a sum of 11, 111, 1111, etc.
We use dynamic programming where check[i] indicates if number i can be formed.
Base cases:
- If i % 11 == 0 or i % 111 == 0, then check[i] = true (can form directly)
Transitions:
- If i > 11 and check[i - 11] is true, then check[i] = true (add 11)
- If i > 111 and check[i - 111] is true, then check[i] = true (add 111)
For any x >= 1111, we always answer "YES" because any large enough number can be expressed
using combinations of 11s and 111s, leveraging the mathematical property that numbers
can be represented in this form once they exceed certain thresholds.
*/

#include <cstdio>
#include <vector>
int main() {
  std::vector<bool> check(1111, false);
  for (long p = 1; p < 1111; p++) {
    if (p % 11 == 0 || p % 111 == 0) {
      check[p] = true;
    } else if (p > 11 && check[p - 11]) {
      check[p] = true;
    } else if (p > 111 && check[p - 111]) {
      check[p] = true;
    }
  }
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld\n", &x);
    if (x >= 1111) {
      puts("YES");
    } else {
      puts(check[x] ? "YES" : "NO");
    }
  }
}


// https://github.com/VaHiX/codeForces/