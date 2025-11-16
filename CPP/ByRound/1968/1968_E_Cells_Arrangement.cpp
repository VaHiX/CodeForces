// Problem: CF 1968 E - Cells Arrangement
// https://codeforces.com/contest/1968/problem/E

/*
Purpose: This code solves the problem of arranging n cells on an n×n grid to maximize the number of distinct Manhattan distances between any pair of cells.

Algorithm/Techniques: 
- The strategy is to place cells in a way that maximizes the variety of Manhattan distances.
- For n=2 and n=3, specific hardcoded arrangements are used.
- For n≥4, the pattern places cells at positions:
  - (1,1) and (n,n) to get distance 2*(n-1)
  - (1,2) and (n,2) to get distances 1 and 2*(n-2)
  - Additional cells at (1,3), (1,4), ..., (1,n-2) to generate more unique distances

Time Complexity: O(n) per test case, as we only output a fixed number of lines and loop linearly for larger n.
Space Complexity: O(1), as no extra space is used apart from a few variables.

*/
#include <iostream>

using namespace std;
using ll = long long;
const int MOD = 1E9 + 7;
const int INF = 1E9;
const ll INFLL = 1E18;
int n;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  for (int test = 1; test <= t; test++) {
    cin >> n;
    if (n == 2) {
      cout << "1 1\n2 2\n"; // Special case for n=2
    } else if (n == 3) {
      cout << "1 1\n1 2\n3 3\n"; // Special case for n=3
    } else {
      cout << "1 1\n"
           << n << " " << n << "\n" 
           << "1 2\n"
           << n << " 2\n";
      // Generate additional points to maximize distance variety
      for (int i = 2; i < n - 2; i++) {
        cout << "1 " << i + 1 << "\n";
      }
    }
    cout << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/