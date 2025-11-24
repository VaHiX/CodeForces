// Problem: CF 2093 D - Skibidi Table
// https://codeforces.com/contest/2093/problem/D

/*
D. Skibidi Table
Algorithm: 
    This problem uses a recursive approach to map coordinates to numbers and vice versa 
    in an N x N matrix filled in a specific order (Z-order or Morton order).
    
    The filling process:
        1. Divide the square matrix into four equal quadrants.
        2. Fill them in this order: top-left, bottom-right, bottom-left, top-right.
        3. Recursively apply the same logic to each quadrant until 2x2 matrices are reached,
           which are filled as: top-left=1, bottom-right=2, bottom-left=3, top-right=4.

    Time Complexity: O(n * q) per test case where n is the size of the matrix (2^n x 2^n), 
                     and q is the number of queries.
                     Each query involves traversing a path from the full matrix down to 
                     a cell or back from the cell to the matrix level, taking at most O(n).
    Space Complexity: O(1) - only using basic integer variables and no additional data structures.

*/

#include <iostream>
#include <string>

using namespace std;

void solve() {
  int n, q;
  cin >> n >> q;
  while (q--) {
    string s;
    cin >> s;
    if (s[0] == '-') { // Query type: find number at coordinates x,y
      int x, y;
      cin >> x >> y;
      long long ans = 0;
      int m = n;
      int ad = 1 << (n - 1); // Half the size of current square being processed
      while (m--) {
        ans <<= 2; // Shift left by 2 bits to accommodate next quadrant code (0-3)
        if (x > ad && y > ad) // Bottom right quadrant
          x -= ad, y -= ad, ans += 1;
        if (x > ad && y <= ad) // Bottom left quadrant
          x -= ad, ans += 2;
        if (x <= ad && y > ad) // Top right quadrant
          y -= ad, ans += 3;
        ad >>= 1; // Move to next smaller square
      }
      ans++; // Adjust for 1-based numbering of final element
      cout << ans << '\n';
    } else { // Query type: find coordinates for a given number d
      long long d;
      cin >> d;
      d--; // Convert to 0-indexed
      int x = 1, y = 1;
      int ad = 1; // Current square size (initially 1x1)
      while (d) {
        int now = d & 3; // Extract last two bits to get quadrant code
        if (now == 1) // Bottom right quadrant
          y += ad, x += ad;
        if (now == 2) // Bottom left quadrant
          x += ad;
        if (now == 3) // Top right quadrant
          y += ad;
        d >>= 2; // Move to parent level
        ad <<= 1; // Double square size
      }
      cout << x << ' ' << y << '\n';
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/codeForces/