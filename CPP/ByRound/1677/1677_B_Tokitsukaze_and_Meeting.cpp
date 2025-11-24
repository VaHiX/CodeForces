// Problem: CF 1677 B - Tokitsukaze and Meeting
// https://codeforces.com/contest/1677/problem/B

/*
Algorithm/Techniques: Simulation with optimized tracking of rows and columns
Time Complexity: O(n * m) per test case, where n and m are the dimensions of the grid
Space Complexity: O(m) for storing row and column status arrays

This problem simulates students entering a meeting hall and occupying seats in a specific pattern.
Each student enters and shifts existing students to the right, wrapping to the next row when necessary.
We track which rows and columns have at least one serious student (represented by '1') and output
the total number of good rows and columns after each student enters.

The optimization uses:
- A `cols` array to track if a column has a serious student
- A `rows` array to track how many rows have a serious student in a specific column
- `cntcols` to maintain the count of good columns
- `previ` to track the position of the last serious student to efficiently compute row status
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    // cols[i] tracks whether column i has a serious student
    vector<int> cols(m, 0), rows(m, 0);
    int cntcols = 0;
    int previ = -n * m; // Position of the last serious student
    for (int i = 0; i < n * m; i++) {
      // If the column is not yet occupied by a serious student and current student is serious
      if (cols[i % m] == 0 && s[i] == '1') {
        cols[i % m] = 1; // Mark column as having a serious student
        cntcols++;       // Increment the count of good columns
      }
      // If the current student is serious, update the position of last serious student
      if (s[i] == '1')
        previ = i;
      // If the distance from the last serious student is less than m, increment row count for column
      if (i - previ < m)
        rows[i % m] = rows[i % m] + 1;
      // Output the total number of good rows and columns
      cout << cntcols + rows[i % m] << " ";
    }
    cout << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/