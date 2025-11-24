// Problem: CF 1070 L - Odd Federalization
// https://codeforces.com/contest/1070/problem/L

/*
Algorithm: 
This solution determines the minimum number of states (r) to split the cities such that every city has an even number of "inner" roads (roads connecting cities within the same state).
The approach uses the concept of linear algebra over GF(2) (Galois Field of order 2).
1. First, check if all degrees are even. If they are, one state is sufficient (r=1).
2. If not, construct a system of linear equations modulo 2 based on the adjacency matrix.
3. The system is solved using Gaussian elimination to find a valid partition into 2 states.

Time Complexity: O(n^3 + m), where n is number of cities and m is number of roads.
Space Complexity: O(n^2), due to the adjacency matrix representation.
*/
#include <stdio.h>
#include <string.h>
#include <bitset>
#include <utility>

using namespace std;
#define max_n 2000
int TID;
int n;
int m;
bitset<max_n + 2> g[max_n + 2]; // Adjacency matrix represented as bitsets
int de[max_n + 2]; // Degree of each node
bool ans1;
bool ans[max_n + 2]; // Result array indicating which state each city belongs to

int main() {
#ifndef ONLINE_JUDGE
  freopen("CF1070L_1.in", "r", stdin);
  freopen("CF1070L_1.out", "w", stdout);
#endif
  scanf("%d", &TID);
  while (TID--) {
    scanf("%d%d", &n, &m);
    // Initialize bitsets
    for (int i = 1; i <= n; ++i)
      g[i].reset();
    // Reset degrees
    memset(de, 0, sizeof(de));
    
    // Read edges and update adjacency matrix and degrees
    for (int i = 1, u, v; i <= m; ++i) {
      scanf("%d%d", &u, &v);
      g[u][v] = g[v][u] = 1; // Mark edge in adjacency matrix
      ++de[u];
      ++de[v];
    }
    
    // Check if all degrees are even - if so, one state is sufficient
    ans1 = true;
    for (int i = 1; i <= n; ++i) {
      if (de[i] & 1) {
        ans1 = false;
        break;
      }
    }
    if (ans1) {
      printf("1\n");
      for (int i = 1; i <= n; ++i)
        printf("%d ", 1);
      printf("\n");
      continue;
    }
    
    // Construct extended matrix for Gaussian elimination
    // Add a column for the constants (degree parity)
    for (int i = 1; i <= n; ++i)
      g[i][i] = g[i][n + 1] = de[i] & 1;
      
    // Perform Gaussian elimination
    for (int i = 1, r; i <= n; ++i) {
      r = 0;
      // Find pivot row
      for (int j = i; j <= n; ++j) {
        if (g[j][i]) {
          r = j;
          break;
        }
      }
      // Swap rows if needed
      swap(g[i], g[r]);
      
      // Eliminate column entries below pivot
      for (int j = i + 1; j <= n; ++j) {
        if (g[j][i])
          g[j] ^= g[i]; // XOR operation in GF(2)
      }
    }
    
    // Back substitution to get solution
    for (int i = n; i >= 1; --i) {
      ans[i] = g[i][n + 1];
      for (int j = i + 1; j <= n; ++j) {
        if (g[i][j])
          ans[i] ^= ans[j]; // XOR operation in GF(2)
      }
    }
    
    printf("2\n");
    for (int i = 1; i <= n; ++i) {
      if (ans[i])
        printf("1 ");
      else
        printf("2 ");
    }
    printf("\n");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/