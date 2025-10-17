// Problem: CF 1971 C - Clock and Strings
// https://codeforces.com/contest/1971/problem/C

/*
C. Clock and Strings
Algorithm: 
  - For each test case, we are given four distinct integers a, b, c, d representing positions on a clock labeled 1 to 12.
  - Alice connects a and b with a red string; Bob connects c and d with a blue string.
  - We need to determine if these two strings intersect on the clock.
  
  Key insight:
    - On a circular clock, two chords (strings) intersect if and only if one endpoint of each chord lies in the interval defined by the other chord's endpoints, considering wraparound.
    - To simplify comparison, we ensure that a <= b by swapping if necessary.
    - Then check whether c lies within [a,b] or d lies within [a,b]. If exactly one of these conditions is true, the chords intersect.

Time Complexity: O(1) per test case
Space Complexity: O(1)

Techniques:
  - Sorting intervals using conditional swaps
  - Checking if point is inside a circular interval using bounded comparisons
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c, d;
    scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
    if (a > b) {
      long x = a;
      a = b;
      b = x;
    }
    // Check if c is in interval [a,b] (inclusive)
    bool u = (a <= c && c <= b);
    // Check if d is in interval [a,b] (inclusive)
    bool v = (a <= d && d <= b);
    // If exactly one of u or v is true, then intervals intersect
    puts(u ^ v ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/