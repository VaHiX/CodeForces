// Problem: CF 1702 A - Round Down the Price
// https://codeforces.com/contest/1702/problem/A

#include <cstdio>
typedef long long ll;
int main() {
  long t; // Number of test cases
  scanf("%ld", &t);
  while (t--) {
    ll m; // Current price of the item
    scanf("%lld", &m);
    ll d(1); // Start with the smallest round number (10^0 = 1)
    while (10 * d <= m) { // Find the largest round number <= m
      d *= 10; // Keep multiplying by 10 to get higher powers of 10
    }
    printf("%lld\n", m - d); // Output the difference between m and the largest round number <= m
  }
}
/*
Algorithm: Find the largest round number (power of 10) less than or equal to m.
Approach:
- Start with d = 1 (which is 10^0).
- Keep doubling d by multiplying by 10 until 10 * d > m.
- At this point, d is the largest round number <= m.
- Return m - d.

Time Complexity: O(log m) per test case, since we loop through powers of 10 up to m.
Space Complexity: O(1), only using a constant amount of extra space.
*/

// https://github.com/VaHiX/codeForces/