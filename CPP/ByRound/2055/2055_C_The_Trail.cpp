// Problem: CF 2055 C - The Trail
// https://codeforces.com/contest/2055/problem/C

/*
Purpose: This code restores a tampered grid to its original state such that all rows and columns have the same sum.
         The tampered grid has a path from (1,1) to (n,m) with zero altitudes, and we need to assign values to these
         zero cells to make all row/column sums equal.

Algorithms/Techniques:
- Simulation of path traversal
- Dynamic adjustment of values to maintain row/column sum balance
- Greedy approach to assign values during path traversal

Time Complexity: O(n * m * (n + m)) in worst case due to nested loops for each path step.
Space Complexity: O(n * m) for storing the grid and path information.

*/
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pair<int, int>> vii;
typedef vector<pair<ll, ll>> vll;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<string> vs;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define pb push_back
#define si(x) (int)x.size()
#ifdef DEBUG
#include "debug/debug.hpp"
#else
#define nl
#define db(x)
#endif
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
#ifdef DEBUG
  freopen("input.txt", "r", stdin);
  freopen("debug.log", "w", stderr);
  freopen("answer.txt", "w", stdout);
#endif
  int Q;
  cin >> Q;
  while (Q--) {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vvl arr(n, vl(m, 0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int x;
        cin >> x;
        arr[i][j] = x;
      }
    }
    int c = 0;
    int r = 0;
    for (const char &ch : s) {
      if (ch == 'D') {
        // When moving down, adjust the current cell value to balance row sums
        for (int i = 0; i < m; i++) {
          if (i == c)
            continue;
          arr[r][c] -= arr[r][i];
        }
        db(arr[r][c]);
        db(ch);
        nl;
        r += 1;
      } else {
        // When moving right, adjust the current cell value to balance column sums
        for (int i = 0; i < n; i++) {
          if (i == r)
            continue;
          arr[r][c] -= arr[i][c];
        }
        db(arr[r][c]);
        db(ch);
        nl;
        c += 1;
      }
    }
    // Final adjustment for the last cell
    for (int i = 0; i < n - 1; i++) {
      arr[r][c] -= arr[i][c];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << arr[i][j] << " ";
      }
      cout << endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/