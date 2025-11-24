// Problem: CF 1909 A - Distinct Buttons
// https://codeforces.com/contest/1909/problem/A

/*
A. Distinct Buttons
time limit per test1 second
memory limit per test256 megabytes
Deemo - Entrance

Algorithm: 
The problem checks whether we can visit all given points using at most 3 distinct moves (U, D, R, L).
We analyze the x and y coordinates of all points to determine if there are:
- Positive and negative x values (needs both R and L)
- Positive and negative y values (needs both U and D)

If we have at most 3 distinct directions (out of {U,D,R,L}), then it's possible.

Time Complexity: O(n) per test case, where n is the number of special points.
Space Complexity: O(1), only using a few variables for tracking signs.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    int xneg(0), xpos(0), yneg(0), ypos(0);
    for (long p = 0; p < n; p++) {
      long x, y;
      scanf("%ld %ld", &x, &y);
      if (x < 0) {        // Mark if any point has negative x
        xneg = 1;
      } else if (x > 0) { // Mark if any point has positive x
        xpos = 1;
      }
      if (y < 0) {        // Mark if any point has negative y
        yneg = 1;
      } else if (y > 0) { // Mark if any point has positive y
        ypos = 1;
      }
    }
    int s = xneg + xpos + yneg + ypos;  // Count how many sign variations exist in x and y
    puts(s <= 3 ? "YES" : "NO");       // If sign variations <= 3, we can use at most 3 buttons
  }
}


// https://github.com/VaHiX/codeForces/