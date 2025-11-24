// Problem: CF 463 C - Gargari and Bishops
// https://codeforces.com/contest/463/problem/C

/*
 * Problem: Gargari and Bishops
 * Algorithm: Preprocessing diagonals, Greedy selection
 * 
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 * 
 * Key Idea:
 * - For each cell (i, j), we compute two sums:
 *   a[i + j] = sum of elements on the main diagonal (top-left to bottom-right)
 *   b[i - j + n] = sum of elements on the anti-diagonal (top-right to bottom-left)
 * - For any two bishops placed on different diagonals (i.e., one on main diagonal and one on anti-diagonal),
 *   we can avoid overlap if they are placed on diagonals with different parity (even vs odd).
 * - For each diagonal, we store maximum sum we can get by placing a bishop there.
 * - Then we select two best positions, one on a main diagonal and one on anti-diagonal of different parity.
 * 
 * The solution is based on:
 * 1. Preprocessing: For all cells, accumulate their values into diagonal sums.
 * 2. Greedily selecting the best position on each parity diagonal.
 * 
 * Sample Input:
 * 4
 * 1 1 1 1
 * 2 1 1 0
 * 1 1 1 0
 * 1 0 0 1
 *
 * Sample Output:
 * 12
 * 2 2 3 2
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
#define rep(i, a, n) for (int i = a; i < n; i++)
typedef long long ll;
int n, c[2010][2010], x[2], y[2];
ll a[4010], b[4010], ret[2];

int main() {
  scanf("%d", &n);
  rep(i, 0, n) rep(j, 0, n) {
    scanf("%d", &c[i][j]);
    a[i + j] += c[i][j]; // Sum of main diagonal elements
    b[i - j + n] += c[i][j]; // Sum of anti-diagonal elements
  }
  rep(i, 0, n)
      rep(j, 0, n) if (a[i + j] + b[i - j + n] - c[i][j] >= ret[(i + j) & 1]) {
    int v = (i + j) & 1; // Determine even or odd parity diagonal
    ret[v] = a[i + j] + b[i - j + n] - c[i][j]; // Compute max value excluding current cell
    x[v] = i + 1; // Row coordinate of bishop
    y[v] = j + 1; // Column coordinate of bishop
  }
  printf("%I64d\n", ret[0] + ret[1]); // Print total maximum value
  printf("%d %d %d %d\n", x[0], y[0], x[1], y[1]); // Print coordinates of two bishops
}


// https://github.com/VaHiX/CodeForces/