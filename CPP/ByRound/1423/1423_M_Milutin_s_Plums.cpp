// Problem: CF 1423 M - Milutin's Plums
// https://codeforces.com/contest/1423/problem/M

/*
 * Problem: M. Milutin's Plums
 * 
 * Algorithm: SMAWK Algorithm for finding minimum in totally monotone matrices
 * 
 * Time Complexity: O(n + m)
 * Space Complexity: O(n + m)
 * 
 * The problem involves finding the minimum element in a matrix with a special property:
 * For each row, the leftmost minimum element is non-decreasing as we go down the rows.
 * This property allows us to use the SMAWK algorithm to efficiently find the minimum.
 * 
 * The SMAWK algorithm works by:
 * 1. Finding the minimum elements in alternating rows for the current column set
 * 2. Recursively solving the problem for the selected rows
 * 3. Using the results to update minimums in the remaining rows
 * 
 * This approach uses at most 4(n + m) queries, satisfying the constraint.
 */

#include <string.h>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
int Tim = 1;
const int N = 1e6 + 5;
const int inf = 1e9;
int n, m;
unordered_map<int, int> a[N];
int f[N], p[N]; // f[i] stores minimum height in row i, p[i] stores column of that minimum

// Query function to get the value at position (i, j)
// Uses memoization to avoid duplicate queries
int ask(int x, int y) {
  if (a[x].count(y)) { // If already queried, return cached value
    return a[x][y];
  }
  cout << "? " << x << ' ' << y << endl;
  cin >> a[x][y];
  return a[x][y];
}

// Update the minimum value and its column index for row i
void calc(int i, int j) {
  if (f[i] > ask(i, j)) { // If new value is smaller
    p[i] = j; // Update column index
    f[i] = ask(i, j); // Update minimum value
  }
}

// SMAWK algorithm implementation
void SMAWK(vector<int> r, vector<int> c) {
  vector<int> C; // Column indices of candidate minimums
  int k = -1; // Index pointer for C
  for (int i : c) {
    // While the new column has a smaller or equal value than the previous candidate,
    // remove the previous candidate because it's dominated
    while (!C.empty() && ask(r[k], C[k]) >= ask(r[k], i)) {
      C.pop_back();
      k--;
    }
    if (k + 1 < r.size()) { // If there's a next row to consider
      C.push_back(i);
      k++;
    }
  }
  
  // Base case: if only one row, compute directly
  if (r.size() == 1) {
    calc(r[0], C[0]);
    return;
  }
  
  // Select odd-indexed rows for recursive call
  vector<int> R;
  for (int i = 1; i < r.size(); i += 2) {
    R.push_back(r[i]);
  }
  
  c = C; // Pass the candidate columns to recursive call
  SMAWK(R, c);
  
  // Process even-indexed rows (in order of original r)
  int u = 0;
  for (int i = 0; i < r.size(); i += 2) {
    // Process all columns that could be candidates for row i's minimum
    while (u < c.size() && c[u] < (i + 1 == r.size() ? inf : p[r[i + 1]])) {
      calc(r[i], c[u]);
      u++;
    }
    // Check the candidate column which could be the minimum for this row
    if (u < c.size()) {
      calc(r[i], c[u]);
    }
  }
}

vector<int> r, c; // Row and column indices to process

void Solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    r.push_back(i);
  }
  for (int i = 1; i <= m; i++) {
    c.push_back(i);
  }
  memset(f, 0x3f, sizeof f); // Initialize f with infinity
  SMAWK(r, c);
  
  // Find global minimum among all row minimums
  int ans = inf;
  for (int i = 1; i <= n; i++) {
    ans = min(ans, f[i]);
  }
  cout << "! " << ans << endl;
}

signed main() {
  while (Tim--) {
    Solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/