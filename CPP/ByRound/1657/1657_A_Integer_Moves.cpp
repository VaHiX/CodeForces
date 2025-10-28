// Problem: CF 1657 A - Integer Moves
// https://codeforces.com/contest/1657/problem/A

/*
Problem: A. Integer Moves
Purpose: Determine the minimum number of operations to move a chip from (0, 0) to (x, y),
         where each operation must move the chip by an integer Euclidean distance.

Algorithms/Techniques:
- Mathematical analysis of possible moves
- Squares and square root approximation using binary search-like approach
- Greedy strategy based on distance properties

Time Complexity: O(1) per test case (since x, y are bounded by 50, the loop runs a constant number of times)
Space Complexity: O(1) - only using a few variables

The key insight is:
- If destination is (0,0), 0 operations needed.
- If distance from origin to destination is integer, 1 operation suffices.
- Otherwise, we need at least 2 operations.

The code uses a loop to find the smallest integer z such that z^2 >= x^2 + y^2,
then checks whether z^2 equals x^2 + y^2 to determine if an integer distance exists.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    long ss = x * x + y * y;
    long z(0);
    while (z * z < ss) {  // Find smallest integer z such that z^2 >= x^2 + y^2
      ++z;
    }
    printf("%d\n", (x > 0 || y > 0) + (z * z > ss));  // If (x,y)!=(0,0) add 1, if z^2 > ss add 1
  }
}


// https://github.com/VaHiX/codeForces/