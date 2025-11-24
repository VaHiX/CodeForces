// Problem: CF 1360 A - Minimal Square
// https://codeforces.com/contest/1360/problem/A

/*
 * Problem: A. Minimal Square
 * Purpose: Find the minimum area of a square that can contain two identical a × b rectangles.
 * Algorithms/Techniques: 
 *   - Greedy approach with case analysis
 *   - Brute-force checking of possible orientations and placements
 * Time Complexity: O(1) per test case (constant time due to fixed input constraints)
 * Space Complexity: O(1) (only using a few variables)
 */
#include <stdio.h>
#include <algorithm>

int main() {
  int t, a, b, c;
  for (scanf("%d", &t); t--; printf("%d\n", c * c)) // Read number of test cases and process each
    scanf("%d%d", &a, &b), // Read dimensions of rectangle
    c = std::min(std::max(a, 2 * b), std::max(b, 2 * a)); // Compute minimal side of square
}


// https://github.com/VaHiX/codeForces/