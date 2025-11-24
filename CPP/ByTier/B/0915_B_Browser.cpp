// Problem: CF 915 B - Browser
// https://codeforces.com/contest/915/problem/B

#include <cstdio>
int main() {
  long n, pos, l, r;
  scanf("%ld %ld %ld %ld", &n, &pos, &l, &r);
  long num(0);
  if (l > 1 && r < n) {
    // Case: segment [l, r] is in the middle, not touching edges
    if (pos <= l) {
      // Cursor is to the left of the segment, move to l then close left, then move to r and close right
      num = (r - pos) + 2;
    } else if (r <= pos) {
      // Cursor is to the right of the segment, move to l then close right, then move to r and close left
      num = (pos - l) + 2;
    } else if (pos - l <= r - pos) {
      // Cursor is inside the segment, closer to left edge, move to left, close left side, then move to right and close right
      num = (pos - l) + (r - l) + 2;
    } else if (pos - l >= r - pos) {
      // Cursor is inside the segment, closer to right edge, move to right, close right side, then move to left and close left
      num = (r - pos) + (r - l) + 2;
    }
  } else if (l == 1 && r < n) {
    // Case: segment starts from the beginning, not touching left edge
    if (pos <= r) {
      // Cursor is to the left or at r, move to r and close everything to the left
      num = (r - pos) + 1;
    } else {
      // Cursor is to the right of r, move to r and close everything to the right
      num = (pos - r) + 1;
    }
  } else if (l > 1 && r == n) {
    // Case: segment ends at the last tab, not touching right edge
    if (pos < l) {
      // Cursor is to the left of l, move to l and close everything to the left
      num = (l - pos) + 1;
    } else {
      // Cursor is to the right or at l, move to l and close everything to the right
      num = (pos - l) + 1;
    }
  }
  printf("%ld\n", num);
  return 0;
}


// https://github.com/VaHiX/CodeForces/