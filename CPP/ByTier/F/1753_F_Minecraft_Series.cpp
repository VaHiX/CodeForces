// Problem: CF 1753 F - Minecraft Series
// https://codeforces.com/contest/1753/problem/F

/*
 * Problem: Minecraft Series
 *
 * Purpose:
 * This code solves a problem where we need to count the number of square
 * subregions in an n x m grid such that a team of at least t people can be
 * formed, where team members have distinct consecutive aggressiveness degrees
 * including 0.
 *
 * Approach:
 * - Sweep through all possible top-left corners of squares (1,1) to (n,1) and
 * (1,1) to (1,m)
 * - For each starting position, expand the square in a diagonal manner
 * - Maintain a data structure to track available aggressiveness values in
 * current window
 * - Use two data structures to handle positive and negative values separately
 * - Check if a valid team (including 0) of at least t members can be formed
 *
 * Time Complexity: O(n * m * sqrt(k)) where k is the number of students.
 * Space Complexity: O(n * m + k) for storing student locations and additional
 * structures.
 */

#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

struct ds {
  // Data structure to maintain count of aggressiveness values
  int a[1000], b[1000000];

  // Initialize data structures
  ds() {
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
  }

  // Add a value to the data structure
  void add(int p) {
    b[p]++;
    if (b[p] == 1)
      a[p / 1000]++;
  }

  // Remove a value from the data structure
  void del(int p) {
    b[p]--;
    if (b[p] == 0)
      a[p / 1000]--;
  }

  // Query for the minimum missing value
  int qry() {
    for (int i = 0; i < 1000; i++)
      if (a[i] != 1000)
        for (int j = i * 1000;; j++)
          if (!b[j])
            return j;
    return 1000000;
  }
} ds0, ds1;

int n, m, k, t, ans;
vector<int> v[40004]; // Store students at each grid position

// Convert grid coordinates to index
int I(int x, int y) { return (x - 1) * m + y; }

// Check if a valid team can be formed
bool check() { return ds0.qry() + ds1.qry() + 1 >= t; }

// Add students at position i to data structures
void add(int i) {
  for (auto w : v[i]) {
    if (w > 0)
      ds0.add(w - 1);
    if (w < 0)
      ds1.add(-w - 1);
  }
}

// Remove students at position i from data structures
void del(int i) {
  for (auto w : v[i]) {
    if (w > 0)
      ds0.del(w - 1);
    if (w < 0)
      ds1.del(-w - 1);
  }
}

// Solve for all squares starting at (a,b) going diagonally
void sol(int a, int b) {
  add(I(a, b));
  int c = a, d = b;
  for (;;) {
    // Expand square until valid team can be formed
    while (!check() && c < n && d < m) {
      c++, d++;
      for (int i = a; i <= c; i++)
        add(I(i, d));
      for (int i = b; i < d; i++)
        add(I(c, i));
    }
    if (!check())
      break;
    // Count valid squares
    ans += min(n - c + 1, m - d + 1);
    if (a == n || b == m)
      break;
    // Shrink square
    for (int i = a; i <= c; i++)
      del(I(i, b));
    for (int i = b + 1; i <= d; i++)
      del(I(a, i));
    a++, b++;
    if (c < a)
      c++, d++, add(I(c, d));
  }
  // Clean up remaining elements
  for (int i = a; i <= c; i++)
    for (int j = b; j <= d; j++)
      del(I(i, j));
}

int main() {
  scanf("%d%d%d%d", &n, &m, &k, &t);
  while (k--) {
    int x, y, w;
    scanf("%d%d%d", &x, &y, &w);
    // Only process values within reasonable range
    if (abs(w) <= 1000000 && w)
      v[I(x, y)].push_back(w);
  }
  // Process all starting points
  for (int i = 1; i <= m; i++)
    sol(1, i);
  for (int i = 2; i <= n; i++)
    sol(i, 1);
  printf("%d", ans);
}

// https://github.com/VaHiX/CodeForces/