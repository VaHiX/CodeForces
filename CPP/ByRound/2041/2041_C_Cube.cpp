/*
 * Problem URL : https://codeforces.com/contest/2041/problem/C
 * Submit Date : 2025-08-25
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
    for (int S : cb[x - 1])
      for (int T : cb[x - 1]) {
        Y = U ^ S;
        pZ = Z = U ^ T;
        for (int y = Y & -Y; Y; Y ^= y, y = Y & -Y, Z = pZ)
          for (int z = Z & -Z; Z; Z ^= z, z = Z & -Z)
            cmn(f[S | y][T | z], f[S][T] + a[lb[y]][lb[z]]);
      }
  }
  printf("%d", f[U][U]);
}