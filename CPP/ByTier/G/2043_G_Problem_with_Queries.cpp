/*
 * Problem URL : https://codeforces.com/contest/2043/problem/G
 * Submit Date : 2025-08-25
 */

#include <bits/allocator.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
#include <immintrin.h>
#define ft first
#define sc second
#define all(x) x.begin(), x.end()
using ll = long long;
using ld = long double;
using dd = double;
using ui = unsigned;

using namespace std;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
const ll mod = 998244353, inf = 1e18;
const int N = 100001, k = 220, b = (N + k - 1) / k;
int n;
int pref[N][k + 1];
ll bl[k + 1][k + 1];
int a[N];
void add(int ind, int x) {
  for (int i = ind; i >= 0; i--) {
    for (int j = ind + 1; j <= k; j++)
      bl[i][j] += pref[x][j];
    for (int j = ind + 1; j <= k; j++)
      bl[i][j] -= pref[x][i];
  }
  for (int i = ind + 1; i <= k; i++)
    pref[x][i]++;
}
void del(int ind, int x) {
  for (int i = ind + 1; i <= k; i++)
    pref[x][i]--;
  for (int i = ind; i >= 0; i--) {
    for (int j = ind + 1; j <= k; j++)
      bl[i][j] -= pref[x][j];
    for (int j = ind + 1; j <= k; j++)
      bl[i][j] += pref[x][i];
  }
}
int cnt[N];
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i]--;
    add(i / b, a[i]);
  }
  ll q, last = 0;
  cin >> q;
  while (q--) {
    int tp, l, r;
    cin >> tp >> l >> r;
    l = (l + last) % n + 1;
    r = (r + last) % n + 1;
    if (tp == 1) {
      l--;
      r--;
      del(l / b, a[l]);
      add(l / b, a[l] = r);
    } else {
      if (l > r)
        swap(l, r);
      l--;
      int il = l / b + 1, ir = r / b;
      last = 0;
      if (il < ir) {
        last = bl[il][ir];
        for (int i = l; i < b * il; i++) {
          last += cnt[a[i]] + pref[a[i]][ir] - pref[a[i]][il];
          cnt[a[i]]++;
        }
        for (int i = b * ir; i < r; i++) {
          last += cnt[a[i]] + pref[a[i]][ir] - pref[a[i]][il];
          cnt[a[i]]++;
        }
        for (int i = l; i < b * il; i++)
          cnt[a[i]] = 0;
        for (int i = b * ir; i < r; i++)
          cnt[a[i]] = 0;
      } else {
        for (int i = l; i < r; i++) {
          last += cnt[a[i]];
          cnt[a[i]]++;
        }
        for (int i = l; i < r; i++)
          cnt[a[i]] = 0;
      }
      last = ll(r - l) * (r - l - 1) / 2 - last;
      cout << last << " ";
    }
  }
}
