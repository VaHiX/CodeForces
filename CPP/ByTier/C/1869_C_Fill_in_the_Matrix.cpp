// Problem: CF 1869 C - Fill in the Matrix
// https://codeforces.com/contest/1869/problem/C

/*
Purpose: 
  This code solves the problem of filling an n x m matrix with permutations of length m such that the beauty (MEX of column MEXs) is maximized.

Algorithms/Techniques:
  - Greedy construction of rows to ensure that the MEXs of columns can cover all values from 0 to m-1.
  - Special handling for edge cases: when m = 1 and when n < m - 1.

Time Complexity: O(n * m)
  - The algorithm iterates through the rows and columns to build the matrix, which takes linear time proportional to the total number of elements.

Space Complexity: O(1) extra space (not counting the output)
  - Only a constant amount of additional variables are used.
*/

#include <iostream>

#define ll long long
using namespace std;

void solve() {
  int n, m;
  cin >> n >> m;
  
  // Special case: if m == 1, all rows must be [0], so MEX of each column is 1, and MEX of all column MEXs is 0
  if (m == 1) {
    cout << 0 << "\n";
    for (int i = 0; i < n; i++)
      cout << "0\n";
    return;
  }
  
  // If n < m - 1, we can't generate enough distinct MEXs for columns, so we use a different strategy
  if (n < m - 1) {
    cout << n + 1 << "\n";
    for (int i = 0; i < n; i++) {
      for (int j = i; j < m; j++)
        cout << j << " ";
      for (int j = 0; j < i; j++)
        cout << j << " ";
      cout << "\n";
    }
    return;
  }
  
  // When n >= m - 1, we construct rows to achieve maximum beauty m
  cout << m << "\n";
  
  // First m - 1 rows are built to have distinct column MEX values 0 to m - 2
  for (int i = 0; i < m - 1; i++) {
    for (int j = i; j < m; j++)
      cout << j << " ";
    for (int j = 0; j < i; j++)
      cout << j << " ";
    cout << "\n";
  }
  
  // Remaining rows are filled with all numbers 0 to m - 1 to ensure consistent column behavior
  for (int i = 1; i <= n - m + 1; i++) {
    for (int j = 0; j < m; j++)
      cout << j << " ";
    cout << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/