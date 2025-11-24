// Problem: CF 1799 E - City Union
// https://codeforces.com/contest/1799/problem/E

/*
Code Purpose:
This code solves the problem of connecting two cities (connected components of filled cells) on a grid 
by filling minimum number of empty cells such that:
1. The two cities become one connected component
2. The shortest path between any two filled cells equals their Manhattan distance

The approach:
1. Identify the bounding box containing all filled cells
2. Fill the entire bounding box with filled cells
3. Remove parts of the bounding box that would violate the Manhattan distance constraint
4. Specifically, for each city, remove parts that would create indirect paths longer than Manhattan distance

Time Complexity: O(n*m) where n and m are grid dimensions
Space Complexity: O(n*m) for storing grid and result

Algorithms/Techniques:
- Bounding box calculation
- Greedy filling strategy
- Manhattan distance constraint enforcement
*/

#include <stddef.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define endl '\n'
#define prec(x)                                                                \
  cout << fixed;                                                               \
  cout.precision(x);
#define mp make_pair
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, ll> pll;
void SolveProblem() {
  int n, m;
  cin >> n >> m;
  string s[60], ans[60];
  for (int i = 0; i < n; i++)
    cin >> s[i];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      ans[i] += '.';
  }
  pii maxi = mp(-1, -1), mini = mp(100, 100), maxj = mp(-1, -1),
      minj = mp(100, 100);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (s[i][j] == '.')
        continue;
      if (maxi.first < i)
        maxi = mp(i, j);
      if (mini.first > i)
        mini = mp(i, j);
      if (maxj.second < j)
        maxj = mp(i, j);
      if (minj.second > j)
        minj = mp(i, j);
    }
  }
  for (int i = mini.first; i <= maxi.first; i++) {
    for (int j = minj.second; j <= maxj.second; j++)
      ans[i][j] = '#';
  }
  pii left = mini, right = mini;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (s[i][j] == '.')
        continue;
      if (j < left.second) {
        s[i][left.second] = '#'; // Fill the cell to connect
        for (int ii = left.first; ii < i; ii++) {
          for (int jj = minj.second; jj < left.second; jj++) {
            ans[ii][jj] = '.'; // Remove cells that would break Manhattan distance
          }
        }
        left = mp(i, j);
      } else if (j > right.second) {
        s[i][right.second] = '#'; // Fill the cell to connect
        for (int ii = right.first; ii < i; ii++) {
          for (int jj = right.second + 1; jj <= maxj.second; jj++) {
            ans[ii][jj] = '.'; // Remove cells that would break Manhattan distance
          }
        }
        right = mp(i, j);
      }
    }
  }
  left = maxi, right = maxi;
  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      if (s[i][j] == '.')
        continue;
      if (j < left.second) {
        for (int ii = left.first; ii > i; ii--) {
          for (int jj = minj.second; jj < left.second; jj++) {
            ans[ii][jj] = '.'; // Remove cells that would break Manhattan distance
          }
        }
        left = mp(i, j);
      } else if (j > right.second) {
        for (int ii = right.first; ii > i; ii--) {
          for (int jj = right.second + 1; jj <= maxj.second; jj++) {
            ans[ii][jj] = '.'; // Remove cells that would break Manhattan distance
          }
        }
        right = mp(i, j);
      }
    }
  }
  for (int i = 0; i < n; i++)
    cout << ans[i] << endl;
  cout << endl;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int test_case = 1;
  cin >> test_case;
  for (int tc = 1; tc <= test_case; tc++) {
    SolveProblem();
  }
}


// https://github.com/VaHiX/CodeForces/