// Problem: CF 1928 A - Rectangle Cutting
// https://codeforces.com/contest/1928/problem/A

/*
Algorithm/Techniques: Mathematical analysis of rectangle cutting and rearrangement
Time Complexity: O(1) per test case
Space Complexity: O(1)

Problem Description:
Given a rectangle of size a x b, determine if it's possible to cut it into two rectangles
and then rearrange them to form a different rectangle (ignoring 90-degree rotations).

Key Insight:
- A rectangle can be cut into two rectangles only if one dimension is even.
- If we cut along the even side, we get two rectangles of size (a/2) x b or a x (b/2).
- Then we check if these two rectangles can form another rectangle with different dimensions.
- We must ensure that the resulting rectangle has integer sides and is not the same as original.

The condition checks:
- If 'a' is even, cutting it in half gives us two rectangles of size (a/2) x b
  - These can form a new rectangle of size (a/2 * 2) x b = a x b (same as original)
  - BUT they can also be arranged to form (b x a) or (b x a/2) depending on how we place them.
- For this to result in a *different* rectangle, the arrangement must produce a new valid dimension.
- Specifically, when 'a' is even and a/2 != b, it implies the resulting shapes are different from original.

The logic handles both cases for even dimensions of either side (a or b).
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    bool possible = (a % 2 == 0 && a / 2 != b) || (b % 2 == 0 && b / 2 != a); // Check if cutting along even side leads to distinct rectangles
    puts(possible ? "Yes" : "No");
  }
}


// https://github.com/VaHiX/codeForces/