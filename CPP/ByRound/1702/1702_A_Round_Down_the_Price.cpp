/*
 * Problem URL : https://codeforces.com/problemset/problem/1702/A
 * Submit Date : 2025-08-22
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1702/A
 * Submit Date : 2025-08-21
 */

#include <cstdio>
typedef long long ll;

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    ll m;
    scanf("%lld", &m);
    ll d(1);
    while (10 * d <= m) {
      d *= 10;
    }
    printf("%lld\n", m - d);
  }
}
