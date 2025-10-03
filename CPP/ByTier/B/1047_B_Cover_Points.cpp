/*
 * Problem URL : https://codeforces.com/problemset/problem/1047/B
 * Submit Date : 2025-08-22
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1047/B
 * Submit Date : 2025-08-22
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  long mxs(0);
  while (n--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    long sum = x + y;
    mxs = (mxs > sum) ? mxs : sum;
  }

  printf("%ld\n", mxs);

  return 0;
}
