/*
 * Problem URL : https://codeforces.com/contest/572/problem/A
 * Submit Date : 2025-09-04
 */

/*
 * Problem URL : https://codeforces.com/contest/572/problem/A
 * Submit Date : 2025-09-02
 */

#include <cstdio>

int main() {

  long na, nb;
  scanf("%ld %ld\n", &na, &nb);
  long k, m;
  scanf("%ld %ld\n", &k, &m);

  long low, high;
  for (long p = 0; p < na; p++) {
    long temp;
    scanf("%ld", &temp);
    if (p == k - 1) {
      low = temp;
    }
  }

  for (long p = 0; p < nb; p++) {
    long temp;
    scanf("%ld", &temp);
    if (p == nb - m) {
      high = temp;
    }
  }

  puts((low < high) ? "YES" : "NO");

  return 0;
}
