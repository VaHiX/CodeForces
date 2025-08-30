/*
 * Problem URL : https://codeforces.com/problemset/problem/2037/D
 * Submit Date : 2025-08-10
 */

#include <cstdio>
#include <set>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, L;
    scanf("%ld %ld %ld", &n, &m, &L);
    std::vector<std::pair<long, long>> h(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld %ld", &h[p].first, &h[p].second);
    }
    std::vector<std::pair<long, long>> w(m);
    for (long p = 0; p < m; p++) {
      scanf("%ld %ld", &w[p].first, &w[p].second);
    }

    std::multiset<long, std::greater<long>> s;
    long idx(0), cnt(0), mjl(1);
    for (long p = 0; p < h.size(); p++) {
      while (idx < m && w[idx].first < h[p].first) {
        s.insert(w[idx].second);
        ++idx;
      }
      long dist = h[p].second - h[p].first + 2;
      while (!s.empty() && mjl < dist) {
        long add = *s.begin();
        s.erase(s.begin());
        mjl += add;
        ++cnt;
      }

      if (mjl < dist) {
        cnt = -1;
        break;
      }
    }

    printf("%ld\n", cnt);
  }
}
