/*
 * Problem URL : https://codeforces.com/contest/1526/problem/C1
 * Submit Date : 2025-09-08
 */

#include <cstdio>
#include <queue>
#include <vector>

int main() {

  long n;
  scanf("%ld", &n);
  std::priority_queue<long, std::vector<long>, std::greater<long>> pq;
  long long cur(0);
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    cur += x;
    pq.push(x);
    while ((cur < 0) && (!pq.empty())) {
      cur -= pq.top();
      pq.pop();
    }
  }

  printf("%ld\n", pq.size());
}
