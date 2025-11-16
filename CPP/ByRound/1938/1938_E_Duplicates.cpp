// Problem: CF 1938 E - Duplicates
// https://codeforces.com/contest/1938/problem/E

/*
 * Code Purpose: 
 * This code solves the problem of making an n×n matrix satisfy the condition that
 * every row and every column contains duplicates. It does this by finding the minimum
 * number of modifications needed to ensure that each row and column has at least one
 * repeated element.
 *
 * Algorithm:
 * 1. For each row, check if it has all distinct elements (size of set equals n).
 *    If so, mark it as needing modification.
 * 2. For each column, check if it has all distinct elements. If so, mark it as needing modification.
 * 3. The minimum modifications needed is the maximum of rows and columns requiring changes.
 * 4. Select modifications to fix either all rows or all columns depending on which is fewer,
 *    prioritizing the case that requires fewer operations.
 * 5. For the remaining changes required, select elements to modify in a way that ensures
 *    the new value does not create a new constraint violation.
 *
 * Time Complexity: O(n^3) per test case due to nested loops for checking and modifying.
 * Space Complexity: O(n^2) for input matrix and auxiliary data structures.
 */

#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;
#define int long long
#define fi first
#define se second
#define pb push_back
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef pair<ii, ii> iiii;
const int N = 105;
const int oo = 1e18 + 7, mod = 1e9 + 7;
int n, a[N][N];
int ind[N];
vector<int> row, col;

void process() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++)
      cin >> a[i][j];
  }
  row.clear();
  col.clear();
  
  // Check rows for duplicates
  for (int i = 1; i <= n; i++) {
    set<int> se;
    for (int j = 1; j <= n; j++)
      se.insert(a[i][j]);
    if (se.size() == n)
      row.pb(i);
  }
  
  // Initialize column markers
  for (int i = 1; i <= n; i++)
    ind[i] = -1;
    
  // Check columns for duplicates
  for (int i = 1; i <= n; i++) {
    set<int> se;
    for (int j = 1; j <= n; j++)
      se.insert(a[j][i]);
    if (se.size() == n)
      col.pb(i);
  }
  
  // Output the minimum number of operations
  cout << max((int)row.size(), (int)col.size()) << "\n";
  
  // If there are more rows needing changes than columns
  if (row.size() > col.size()) {
    // Mark which rows correspond to columns for tracking
    for (int i = 0; i < col.size(); i++)
      ind[row[i]] = i;
      
    // Modify elements at intersections of rows and columns needing changes
    for (int i = 0; i < col.size(); i++) {
      int temp = a[row[i]][col[i]];
      temp++;
      if (temp > n)
        temp = 1;
      cout << row[i] << " " << col[i] << " " << temp << "\n";
      a[row[i]][col[i]] = temp;
    }
    
    // Handle remaining rows that need fixing
    int cnt = 0;
    for (int i = col.size(); i < row.size(); i++) {
      cnt++;
      for (int j = 1; j <= n; j++) {
        a[row[i]][cnt] = j;
        bool ck = 1;
        set<int> se;
        se.clear();
        for (int k = 1; k <= n; k++)
          se.insert(a[row[i]][k]);
        if (se.size() == n)
          continue;
          
        se.clear();
        for (int k = 1; k <= n; k++)
          se.insert(a[k][cnt]);
        if (se.size() == n)
          continue;
          
        cout << row[i] << " " << cnt << " " << j << "\n";
        break;
      }
    }
  } else {
    // Mark which columns correspond to rows for tracking
    for (int i = 0; i < row.size(); i++)
      ind[col[i]] = i;
      
    // Modify elements at intersections of rows and columns needing changes
    for (int i = 0; i < row.size(); i++) {
      int temp = a[row[i]][col[i]];
      temp++;
      if (temp > n)
        temp = 1;
      a[row[i]][col[i]] = temp;
      cout << row[i] << " " << col[i] << " " << temp << "\n";
    }
    
    // Handle remaining columns that need fixing
    int cnt = 0;
    for (int i = row.size(); i < col.size(); i++) {
      cnt++;
      for (int j = 1; j <= n; j++) {
        a[cnt][col[i]] = j;
        set<int> se;
        se.clear();
        for (int k = 1; k <= n; k++)
          se.insert(a[k][col[i]]);
        if (se.size() == n)
          continue;
          
        se.clear();
        for (int k = 1; k <= n; k++)
          se.insert(a[cnt][k]);
        if (se.size() == n)
          continue;
          
        cout << cnt << " " << col[i] << " " << j << "\n";
        break;
      }
    }
  }
}

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    process();
}


// https://github.com/VaHiX/CodeForces/