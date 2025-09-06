/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1560/C
 * Submit Date : 2025-08-24
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll k;
    scanf("%lld", &k);
    ll idx(0);
    while (idx * idx < k) {
      ++idx;
    }
    ll row(idx), col(idx);
    ll rem = k - (idx - 1) * (idx - 1);
    if (rem <= idx) {
      row = rem;
    } else {
      col = 2 * idx - rem;
    }
    printf("%lld %lld\n", row, col);
  }
}
