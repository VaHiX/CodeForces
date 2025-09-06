/*
 * Problem URL : https://codeforces.com/contest/649/problem/A
 * Submit Date : 2025-09-02
 */

/*
 * Problem URL : https://codeforces.com/contest/649/problem/A
 * Submit Date : 2025-09-02
 */



#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  long mxd(1), cnt(0);
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    long div(1);
    while (x % (2 * div) == 0) {
      div *= 2;
    }
    if (div > mxd) {
      mxd = div;
      cnt = 1;
    } else if (div == mxd) {
      ++cnt;
    }
  }

  printf("%ld %ld\n", mxd, cnt);

  return 0;
}
