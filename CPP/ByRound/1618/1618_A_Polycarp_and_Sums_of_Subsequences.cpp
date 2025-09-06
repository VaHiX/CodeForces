/*
 * Problem URL : https://codeforces.com/problemset/problem/1618/A
 * Submit Date : 2025-08-19
 */

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {

  const int N = 7;
  long t;
  scanf("%ld", &t);
  while (t--) {
    std::vector<ll> a(N);
    for (int p = 0; p < N; p++) {
      scanf("%lld", &a[p]);
    }
    printf("%lld %lld %lld\n", a[0], a[1], a.back() - a[0] - a[1]);
  }
}
