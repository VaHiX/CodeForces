// Problem: CF 1765 K - Torus Path
// https://codeforces.com/contest/1765/problem/K

/*
K. Torus Path
Algorithms/Techniques: Greedy, Matrix Traversal
Time Complexity: O(n^2)
Space Complexity: O(n^2)

The problem involves finding the maximum sum path from top-left to bottom-right
in an n×n grid with special torus-like movement rules:
- Can only move right or down.
- Moving right from last column teleports to first column in same row.
- Moving down from last row teleports to first row in same column.
- Cannot revisit cells (including start and end).
The key insight is that the path must visit exactly n cells (since we need to 
move exactly n-1 steps right and n-1 steps down, but the starting cell is counted
from the beginning and the ending cell is not left). However, since there's a
special constraint involving the torus movement, the optimal solution can be found
by avoiding the minimum element on the main anti-diagonal (from top-right to bottom-left),
as that is part of any possible path.

The approach:
1. Read all elements into a 2D matrix.
2. Calculate total sum of all elements.
3. Find the minimum value in the anti-diagonal (i-th row, n-i-1 column).
4. Subtract this minimum from the total sum to get the maximum score.

This is valid because:
- Any valid path must include exactly one element from the anti-diagonal.
- To maximize the sum of visited elements, we minimize the penalty,
  which is removing the smallest element on the anti-diagonal.

Sample Input 1:
2
1 2
3 4
Output: 8

Sample Input 2:
3
10 10 10
10 0 10
10 10 10
Output: 80
*/

#include <algorithm>
#include <iostream>

#define ll long long int
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  ll n;
  cin >> n;
  ll a[n][n], sum = 0; // Declare grid and sum variable

  // Read input and calculate total sum of all elements
  for (ll i = 0; i < n; i++)
    for (ll j = 0; j < n; j++)
      cin >> a[i][j], sum += a[i][j];

  ll mn = 1e9 + 10; // Initialize minimum to large value

  // Find the minimum element on the anti-diagonal (top-right to bottom-left)
  for (ll i = 0; i < n; i++) {
    mn = min(mn, a[i][n - i - 1]);
  }

  // Output total sum minus the minimum anti-diagonal element
  cout << sum - mn << "\n";
}


// https://github.com/VaHiX/codeForces/