// Problem: CF 2163 E - Plegma
// https://codeforces.com/contest/2163/problem/E

/*
Algorithm/Technique: 
- This solution uses a strategy to encode the connectivity of a binary grid by selecting specific row and column indices.
- For connected grid (C = 1): Select row with minimum lexicographical string and column with maximum lexicographical string.
- For disconnected grid (C = 0): Select row with maximum lexicographical string and column with minimum lexicographical string.
- During second run, player B compares the received row and column strings to determine connectivity.

Time Complexity: O(n^2) for each test case due to string comparisons and column transformations.
Space Complexity: O(n^2) for storing the grid and transposed grid.
*/

#include <iostream>
#include <string>

using namespace std;
int Tim = 1;
const int N = 1005;
string type;
int n;
string s[N], t[N];
string x, y;
void Solve() {
  if (type == "first") {
    int flag = 0;
    cin >> n >> flag;
    for (int i = 1; i <= n; i++) {
      cin >> s[i];
      s[i] = ' ' + s[i]; // Add dummy character at beginning to make it 1-indexed
    }
    for (int i = 1; i <= n; i++) {
      t[i] = " ";
      for (int j = 1; j <= n; j++) {
        t[i] += s[j][i]; // Transpose the grid: t[i] becomes i-th column of original grid
      }
    }
    if (flag) { // If grid is connected
      int mi = 1, mx = 1;
      for (int i = 1; i <= n; i++) {
        if (s[i] < s[mi]) { // Find row with lexicographically smallest string
          mi = i;
        }
      }
      for (int i = 1; i <= n; i++) {
        if (t[i] > t[mx]) { // Find column with lexicographically largest string
          mx = i;
        }
      }
      cout << mi << ' ' << mx << '\n';
    } else { // If grid is disconnected
      int mi = 1, mx = 1;
      for (int i = 1; i <= n; i++) {
        if (s[i] > s[mx]) { // Find row with lexicographically largest string
          mx = i;
        }
      }
      for (int i = 1; i <= n; i++) {
        if (t[i] < t[mi]) { // Find column with lexicographically smallest string
          mi = i;
        }
      }
      cout << mx << ' ' << mi << '\n';
    }
  } else { // Second run: Player B
    cin >> n;
    cin >> x >> y;
    cout << (x <= y) << '\n'; // If x <= y, then connectivity is 1 (connected), otherwise 0 (disconnected)
  }
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> type;
  cin >> Tim;
  while (Tim--) {
    Solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/