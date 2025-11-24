// Problem: CF 1689 D - Lena and Matrix
// https://codeforces.com/contest/1689/problem/D

/*
Algorithm: 
The problem asks to find a cell (a,b) that minimizes the maximum Manhattan distance to all black cells.
We use the key insight that for a given cell (a,b), the Manhattan distance to a black cell (x,y) is |a-x|+|b-y|.
For all black cells, we want to minimize max_i(|a-x_i|+|b-y_i|).

Key idea:
- For any point (a,b), we can rewrite the expression |a-x|+|b-y| using four cases based on the signs.
- The maximum Manhattan distance from (a,b) to all black cells is:
   max( (a+b) - (x+y), -(a+b) + (x+y), (a-b) - (x-y), -(a-b) + (y-x) )
   Which simplifies to:
   max( (a+b) - (x+y), -(a+b) + (x+y), (a-b) - (x-y), -(a-b) + (y-x) )
   max( (a+b) - (x+y), (x+y) - (a+b), (a-b) - (x-y), (y-x) - (a-b) )
   max( (a+b) - (x+y), (x+y) - (a+b), (a-b) - (x-y), -(a-b) + (y-x) )
   
Let us define:
- S1 = max(i + j) over all black cells (i,j)
- S2 = max(-i - j) over all black cells (i,j)
- S3 = max(i - j) over all black cells (i,j)
- S4 = max(j - i) over all black cells (i,j)

For any point (a,b), the maximum Manhattan distance is:
max(S1 - a - b, -S2 + a + b, S3 - a + b, -S4 + a - b)

This can be rewritten as:
max(S1 - a - b, S2 + a + b, S3 - a + b, S4 - a + b)

We are trying to minimize this over all possible (a,b) in the matrix.

Optimization:
We compute the minimum value of the above expression over all (a,b) in the matrix.
Since the expression contains absolute values, we evaluate it for all cells,
and find the cell that minimizes the maximum distance.

Complexity:
Time Complexity: O(n * m) per test case, as we scan the matrix twice.
Space Complexity: O(1) additional space, only using a few variables.

*/

#include <algorithm>
#include <iostream>

#define D(x) cerr << #x << ":\n" << x << endl
using namespace std;
const int N = 1111;
signed main() {
  ios::sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    static int n, m;
    cin >> n >> m;
    int m1, m2, m3, m4, ans = 1e9, x, y;
    m1 = m2 = m3 = m4 = -1e9;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        char c;
        cin >> c;
        if (c == 'B') {
          // Update the maximum values for the four expressions derived from Manhattan distance
          m1 = max(m1, i + j);      // max(i + j) for black cells
          m2 = max(m2, -i - j);     // max(-i - j) for black cells
          m3 = max(m3, i - j);      // max(i - j) for black cells
          m4 = max(m4, j - i);      // max(j - i) for black cells
        }
      }
    }
    // For each cell (i,j), compute the maximum Manhattan distance to all black cells
    // and keep track of the one with minimum such distance
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        int t = max(m1 - i - j, max(m2 + i + j, max(m3 - i + j, m4 - j + i)));
        if (t < ans)
          ans = t, x = i, y = j;
      }
    cout << x << " " << y << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/