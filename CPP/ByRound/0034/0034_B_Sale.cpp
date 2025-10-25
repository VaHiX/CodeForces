/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <algorithm>
#include <cstdio>

int main() {

  int n(0), m(0);
  scanf("%d %d", &n, &m);
  int *price = new int[n];
  for (int k = 0; k < n; k++) {
    scanf("%d", price + k);
  }
  std::sort(price, price + n);
  long total(0);
  for (int k = 0; k < m; k++) {
    if (price[k] < 0) {
      total -= price[k];
    } else {
      break;
    }
  }
  printf("%ld\n", total);
  return 0;
}
