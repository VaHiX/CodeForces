// Problem: CF 859 B - Lazy Security Guard
// https://codeforces.com/contest/859/problem/B

/*
Algorithm: Find minimum perimeter of a rectangle with area N
Techniques: Mathematical optimization, square root computation

Time Complexity: O(1) - constant time operations using sqrt() and basic arithmetic
Space Complexity: O(1) - only using a constant amount of extra space

The approach is based on the fact that for a given area N, we want to minimize the perimeter of a rectangle.
The optimal solution is to find the rectangle closest to a square (side lengths as close as possible).
We find the integer square root of N, then check three cases:
1. If a*a >= N, then we can form a square of side a
2. If a*(a+1) >= N, then we need a rectangle of dimensions a x (a+1) 
3. Otherwise, we need a rectangle of dimensions (a+1) x (a+1)
*/
#include <cmath>
#include <cstdio>
int main() {
  long x;
  scanf("%ld", &x);
  long a = sqrt(x);  // Find integer square root of x
  long perimeter(0);
  if (a * a >= x) {
    // Case 1: Perfect square or slightly larger square
    perimeter = 4 * a;  // Square perimeter
  } else if (a * (a + 1) >= x) {
    // Case 2: Rectangle with one side a and other side a+1
    perimeter = 4 * a + 2;  // Perimeter of a*(a+1) rectangle
  } else if ((a + 1) * (a + 1) >= x) {
    // Case 3: Rectangle with both sides a+1
    perimeter = 4 * a + 4;  // Perimeter of (a+1)*(a+1) square
  }
  printf("%ld\n", perimeter);
  return 0;
}


// https://github.com/VaHiX/CodeForces/