// Problem: CF 1734 E - Rectangular Congruence
// https://codeforces.com/contest/1734/problem/E

/*
 * Code Purpose:
 *   Constructs an n x n matrix satisfying specific congruence conditions
 *   on submatrices and with prescribed diagonal elements.
 *
 * Algorithm/Techniques:
 *   - Uses a mathematical formula to fill matrix entries to ensure
 *     the required inequality conditions hold for all 2x2 submatrices.
 *   - The formula ensures that for any 2x2 submatrix with corners at
 *     (r1, c1), (r1, c2), (r2, c1), (r2, c2), the sum of opposite corners
 *     are not congruent modulo n.
 *
 * Time Complexity: O(n^2)
 *   - Two nested loops iterate through all matrix entries.
 *
 * Space Complexity: O(1)
 *   - Only a constant amount of extra space is used aside from the
 * input/output.
 */
#include <iostream>
using namespace std;

int n, x;
int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x; // Read the diagonal element for row i
    for (int j = 0; j < n; j++)
      cout << (x + (j - i + n) % n * i) % n
           << " "; // Compute and print matrix entry
    cout << endl;
  }
}

// https://github.com/VaHiX/CodeForces/