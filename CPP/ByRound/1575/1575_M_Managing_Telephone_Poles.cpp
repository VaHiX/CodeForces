// Problem: CF 1575 M - Managing Telephone Poles
// https://codeforces.com/contest/1575/problem/M

/*
Problem: M. Managing Telephone Poles
Algorithms/Techniques: Dynamic Programming with Convex Hull Trick
Time Complexity: O((n + m) * (n + m)) 
Space Complexity: O(n * m)

This code calculates the sum of squared Euclidean distances from each point in a grid
to the nearest telephone pole. It uses a preprocessing step to store pole positions,
followed by a dynamic programming approach with convex hull trick optimization
to efficiently compute the minimal distance for each row.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
int n, m, x[2005][2005], c[2005], p[2005], q[2005], b[2005];
char s[2005];
long long ans;

int main() {
  cin >> n >> m;
  // Preprocessing: For each column, store the row indices of poles
  for (int i = 0; i <= n; i++) {
    scanf("%s", s);
    for (int j = 0; j <= m; j++)
      if (s[j] == '1')
        x[j][c[j]++] = i;
  }
  
  // Main DP loop: For each row, compute the minimal squared distance
  for (int i = 0; i <= n; i++) {
    int h = 0, t = -1;
    // Process all columns that have at least one pole
    for (int j = 0; j <= m; j++)
      if (c[j]) {
        // Maintain pointer p[j] to the closest pole to row i in column j
        while (p[j] < c[j] - 1 &&
               abs(x[j][p[j]] - i) >= abs(x[j][p[j] + 1] - i))
          p[j]++;
        // Compute squared distance from current row to the nearest pole
        b[j] = (x[j][p[j]] - i) * (x[j][p[j]] - i) + j * j;
        // Convex Hull Trick optimization: Remove redundant lines from the hull
        while (h < t && 1ll * (b[j] - b[q[t]]) * (q[t] - q[t - 1]) <=
                            1ll * (b[q[t]] - b[q[t - 1]]) * (j - q[t]))
          t--;
        q[++t] = j;
      }
    // For each column, use the convex hull to find minimum value of
    // -2*q[h]*j + b[q[h]] + j*j for all j, where h is the current pointer
    for (int j = 0; j <= m; j++) {
      while (h < t &&
             -2 * q[h] * j + b[q[h]] >= -2 * q[h + 1] * j + b[q[h + 1]])
        h++;
      ans += -2 * q[h] * j + b[q[h]] + j * j;
    }
  }
  cout << ans;
}


// https://github.com/VaHiX/codeForces/