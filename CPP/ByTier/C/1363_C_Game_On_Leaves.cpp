// Problem: CF 1363 C - Game On Leaves
// https://codeforces.com/contest/1363/problem/C

/*
C. Game On Leaves
Purpose: Determine the winner of a game played on an unrooted tree where players remove leaf nodes,
         with the player removing the special node x winning. Players play optimally.

Algorithm:
- For each test case, build the tree from input edges.
- Count the degree of node x (number of neighbors).
- The key observation is:
  * If x has degree <= 1 or n is even, Ayush wins.
  * Otherwise, Ashish wins.

Time Complexity: O(n) per test case, as we process each edge once to count degrees.
Space Complexity: O(1) extra space, not counting input storage.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    long deg(0);
    for (long p = 1; p < n; p++) {
      long a, b;
      scanf("%ld %ld", &a, &b);
      if (a == x || b == x) {   // Check if the special node x is connected to current edge
        ++deg;                  // Increment degree of x
      }
    }
    puts((deg <= 1 || n % 2 == 0) ? "Ayush" : "Ashish");  // Decide winner based on rules
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/