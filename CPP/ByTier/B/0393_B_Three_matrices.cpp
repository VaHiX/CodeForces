/*
 * Problem URL : https://codeforces.com/contest/393/problem/B
 * Submit Date : 2025-09-06
 */

#include <cstdio>
#include <vector>

int main() {

  int n(0);
  scanf("%d", &n);
  std::vector<std::vector<int>> input(n, std::vector<int>(n, 0));

  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      scanf("%d", &input[row][col]);
    }
  }

  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      printf("%.5lf ", 0.5 * (input[row][col] + input[col][row]));
    }
    puts("");
  }

  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      printf("%.5lf ", 0.5 * (input[row][col] - input[col][row]));
    }
    puts("");
  }

  return 0;
}
