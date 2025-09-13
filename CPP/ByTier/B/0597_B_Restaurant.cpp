/*
 * Problem URL : https://codeforces.com/problemset/problem/597/B
 * Submit Date : 2025-08-15
 */

#include <algorithm>
#include <cstdio>
#include <vector>

bool pairCompare(const std::pair<long, long> &x,
                 const std::pair<long, long> &y) {
  return x.second < y.second;
}

int main() {

  long n;
  scanf("%ld\n", &n);
  std::vector<std::pair<long, long>> rentals(n);
  for (long p = 0; p < n; p++) {
    long x, y;
    scanf("%ld %ld\n", &x, &y);
    rentals[p] = std::pair<long, long>(x, y);
  }

  sort(rentals.begin(), rentals.end(), pairCompare);

  long time(-1), total(0);
  for (long p = 0; p < n; p++) {
    if (rentals[p].first <= time) {
      continue;
    }
    time = rentals[p].second;
    ++total;
  }

  printf("%ld\n", total);

  return 0;
}
