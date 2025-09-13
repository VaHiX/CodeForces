/*
 * Problem URL : https://codeforces.com/contest/600/problem/B
 * Submit Date : 2025-09-04
 */

/*
 * Problem URL : https://codeforces.com/contest/600/problem/B
 * Submit Date : 2025-09-02
 */

#include <algorithm>
#include <iostream>
#include <vector>

int main() {

  long n, m;
  std::cin >> n >> m;
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    std::cin >> a[p];
  }

  std::vector<long> b(m);
  for (long p = 0; p < m; p++) {
    std::cin >> b[p];
  }

  sort(a.begin(), a.end());
  for (long p = 0; p < m; p++) {
    long ans = upper_bound(a.begin(), a.end(), b[p]) - a.begin();
    std::cout << ans << " ";
  }

  return 0;
}
