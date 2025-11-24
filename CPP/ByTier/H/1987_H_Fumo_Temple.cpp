// Problem: CF 1987 H - Fumo Temple
// https://codeforces.com/contest/1987/problem/H

/*
Purpose: This code solves an interactive problem where the goal is to find a special cell (i0, j0) in a hidden n×m matrix.
The matrix contains values from {-1, 0, 1}, and the jury responds to queries with a specific computed value.
We use a hill-climbing-like approach with randomization to efficiently locate the target cell.

Algorithms/Techniques:
- Hill climbing with randomization
- Binary search and iterative refinement using distance-based queries
- Preprocessing and caching query results

Time Complexity: O(n * m * log(max(n, m))) - due to the iterative search and bounded query limit
Space Complexity: O(n * m) - for storing the matrix and memoization table
*/

#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>
#include <map>
#include <utility>

using namespace std;

// Memoization table to store query results
map<pair<int, int>, int> mp;

// Function to perform a query and cache result
int qry(int x, int y) {
  if (mp.count({x, y}))
    return mp[{x, y}];
  int ans;
  cout << "? " << x << " " << y << endl;
  cin >> ans;
  mp[{x, y}] = ans;
  return ans;
}

// Precomputed prefix sums for fast range sum calculation
int a[5005][5005];
int ax, ay;
int num = 0;

// Function for fast range sum computation
int qry2(int x, int y) {
  int lx = ax, rx = x, ly = ay, ry = y;
  if (lx == rx && ly == ry)
    return 0;
  if (lx > rx)
    swap(lx, rx);
  if (ly > ry)
    swap(ly, ry);
  num++;
  // Calculate sum using prefix sums
  return ry + rx - ly - lx +
         abs(a[rx][ry] - a[lx - 1][ry] - a[rx][ly - 1] + a[lx - 1][ly - 1]);
}

int main() {
  srand(time(0));
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    mp.clear();
    cin >> n >> m;
    // Start at a random location
    int nowx = rand() % n + 1, nowy = rand() % m + 1;
    int ans = qry(nowx, nowy);
    // Iteratively improve the position
    while (ans > 0) {
      int dx = ans, dy = ans;
      // Randomly adjust distance parameters
      if (rand() % 2)
        dx /= 2;
      else if (rand() % 2)
        dy /= 2;
      if (rand() % 5 == 0) {
        if (rand() % 2)
          dx = sqrt(dx);
        else
          dx = sqrt(dx + 100);
      } else if (rand() % 5 == 0) {
        if (rand() % 2)
          dy = sqrt(dy);
        else
          dy = sqrt(dy + 100);
      }
      // Define bounds for next random search
      int lx = nowx - dx, rx = nowx + dx, ly = nowy - dy, ry = nowy + dy;
      if (lx <= 1)
        lx = 1;
      if (ly <= 1)
        ly = 1;
      if (rx >= n)
        rx = n;
      if (ry >= m)
        ry = m;
      // Pick a random point within the bounds
      int nx = rand() % (rx - lx + 1) + lx;
      int ny = rand() % (ry - ly + 1) + ly;
      int c = qry(nx, ny);
      // If the new point is better, move to it
      if (c <= ans) {
        ans = c;
        nowx = nx;
        nowy = ny;
      }
    }
    // Output the found position
    cout << "! " << nowx << " " << nowy << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/