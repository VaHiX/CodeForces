// Problem: CF 1845 B - Come Together
// https://codeforces.com/contest/1845/problem/B

/*
Algorithm: 
The problem involves finding the maximum number of cells that two people (Bob and Carol) can walk together on their shortest paths from a shared starting point A to their respective destinations B and C. The key insight is that the shared cells occur on the path from A to the point where both paths align (i.e., take the same route), then diverge to their respective destinations.

Approach:
1. We calculate how much of the path Bob and Carol can walk together based on their relative positions.
2. For both x- and y-directions:
   - If A is the closest to both B and C in that direction, we add the minimum of the distances from A to B and A to C.
   - If A is the farthest from both B and C in that direction, we add the distance from A to the farthest of the two.
3. The starting cell A is always counted (hence cnt = 1).

Time Complexity: O(t) where t is the number of test cases. Each test case is processed in constant time.
Space Complexity: O(1). Only a constant amount of extra space is used.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long xa, ya;
    scanf("%ld %ld", &xa, &ya);
    long xb, yb;
    scanf("%ld %ld", &xb, &yb);
    long xc, yc;
    scanf("%ld %ld", &xc, &yc);
    long cnt(1); // Start with 1 because cell A is always included
    
    // Handle the x-direction
    if (xa < xb && xa < xc) {
      // A is the closest to both B and C in x-direction
      // Add the smaller of the two distances from A to B and A to C
      cnt += (xb < xc ? xb : xc) - xa;
    } else if (xa > xb && xa > xc) {
      // A is the farthest from both B and C in x-direction
      // Add the distance from A to the farthest of the two
      cnt += xa - (xb > xc ? xb : xc);
    }
    
    // Handle the y-direction
    if (ya < yb && ya < yc) {
      // A is the closest to both B and C in y-direction
      cnt += (yb < yc ? yb : yc) - ya;
    } else if (ya > yb && ya > yc) {
      // A is the farthest from both B and C in y-direction
      cnt += ya - (yb > yc ? yb : yc);
    }
    
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/CodeForces/