// Problem: CF 887 B - Cubes for Masha
// https://codeforces.com/contest/887/problem/B

/*
 * Problem: B. Cubes for Masha
 * 
 * Purpose: Determine the largest number x such that all integers from 1 to x can be formed
 *          using the given cubes. Each cube has 6 faces with digits 0-9. Numbers cannot
 *          have leading zeros, and rotations do not allow forming 6 from 9 or vice versa.
 * 
 * Approach:
 * - Read the digits on each cube and store them in sets for fast lookup.
 * - For each number from 1 upward, check if it can be constructed using available digits:
 *   - Single digit: Check if digit exists on any cube.
 *   - Two digits: Check all permutations of cube pairs.
 *   - Three digits: Check all permutations of cube triplets.
 * 
 * Time Complexity: O(1000 * 1) = O(1) since we loop up to 1000 and set lookups are constant.
 * Space Complexity: O(1) since we use at most 3 sets of size 6 each.
 */

#include <cstdio>
#include <set>
int main() {
  const int S = 6;
  int n;
  scanf("%d", &n);
  std::set<int> a, b, c;
  for (long p = 0; p < S; p++) {
    int x;
    scanf("%d", &x);
    a.insert(x);  // Insert digits of first cube into set 'a'
  }
  if (n > 1) {
    for (long p = 0; p < S; p++) {
      int x;
      scanf("%d", &x);
      b.insert(x);  // Insert digits of second cube into set 'b'
    }
  }
  if (n > 2) {
    for (long p = 0; p < S; p++) {
      int x;
      scanf("%d", &x);
      c.insert(x);  // Insert digits of third cube into set 'c'
    }
  }
  int last(0); // Initialize the last valid number found
  for (long p = 1; p < 1000; p++) {
    if (p < 10) {
      // Check if single digit number can be formed
      if (a.count(p) || b.count(p) || c.count(p)) {
        last = p;
      } else {
        break; // Cannot form this number, stop the loop
      }
    } else if (p < 100) {
      // Check if two-digit number can be formed using two cubes
      if ((a.count(p / 10) && b.count(p % 10)) ||
          (b.count(p / 10) && a.count(p % 10)) ||
          (a.count(p / 10) && c.count(p % 10)) ||
          (c.count(p / 10) && a.count(p % 10)) ||
          (b.count(p / 10) && c.count(p % 10)) ||
          (c.count(p / 10) && b.count(p % 10))) {
        last = p;
      } else {
        break; // Cannot form this number, stop the loop
      }
    } else {
      // Check if three-digit number can be formed using three cubes
      int d0 = p % 10;
      int d1 = (p / 10) % 10;
      int d2 = (p / 100);
      if ((a.count(d0) && b.count(d1) && c.count(d2)) ||
          (a.count(d0) && b.count(d2) && c.count(d1)) ||
          (a.count(d1) && b.count(d0) && c.count(d2)) ||
          (a.count(d1) && b.count(d2) && c.count(d0)) ||
          (a.count(d2) && b.count(d0) && c.count(d1)) ||
          (a.count(d2) && b.count(d1) && c.count(d0))) {
        last = p;
      } else {
        break; // Cannot form this number, stop the loop
      }
    }
  }
  printf("%d\n", last);
  return 0;
}


// https://github.com/VaHiX/CodeForces/