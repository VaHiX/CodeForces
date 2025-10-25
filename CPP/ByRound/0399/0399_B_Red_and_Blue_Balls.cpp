/*
 * Problem URL : https://codeforces.com/contest/399/problem/B
 * Submit Date : 2025-09-06
 */

#include <stdio.h>

int main() {

  int n(0);
  scanf("%d\n", &n);

  long long output(0);
  for (int k = 0; k < n; k++) {
    char temp(0);
    scanf("%c", &temp);
    if (temp == 'B') {
      output += (1ll << k);
    }
  }

  printf("%lld\n", output);
  return 0;
}
