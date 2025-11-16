// Problem: CF 2081 C - Quaternary Matrix
// https://codeforces.com/contest/2081/problem/C

/*
 * Problem: C. Quaternary Matrix
 * 
 * Purpose:
 *   This code finds the minimum number of elements to change in a quaternary matrix (0,1,2,3) 
 *   to make it "good", where good means that the XOR of all elements in each row and column is 0.
 * 
 * Algorithms/Techniques:
 *   - Uses the property of XOR to identify mismatches in rows/columns.
 *   - Tracks positions of mismatches (non-zero XOR) in rows and columns.
 *   - Greedily resolves mismatches by changing elements strategically.
 *   - Uses greedy methods to minimize total changes.
 * 
 * Time Complexity:
 *   O(n * m) per test case due to linear processing of matrix elements and fixed operations 
 *   on XOR mismatches (since there are at most 3 types of mismatches).
 * 
 * Space Complexity:
 *   O(n + m) for storing positions of mismatched rows/columns.
 */
#include <cstdio>
#include <iostream>
using namespace std;

int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}

int reac() {
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    ch = getchar();
  }
  return ch - '0';
}

const int N = 1010;
int t, n, m, a[N][N];
int s1[4][N], s2[4][N], t1[4], t2[4];

int main() {
  t = read();
  while (t--) {
    n = read(), m = read();
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        a[i][j] = reac();
      }
    }

    // Precompute row XORs and column XORs, then store indices of mismatches
    for (int i = 1; i <= n; i++) {
      int x = 0;
      for (int j = 1; j <= m; j++) {
        x ^= a[i][j];
      }
      if (x)
        s1[x][++t1[x]] = i;  // Store row index with non-zero XOR
    }
    
    for (int j = 1; j <= m; j++) {
      int x = 0;
      for (int i = 1; i <= n; i++) {
        x ^= a[i][j];
      }
      if (x)
        s2[x][++t2[x]] = j;  // Store column index with non-zero XOR
    }

    int ans = 0;
    // Resolve mismatches in pairs (xor of 1,2,3 with same value)
    for (int i = 1; i <= 3; i++) {
      while (t1[i] && t2[i]) {
        ans++;
        a[s1[i][t1[i]]][s2[i][t2[i]]] ^= i;
        t1[i]--, t2[i]--;
      }
    }

    // Resolve 3-way mismatches using XOR properties
    for (int i = 1; i <= 3; i++) {
      int j = i % 3 + 1, k = j % 3 + 1;
      // Pair one mismatch from i with two from j,k
      while (t1[i] && t2[j] && t2[k]) {
        ans += 2;
        a[s1[i][t1[i]]][s2[j][t2[j]]] ^= j;
        a[s1[i][t1[i]]][s2[k][t2[k]]] ^= k;
        t1[i]--, t2[j]--, t2[k]--;
      }
      // Pair one mismatch from j,k with one from i
      while (t2[i] && t1[j] && t1[k]) {
        ans += 2;
        a[s1[j][t1[j]]][s2[i][t2[i]]] ^= j;
        a[s1[k][t1[k]]][s2[i][t2[i]]] ^= k;
        t2[i]--, t1[j]--, t1[k]--;
      }
    }

    // Handle 2-way mismatches for 3 different values
    for (int i = 1; i <= 3; i++) {
      for (int j = 1; j <= 3; j++) {
        if (i == j)
          continue;
        // Use pairs of mismatches to resolve
        while (t1[i] >= 2 && t2[j] >= 2) {
          ans += 3;
          int x = s1[i][t1[i]], y = s2[j][t2[j]];
          t1[i]--, t2[j]--;
          a[s1[i][t1[i]]][y] ^= j;
          a[x][s2[j][t2[j]]] ^= i;
          a[s1[i][t1[i]]][s2[j][t2[j]]] ^= (i ^ j);
          t1[i]--, t2[j]--;
        }
      }
    }

    // Resolve remaining single mismatches (i.e. set remaining to 0)
    for (int i = 1; i <= 3; i++) {
      while (t1[i]) {
        ans++;
        a[s1[i][t1[i]]][1] ^= i;
        t1[i]--;
      }
      while (t2[i]) {
        ans++;
        a[1][s2[i][t2[i]]] ^= i;
        t2[i]--;
      }
    }

    cout << ans << "\n";
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        cout << a[i][j];
      }
      cout << "\n";
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/