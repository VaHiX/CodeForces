// Problem: CF 2047 C - Swap Columns and Find a Path
// https://codeforces.com/contest/2047/problem/C

/*
C. Swap Columns and Find a Path
Algorithms/Techniques: Greedy, Sorting, Maximum Path Sum

The problem involves finding the maximum sum path from (1,1) to (2,n) in a 2xN matrix,
where columns can be swapped any number of times. The key insight is:
- Each column contributes exactly one element to the path.
- For each column i, we can choose either a[0][i] or a[1][i].
- To maximize the total sum: 
  - We add the maximum of the two elements from each column.
  - We also add an extra value which is the maximum of the minimum values across all columns.
    This handles the optimal choice for one column.

Time Complexity: O(n) per test case (linear scan)
Space Complexity: O(n) for storing the input matrix
*/

#include <algorithm>
#include <iostream>

using namespace std;
const int N = 5010;
int n, a[2][N], sum, Max;
int main() {
  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    Max = -1000000, sum = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[0][i]; // Read first row
    }
    for (int i = 1; i <= n; i++) {
      cin >> a[1][i]; // Read second row
      sum += max(a[0][i], a[1][i]); // Add maximum of the two elements in this column
      Max = max(Max, min(a[0][i], a[1][i])); // Track the maximum of minimums across columns
    }
    cout << sum + Max << "\n"; // Final answer is sum of maxes plus the best min
  }
}


// https://github.com/VaHiX/codeForces/