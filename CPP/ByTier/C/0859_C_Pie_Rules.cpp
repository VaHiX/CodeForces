#include <cstdio>

int x[55], n, i = 1, a, b;
main() {
  scanf("%d", &n);
  while (i++ <= n)
    scanf("%d", x + i);
  while (i--) {
    a > b ? b += x[i] : a += x[i];
  }
  printf("%d %d", a < b ? a : b, a < b ? b : a);
}