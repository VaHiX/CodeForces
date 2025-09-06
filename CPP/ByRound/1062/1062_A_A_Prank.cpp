/*
 * Problem URL : https://codeforces.com/contest/1062/problem/A
 * Submit Date : 2025-08-30
 */

/*
 * Problem URL : https://codeforces.com/contest/1062/problem/A
 * Submit Date : 2025-08-28
 */



#include <cstdio>
#include <vector>

int main() {

  long n;
  scanf("%ld", &n);
  std::vector<long> a(n + 2);
  a[0] = 0;
  a[n + 1] = 1001;
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &a[p]);
  }
  long cnt(1), mx(0);
  for (long p = 1; p < a.size(); p++) {
    if (a[p - 1] + 1 == a[p]) {
      ++cnt;
    } else {
      cnt = 1;
    }
    mx = (mx > cnt) ? mx : cnt;
  }

  printf("%ld\n", mx > 1 ? (mx - 2) : 0);

  return 0;
}
