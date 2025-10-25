/*
 * Problem URL : https://codeforces.com/contest/426/problem/A
 * Submit Date : 2025-09-05
 */

#include <cstdio>
#include <iostream>

int main() {

  long currentMax(0), total(0);

  long n(0), s(0);
  scanf("%ld %ld\n", &n, &s);

  while (n--) {
    int temp(0);
    scanf("%d", &temp);
    if (temp > currentMax) {
      currentMax = temp;
    }
    total += temp;
  }

  total -= currentMax;
  if (total <= s) {
    puts("YES");
  } else {
    puts("NO");
  }

  return 0;
}
