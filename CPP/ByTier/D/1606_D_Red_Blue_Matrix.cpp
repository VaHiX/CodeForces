// Problem: CF 1606 D - Red-Blue Matrix
// https://codeforces.com/contest/1606/problem/D

/*
Algorithm/Techniques: 
This code solves the Red-Blue Matrix problem using a combination of preprocessing and sorting techniques.
The approach involves:
1. Preprocessing maximum and minimum values for each row from left to right and right to left
2. For each possible cut position (k), trying all possible colorings of rows
3. Using sorting to efficiently check the perfect coloring conditions
4. Time complexity: O(n * m * log(n)) due to sorting
5. Space complexity: O(n * m) for storing preprocessed data

Time Complexity: O(n * m * log(n)) per test case
Space Complexity: O(n * m)
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
int t, n, m;
char ch[1000010];
struct edge {
  int m1, m2, m3, m4, id;
};
bool cmp(edge a, edge b) { return a.m2 < b.m2; }
void solve() {
  scanf("%d%d", &n, &m);
  int a[n + 3][m + 3], m1, m4, m3[n + 3];
  edge f[n + 3][m + 3], p[n + 3];
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      scanf("%d", &a[i][j]);
  // Preprocessing step: for each row, compute maximum from left and minimum from left
  for (int i = 1; i <= n; i++) {
    f[i][1].m1 = a[i][1];        // Maximum from left to right for position 1
    f[i][1].m2 = a[i][1];        // Minimum from left to right for position 1
    for (int j = 2; j < m; j++) {
      f[i][j].m1 = max(f[i][j - 1].m1, a[i][j]);  // Maximum in range [1,j]
      f[i][j].m2 = min(f[i][j - 1].m2, a[i][j]);  // Minimum in range [1,j]
    }
    // Preprocessing step: for each row, compute maximum from right and minimum from right
    f[i][m - 1].m3 = a[i][m];    // Maximum from right to left for position m-1
    f[i][m - 1].m4 = a[i][m];    // Minimum from right to left for position m-1
    for (int j = m - 2; j >= 1; j--) {
      f[i][j].m3 = max(f[i][j + 1].m3, a[i][j + 1]);  // Maximum in range [j+1,m]
      f[i][j].m4 = min(f[i][j + 1].m4, a[i][j + 1]);  // Minimum in range [j+1,m]
    }
  }
  // Try each possible cut position k from 1 to m-1
  for (int i = 1; i < m; i++) {
    // For current cut position, prepare data for sorting
    for (int j = 1; j <= n; j++) {
      p[j].m1 = f[j][i].m1;   // Max in left part for row j
      p[j].m2 = f[j][i].m2;   // Min in left part for row j
      p[j].m3 = f[j][i].m3;   // Max in right part for row j  
      p[j].m4 = f[j][i].m4;   // Min in right part for row j
      p[j].id = j;           // Original row index
    }
    sort(p + 1, p + n + 1, cmp);  // Sort by minimum value in left part
    
    // Initialize global maximum and minimum for left part
    m1 = p[1].m1;   // Maximum in left part of best row
    m4 = p[1].m4;   // Minimum in left part of best row  
    m3[n] = p[n].m3;  // Max in right part from current position onwards
    for (int j = n - 1; j >= 1; j--)
      m3[j] = max(m3[j + 1], p[j].m3);  // Compute max right part values
    
    // Try all possible separations of rows (red vs blue)
    for (int j = 2; j <= n; j++) {
      m1 = max(p[j - 1].m1, m1);  // Update maximum in left part 
      m4 = min(p[j - 1].m4, m4);  // Update minimum in left part
      // Check if valid split exists: red rows have max < blue rows' min, and blue rows have min > red rows' max
      if (p[j].m2 > m1 && m4 > m3[j]) {
        printf("YES\n");
        // Color rows: first j-1 rows blue, remaining rows red
        for (int q = 1; q < j; q++)
          ch[p[q].id] = 'B';
        for (int q = j; q <= n; q++)
          ch[p[q].id] = 'R';
        ch[n + 1] = '\0';
        printf("%s %d\n", ch + 1, i);
        return;
      }
    }
  }
  printf("NO\n");
}
int main() {
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/