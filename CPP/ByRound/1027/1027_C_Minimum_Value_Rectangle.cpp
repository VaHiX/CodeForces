#include <bits/stdc++.h>
#define N 1234567
using namespace std;

int t, n, x, y, last, a[N];
int main() {
  scanf("%d", &t);
  while (t--) {
    x = y = -1;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
      scanf("%d", &a[i]);
    sort(a, a + n);
    for (int i = 1; i < n; ++i)
      if (a[i] == a[i - 1]) {
        if (x == -1)
          x = a[i];
        else if (y == -1)
          y = a[i];
        else if ((double)a[i] / last < (double)y / x)
          x = last, y = a[i];
        last = a[i++];
      }
    printf("%d %d %d %d\n", x, x, y, y);
  }
  return 0;
}