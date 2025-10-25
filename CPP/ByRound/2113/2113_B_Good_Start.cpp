// Problem: CF 2113 B - Good Start
// https://codeforces.com/contest/2113/problem/B

/*
B. Good Start
Algorithm: Check if a rectangular roof of size w x h can be tiled with identical a x b sheets,
           given that two sheets are already placed at positions (x1,y1) and (x2,y2).
           The problem reduces to checking whether the remaining area after placing the two sheets
           can be filled exactly by additional sheets without overlap or rotation.

Time Complexity: O(1) - Constant time operations.
Space Complexity: O(1) - Only a constant amount of extra space used.

Approach:
- Each sheet has fixed dimensions a x b.
- Two sheets are already placed at coordinates (x1,y1) and (x2,y2).
- We analyze the alignment of these two sheets to determine if they can form a valid tiling pattern.
- For vertical alignment: check if the y-difference is divisible by b (i.e., sheets align vertically).
- For horizontal alignment: check if the x-difference is divisible by a (i.e., sheets align horizontally).
- If both the existing sheets are aligned properly, we can tile completely; otherwise, tiling is not possible.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long w, h, a, b;
    scanf("%ld %ld %ld %ld", &w, &h, &a, &b);
    long x1, y1, x2, y2;
    scanf("%ld %ld %ld %ld", &x1, &y1, &x2, &y2);
    if (x1 == x2) {  // If both sheets are aligned vertically
      puts((y1 - y2) % b ? "No" : "Yes");  // Check if difference in y-coordinates is divisible by b
    } else if (y1 == y2) {  // If both sheets are aligned horizontally
      puts((x1 - x2) % a ? "No" : "Yes");  // Check if difference in x-coordinates is divisible by a
    } else {
      // If sheets are not aligned vertically or horizontally, check if either dimension mismatch
      // allows for completion of tiling pattern.
      puts(((x1 - x2) % a) && ((y1 - y2) % b) ? "No" : "Yes");
    }
  }
}


// https://github.com/VaHiX/codeForces/