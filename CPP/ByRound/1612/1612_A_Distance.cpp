// Problem: CF 1612 A - Distance
// https://codeforces.com/contest/1612/problem/A

#include <cstdio>
// Flowerbox:
// Problem: Find a point C such that it is equidistant (in Manhattan distance) from both A(0,0) and B(x,y),
// and the distance is half of the distance from A to B.
// Key algorithm: The point C must be at the midpoint of the path between A and B in Manhattan space.
// For a point to exist, the total Manhattan distance from A to B must be even.
// If x+y is odd, then no such integer point C exists.
// If x+y is even, we can construct C as (x/2, (y+1)/2).
// This formula ensures:
//   - d(A,C) = x/2 + (y+1)/2 = (x+y+1)/2 = d(A,B)/2 (since d(A,B) = x+y)
//   - d(B,C) = |x - x/2| + |y - (y+1)/2| = x/2 + (y-1)/2 = (x+y-1)/2 = d(A,B)/2
// Time complexity: O(t), where t is the number of test cases.
// Space complexity: O(1).

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    if ((x + y) % 2) {
      puts("-1 -1");
    } else {
      printf("%ld %ld\n", (x / 2), (y + 1) / 2);
    }
  }
}

// https://github.com/VaHiX/CodeForces/