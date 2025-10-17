/*
 * Problem URL : https://codeforces.com/problemset/problem/479/C
 * Submit Date : 2025-08-13
 */

#include <algorithm>
#include <cstdio>
#include <vector>

bool pairCompare(std::pair<long, long> a, std::pair<long, long> b) {
  return (a.first < b.first) || (a.first == b.first && a.second < b.second);
}

int main() {

  long n;
  scanf("%ld\n", &n);
  std::vector<std::pair<long, long>> dates(n);

  for (long p = 0; p < n; p++) {
    long x, y;
    scanf("%ld %ld\n", &x, &y);
    dates[p] = std::pair<long, long>(x, y);
  }

  sort(dates.begin(), dates.end(), pairCompare);

  long minDate(0);

  for (long p = 0; p < n; p++) {
    if (minDate <= dates[p].second) {
      minDate = dates[p].second;
    } else {
      minDate = dates[p].first;
    }
  }

  printf("%ld\n", minDate);

  return 0;
}
