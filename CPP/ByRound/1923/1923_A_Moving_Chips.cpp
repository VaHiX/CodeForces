// Problem: CF 1923 A - Moving Chips
// https://codeforces.com/contest/1923/problem/A

/*
Problem: A. Moving Chips
Task: Move chips to form a single contiguous block with minimum operations.
Algorithm: Two-pointer approach with tracking of free cells and chip movements.
Time Complexity: O(n) per test case, where n is the number of cells.
Space Complexity: O(1), only using a constant amount of extra space.

The idea is to traverse the ribbon from left to right. When we encounter a chip,
we track how many free cells are between this chip and the previous chip.
Each such "gap" contributes one operation to move a chip into it.
We accumulate these operations in cnt.

For each chip found:
- If start is not set, set it as current position.
- Add number of zeros (free cells) since last chip to count.
- Reset zero counter after encountering a chip.
If a free cell is encountered and there's already a started block:
- Increment zero counter for potential gap.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long start(-1), z(0), cnt(0); // start: first chip position, z: free cells since last chip, cnt: operations
    for (long p = 0; p < n; p++) {
      int x;
      scanf("%d", &x);
      if (x) { // if chip found
        if (start < 0) { // first chip
          start = p;
        }
        cnt += z; // add free cells between this and previous chip to operation count
        z = 0; // reset gap counter
      } else if (start >= 0) { // if free cell and we've started seeing chips
        ++z; // increment free cell counter
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/