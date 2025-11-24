// Problem: CF 2041 C - Cube
// https://codeforces.com/contest/2041/problem/C

/*
C. Cube
Purpose:
This code solves a 3D cube selection problem where we must select exactly n numbers from an n×n×n cube such that no two selected numbers lie in the same x, y, or z plane. The goal is to minimize the sum of selected numbers.

Algorithms/Techniques:
- Dynamic Programming with Bitmasking
- State compression DP over permutations of layers
- For each layer (x-coordinate), we assign one number to each column (y) and row (z) ensuring no conflict in x, y, z coordinates.

Time Complexity: O(n^3 * 2^(2n)) 
Space Complexity: O(2^(2n))

The solution uses a state `f[S][T]` where:
- S is a bitmask representing which rows of the current layer are used
- T is a bitmask representing which columns of the current layer are used  
- Transition builds up solutions incrementally by processing layers one by one.

*/

#include <cstdio>
#include <cstring>
#include <vector>
#pragma GCC target("popcnt")
void cmn(int &x, int y) {
  if (x > y)
    x = y;
}
const int N = 12;
int a[N + 1][N + 1], lb[1 << N], f[1 << N][1 << N];
std::vector<int> cb[N + 1];
int main() {
  int n;
  scanf("%d", &n);
  int U = (1 << n) - 1;
  for (int s = 0; s < n; ++s)
    lb[1 << s] = s + 1;
  for (int S = 0; S < 1 << n; ++S)
    cb[__builtin_popcount(S)].push_back(S);
  memset(f, 63, sizeof(f));
  f[0][0] = 0;
  for (int x = 1, Y, Z, pZ; x <= n; ++x) {
    for (int y = 1; y <= n; ++y)
      for (int z = 1; z <= n; ++z)
        scanf("%d", a[y] + z);
    for (int S : cb[x - 1])           // For each subset of rows already chosen in previous layers
      for (int T : cb[x - 1]) {       // For each subset of columns already chosen in previous layers
        Y = U ^ S;                    // Available rows in this layer
        pZ = Z = U ^ T;               // Available columns in this layer
        for (int y = Y & -Y; Y; Y ^= y, y = Y & -Y, Z = pZ)  // Iterate available rows
          for (int z = Z & -Z; Z; Z ^= z, z = Z & -Z)         // Iterate available columns
            cmn(f[S | y][T | z], f[S][T] + a[lb[y]][lb[z]]);  // Update DP state
      }
  }
  printf("%d", f[U][U]);
}


// https://github.com/VaHiX/codeForces/