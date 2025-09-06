/*
 * Problem URL : https://codeforces.com/contest/507/problem/A
 * Submit Date : 2025-09-05
 */

/*
 * Problem URL : https://codeforces.com/contest/507/problem/A
 * Submit Date : 2025-09-02
 */



#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long n, k;
  scanf("%ld %ld\n", &n, &k);
  std::vector<std::pair<long, long>> days(n);
  for (long p = 0; p < n; p++) {
    long temp;
    scanf("%ld", &temp);
    days[p] = std::pair<long, long>(temp, 1 + p);
  }
  sort(days.begin(), days.end());
  std::vector<long> learn;
  long remTime(k);
  for (long p = 0; p < n; p++) {
    if (days[p].first > remTime) {
      break;
    }
    remTime -= days[p].first;
    learn.push_back(days[p].second);
  }

  printf("%ld\n", learn.size());
  for (long p = 0; p < learn.size(); p++) {
    printf("%ld ", learn[p]);
  }
  puts("");

  return 0;
}
