/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <algorithm>
#include <cstdio>
#include <iostream>

int main() {

  const long mult = 100;
  int n(0), k(0);
  scanf("%d %d\n", &n, &k);
  int *array = new int[n];

  int solved(0), penalty(0);
  for (int p = 0; p < n; p++) {
    scanf("%d %d\n", &solved, &penalty);
    array[p] = mult * solved - penalty;
  }

  std::sort(array, array + n);
  int seekScore(array[n - k]), result(0);
  for (int p = 0; p < n; p++) {
    if (array[p] == seekScore) {
      ++result;
    }
  }

  printf("%d\n", result);
  return 0;
}
