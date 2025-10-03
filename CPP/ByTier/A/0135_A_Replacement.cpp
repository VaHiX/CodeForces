/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

int main() {

  long n;
  scanf("%ld", &n);
  std::vector<long> array(n);
  long maxElement(0), maxPos(0);

  for (long p = 0; p < n; p++) {
    scanf("%ld", &array[p]);
    if (array[p] > maxElement) {
      maxElement = array[p];
      maxPos = p;
    }
  }

  if (maxElement == 1) {
    array[maxPos] = 2;
  } else {
    array[maxPos] = 1;
  }

  sort(array.begin(), array.end());
  for (long p = 0; p < n; p++) {
    printf("%ld ", array[p]);
  }

  return 0;
}
