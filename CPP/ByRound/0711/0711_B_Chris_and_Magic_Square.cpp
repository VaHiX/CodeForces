// Problem: CF 711 B - Chris and Magic Square
// https://codeforces.com/contest/711/problem/B

/*
 * Problem: Chris and Magic Square
 * Purpose: Determine the positive integer to fill in the empty cell of a magic square.
 * Algorithm:
 *   1. Read the grid and compute row sums, column sums, and diagonal sums.
 *   2. Identify the position of the empty cell (0).
 *   3. Assume the magic sum is the same as the row sum of the row adjacent to the empty cell.
 *   4. Compute the value to place in the empty cell based on this assumption.
 *   5. Validate if placing this value creates a valid magic square.
 * Time Complexity: O(n^2) - we iterate through the grid twice.
 * Space Complexity: O(n) - we store row and column sums.
 */

#include <stdio.h>
#include <iostream>

using namespace std;
typedef long long ll;
#define N 505
int n;
ll r[N];  // Row sums
ll c[N];  // Column sums
int main() {
  scanf("%d", &n);
  int x, y;  // Coordinates of the empty cell
  ll d1 = 0, d2 = 0;  // Primary and secondary diagonal sums
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      int p;
      scanf("%d", &p);
      if (p == 0) {
        x = i;
        y = j;
      }
      r[i] += p;  // Accumulate row sum
      c[j] += p;  // Accumulate column sum
      if (i == j)
        d1 += p;  // Primary diagonal
      if (i == n - j - 1)
        d2 += p;  // Secondary diagonal
    }
  if (n == 1) {
    printf("1\n");
    return 0;
  }
  // Estimate the magic sum assuming the adjacent row is correct
  ll m = r[(x + 1) % n] - r[x];
  r[x] += m;  // Add the value to row sum
  c[y] += m;  // Add the value to column sum
  if (x == y)
    d1 += m;  // Update primary diagonal
  if (x == n - y - 1)
    d2 += m;  // Update secondary diagonal
  int ok = int(m > 0 && d1 == d2);  // Check if m is positive and diagonals are equal
  for (int i = 0; i < n; i++)
    ok &= int(r[i] == d1 && c[i] == d1);  // Validate all rows and columns
  if (ok)
    cout << m << endl;
  else
    cout << -1 << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/