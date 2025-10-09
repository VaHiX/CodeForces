/*
 * Problem URL : https://codeforces.com/problemset/problem/768/A
 * Submit Date : 2025-08-15
 */

#include <iostream>
#include <vector>

int main() {

  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::vector<long> a(n);
  long min(1e9 + 1), max(-1e9 - 1);
  for (long p = 0; p < n; p++) {
    std::cin >> a[p];
    min = (min < a[p]) ? min : a[p];
    max = (max > a[p]) ? max : a[p];
  }

  long count(0);
  for (long p = 0; p < n; p++) {
    count += (min < a[p] && a[p] < max);
  }
  std::cout << count << std::endl;

  return 0;
}
