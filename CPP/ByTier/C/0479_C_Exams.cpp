// Problem: CF 479 C - Exams
// https://codeforces.com/contest/479/problem/C

/*
Algorithm: Greedy
Approach:
- We are given n exams, each with a scheduled date (a_i) and an early date (b_i) when the exam can be taken.
- Each exam's record is stamped with the scheduled date (a_i), regardless of when it's taken.
- We must arrange the order of exams so that the dates of the records are non-decreasing.
- To achieve this, we sort exams by their scheduled dates (and early dates as tie breaker).
- Then, for each exam in sorted order:
  * If the current earliest possible date to take the exam (b_i) is after or equal to the latest recorded date (minDate), we take it on b_i.
  * Otherwise, we take it on a_i, and update minDate to a_i.

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(n) for storing the dates.

*/
#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

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


// https://github.com/VaHiX/CodeForces/