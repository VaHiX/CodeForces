// Problem: CF 1918 A - Brick Wall
// https://codeforces.com/contest/1918/problem/A

/*
 * Problem: Brick Wall
 * Purpose: Calculate the maximum possible stability of an n×m brick wall.
 *          Stability = (number of horizontal bricks) - (number of vertical bricks).
 *          Bricks are of size 1×k or k×1 where k ≥ 2.
 *
 * Algorithm:
 *   To maximize stability, we want to use as many horizontal bricks as possible
 *   and as few vertical bricks as possible.
 *   Each row can be filled optimally with horizontal bricks (1×k) of size at least 2.
 *   For a row of width m, the maximum number of horizontal bricks is floor(m / 2).
 *   With n rows, total horizontal bricks = n * floor(m / 2).
 *   Vertical bricks should be minimized; one approach is to avoid using any,
 *   but since we must cover the whole area, we can place vertical bricks in a way
 *   that reduces conflict.
 *   However, optimal strategy assumes we use only horizontal bricks in all rows:
 *     - Use maximum horizontal bricks = n * floor(m / 2)
 *     - Vertical bricks = 0
 *     - Stability = n * floor(m / 2) - 0 = n * floor(m / 2)
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t); // Read number of test cases
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m); // Read dimensions
    printf("%ld\n", n * (m / 2)); // Compute and print maximum stability
  }
}


// https://github.com/VaHiX/codeForces/