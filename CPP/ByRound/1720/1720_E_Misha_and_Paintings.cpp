// Problem: CF 1720 E - Misha and Paintings
// https://codeforces.com/contest/1720/problem/E

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <set>

#define ll long long
#define eb emplace_back
#define mk make_pair
#define N 509
using namespace std;
int n, k, dx[N * N], dy[N * N], ux[N * N], uy[N * N], a[N][N];
set<int> s;
signed main() {
  // Read input: matrix size n and desired number of distinct elements k
  scanf("%d%d", &n, &k);
  
  // Initialize arrays to store min/max row/column indices for each value
  memset(dx, 0x3f, sizeof(dx)), memset(dy, 0x3f, sizeof(dy));
  for (int i = 1; i <= n; i++)
    for (int j = 1, x; j <= n; j++) {
      scanf("%d", &x), dx[x] = min(dx[x], i), ux[x] = max(ux[x], i),
                       dy[x] = min(dy[x], j), uy[x] = max(uy[x], j);
      s.insert(x);
    }
  
  // Count number of distinct values in the matrix
  int m = s.size();
  
  // If already have at most k distinct values, we need k - m operations to add more
  if (m <= k) {
    printf("%d\n", k - m);
    return 0;
  }
  
  // Try all possible square submatrix sizes from 1 to n
  for (int len = 1; len <= n; len++) {
    // Reset the 2D difference array
    memset(a, 0, sizeof(a));
    
    // For each distinct value in the matrix, calculate how many submatrices of size len contain it
    for (int i = 1; i <= n * n; i++)
      if (ux[i]) {
        // Determine the rectangle that covers all positions of value i
        int lx = max(1, ux[i] - len + 1), rx = min(n - len + 1, dx[i]),
            ly = max(uy[i] - len + 1, 1), ry = min(n - len + 1, dy[i]);
        // If valid rectangle and it fits the matrix
        if (lx <= rx && ly <= ry)
          // Update the difference array for submatrix updates
          a[lx][ly]++, a[rx + 1][ly]--, a[lx][ry + 1]--, a[rx + 1][ry + 1]++;
      }
    
    // Compute prefix sum to get actual counts
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        a[i][j] = a[i][j] + a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        // If a submatrix of size len has either (m - k) or (m - k + 1) distinct values
        // it means we can reduce the number of distinct values to exactly k with one operation
        if (i + len - 1 <= n && j + len - 1 <= n &&
            (a[i][j] == m - k || a[i][j] == m - k + 1)) {
          printf("1\n");
          return 0;
        }
      }
    }
  }
  
  // If no single operation can reduce it to k distinct elements,
  // then we need at least 2 operations
  printf("2\n");
  return 0;
}
/*
Algorithm: Minimize operations to get exactly k distinct values.
Time Complexity: O(n^4)
Space Complexity: O(n^2)
*/

// https://github.com/VaHiX/CodeForces/