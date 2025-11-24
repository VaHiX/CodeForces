// Problem: CF 1980 E - Permutation of Rows and Columns
// https://codeforces.com/contest/1980/problem/E

/*
Purpose: Determine if matrix 'a' can be transformed into matrix 'b' using row and column swaps.
Approach:
- For each element in matrix 'b', store its original row and column indices.
- Check if all elements in the same row of 'a' map to the same row in 'b'.
- Check if all elements in the same column of 'a' map to the same column in 'b'.
- If both conditions are satisfied, transformation is possible.

Time Complexity: O(n * m)
Space Complexity: O(n * m)

Algorithm:
1. Read input matrices a and b.
2. Create row and col arrays to store original positions of elements in b.
3. For each row in a, verify all elements map to the same row in b.
4. For each column in a, verify all elements map to the same column in b.
5. If both checks pass, output "YES", else "NO".
*/

#include <iostream>

#define ll long long
#define fori(n) for (int i = 0; i < n; i++)
#define testcases                                                              \
  int t;                                                                       \
  cin >> t;                                                                    \
  while (t--)
#define ld long double
#define vl vector<long long>
#define fast                                                                   \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);
#define endl '\n'
using namespace std;
int main() {
  fast testcases {
    int n, m;
    cin >> n >> m;
    int a[n][m], b[n][m];
    fori(n) {
      for (int j = 0; j < m; j++) {
        cin >> a[i][j];
      }
    }
    int row[n * m], col[n * m]; // Store original row and column indices for elements in b
    fori(n) {
      for (int j = 0; j < m; j++) {
        cin >> b[i][j];
        row[b[i][j] - 1] = i; // Map element value to its original row
        col[b[i][j] - 1] = j; // Map element value to its original column
      }
    }
    bool check = true;
    // Check if all elements in a row map to the same row in b
    fori(n) {
      int currow = row[a[i][0] - 1]; // Get the row index of first element in row i of a
      for (int j = 1; j < m; j++) {
        if (row[a[i][j] - 1] != currow) { // If any element maps to different row
          check = false;
          break;
        }
      }
      if (!check) {
        break;
      }
    }
    if (!check) {
      cout << "NO" << endl;
      continue;
    }
    // Check if all elements in a column map to the same column in b
    fori(m) {
      int curcol = col[a[0][i] - 1]; // Get the column index of first element in column i of a
      for (int j = 1; j < n; j++) {
        if (col[a[j][i] - 1] != curcol) { // If any element maps to different column
          check = false;
          break;
        }
      }
      if (!check) {
        break;
      }
    }
    if (!check) {
      cout << "NO" << endl;
      continue;
    }
    cout << "YES" << endl;
  }
}


// https://github.com/VaHiX/CodeForces/