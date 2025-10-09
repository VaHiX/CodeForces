/*
 * Problem URL : https://codeforces.com/contest/317/problem/B
 * Submit Date : 2025-09-06
 */

#include <cstdio>
#include <memory.h>

const int M = 64;

int main() {
  int n, t, ants[M * 2 + 1][M * 2 + 1] = {0}, ants_temp[M * 2 + 1][M * 2 + 1];
  scanf("%d%d", &n, &t);
  ants[M][M] = n;
  bool find = (n != 0);
  while (find) {
    find = false;

    memset(ants_temp, 0, sizeof(ants_temp));

    for (int i = 0; i <= M * 2; ++i) {
      for (int j = 0; j <= M * 2; ++j) {
        if (ants[i][j] >= 4) {
          find = true;
          ants_temp[i - 1][j] += ants[i][j] / 4;
          ants_temp[i + 1][j] += ants[i][j] / 4;
          ants_temp[i][j - 1] += ants[i][j] / 4;
          ants_temp[i][j + 1] += ants[i][j] / 4;
        }
        ants_temp[i][j] += ants[i][j] % 4;
      }
    }

    memcpy(ants, ants_temp, sizeof(ants));
  }

  while (t--) {
    int x, y;
    scanf("%d%d", &x, &y);
    printf("%d\n",
           (x >= -M && y >= -M && x <= M && y <= M) ? ants[M + x][M + y] : 0);
  }
  return 0;
}
