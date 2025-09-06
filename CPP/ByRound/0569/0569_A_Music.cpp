/*
 * Problem URL : https://codeforces.com/contest/569/problem/A
 * Submit Date : 2025-09-04
 */

/*
 * Problem URL : https://codeforces.com/contest/569/problem/A
 * Submit Date : 2025-09-02
 */



#include <cstdio>

int main() {

  long T, S, q;
  scanf("%ld %ld %ld\n", &T, &S, &q);

  long t(S), n(0);
  while (t < T) {
    t *= q;
    ++n;
  }
  printf("%ld\n", n);

  return 0;
}
