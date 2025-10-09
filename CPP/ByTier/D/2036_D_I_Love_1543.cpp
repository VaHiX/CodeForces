// Problem: CF 2036 D - I Love 1543
// https://codeforces.com/contest/2036/problem/D

/*
D. I Love 1543
Purpose: Count occurrences of the sequence "1543" in each concentric layer of a grid when traversed clockwise.

Algorithms/Techniques:
- Layer-by-layer traversal of the grid in clockwise direction.
- For each layer, collect characters in order and check for pattern "1543".
- Uses vector to store layer characters and string for pattern matching.

Time Complexity: O(n * m) per test case, where n and m are dimensions of the grid.
Space Complexity: O(n * m) for storing the grid and temporary vectors for each layer.

*/

#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
int t, n, m, i, j, k, l, x, y, c;
char s[1000005], a[1005][1005];
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++)
      scanf("%s", a[i]);
    c = 0;
    for (l = 0; l < min(n, m) / 2; l++) {
      vector<char> v;
      int u = n - 1 - l, w = m - 1 - l;
      // Traverse top row left to right
      for (j = l; j <= w; j++)
        v.push_back(a[l][j]);
      // Traverse right column top to bottom
      for (i = l + 1; i <= u; i++)
        v.push_back(a[i][w]);
      // Traverse bottom row right to left (if not a single row)
      if (u > l)
        for (j = w - 1; j >= l; j--)
          v.push_back(a[u][j]);
      // Traverse left column bottom to top (if not a single column)
      if (w > l)
        for (i = u - 1; i > l; i--)
          v.push_back(a[i][l]);
      int sz = v.size();
      string s(v.begin(), v.end());
      // Check for pattern "1543" in the layer
      for (k = 0; k < sz; k++) {
        if (s[k] == '1' && s[(k + 1) % sz] == '5' && s[(k + 2) % sz] == '4' &&
            s[(k + 3) % sz] == '3')
          c++;
      }
    }
    printf("%d\n", c);
  }
}


// https://github.com/VaHiX/codeForces/