/*
 * Problem URL : https://codeforces.com/contest/1938/problem/L
 * Submit Date : 2025-09-07
 */

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
typedef long long LL;
LL fastpo(LL x, LL n, LL mod) {
  LL res = 1;
  while (n) {
    if (n & 1) {
      res = res * x % mod;
    }
    x = x * x % mod;
    n /= 2;
  }
  return res;
}
const int N = 200022;
int a[N];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    if (i) {
      a[i] ^= a[0];
    }
  }
  vector<int> b(30);
  int cnt = 0;
  for (int i = 1; i < n; i++) {
    int x = a[i];
    for (int j = 0; j < 30; j++) {
      if (b[j] != 0) {
        if (x & (1 << j)) {
          x ^= b[j];
        }
      }
    }
    if (x != 0) {
      int pos = ilogb(x & -x);
      b[pos] = x;
      cnt++;
    }
  }
  int pw = cnt == 0 ? 0 : n * cnt - (cnt + 1) * cnt / 2;
  printf("%d\n", fastpo(2, pw, mod));
}