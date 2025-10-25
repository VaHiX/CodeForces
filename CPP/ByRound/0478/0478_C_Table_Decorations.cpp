/*
 * Problem URL : https://codeforces.com/contest/478/problem/C
 * Submit Date : 2025-09-05
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

int main() {

  std::vector<long long> array(3);
  scanf("%lld %lld %lld\n", &array[0], &array[1], &array[2]);
  sort(array.begin(), array.end());
  long long result = (array[0] + array[1] + array[2]) / 3;
  if (array[0] + array[1] < result) {
    result = array[0] + array[1];
  }
  printf("%lld\n", result);

  return 0;
}
