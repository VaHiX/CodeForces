/*
 * Problem URL : https://codeforces.com/problemset/problem/1108/A
 * Submit Date : 2025-08-13
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  while (n--) {
    long ls, rs, lt, rt;
    scanf("%ld %ld %ld %ld\n", &ls, &rs, &lt, &rt);
    printf("%ld %ld\n", ls, lt + (ls == lt));
  }

  return 0;
}
