/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <algorithm>
#include <cstdio>
#include <iostream>

int main() {

  long count[4] = {0};

  long n;
  scanf("%ld", &n);
  for (long p = 0; p < n; p++) {
    int temp;
    scanf("%d", &temp);
    ++count[temp];
  }
  std::sort(count, count + 4);
  printf("%ld\n", count[1] + count[2]);

  return 0;
}
