/*
 * Problem URL : https://codeforces.com/problemset/problem/2118/C
 * Submit Date : 2025-08-10
 */

#include <cstdio>
typedef long long ll;

int main() {

  const ll B = 63;

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll zv[B] = {0};

    ll beauty(0);
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      for (ll p = 0; p < B; p++) {
        if (x % 2) {
          ++beauty;
        } else {
          ++zv[p];
        }
        x /= 2;
      }
    }

    for (ll p = 0; p < B; p++) {
      ll add = (1LL << p);
      ll need = k / add;
      need = (need < zv[p] ? need : zv[p]);
      beauty += need;
      k -= need * add;
    }

    printf("%lld\n", beauty);
  }
}
