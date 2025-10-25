// Problem: CF 1769 A - Узкая дорога
// https://codeforces.com/contest/1769/problem/A

/*
 * Problem: A. Узкая дорога (Narrow Road)
 *
 * Purpose: Simulate the movement of n motorcycles on a narrow one-way road,
 * where each motorcycle i moves at speed i meters per second (i = 1..n).
 * Motorcycles cannot overtake and must maintain at least 1 meter distance
 * from the next one. After one second, output their new distances to the destination.
 *
 * Algorithm:
 * - For each motorcycle i at position a[i], simulate moving forward by speed i.
 * - Adjust positions so that minimum 1-meter gap is maintained from previous.
 * - Use dynamic programming logic: maintain minimum safe position for current
 *   motorcycle.
 *
 * Time Complexity: O(n) - single pass through all motorcycles.
 * Space Complexity: O(1) - only a few variables used, no extra space.
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long prev(-100); // Initialize to a value smaller than any possible position
  for (long p = 1; p <= n; p++) {
    long x;
    scanf("%ld", &x);
    x -= p; // Adjust the position by subtracting the speed (p)
    // Update prev to be either current position x or (prev + 1), whichever is larger
    // Ensures minimum 1-meter gap from previous motorcycle
    prev = (x > (prev + 1) ? x : (prev + 1));
    printf("%ld\n", prev);
  }
}


// https://github.com/VaHiX/codeForces/