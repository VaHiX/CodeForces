/*
 * Problem URL : https://codeforces.com/contest/1046/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define per(i, r, l) for (int i = r; i >= l; i--)
const int MX = 3e5 + 7;
const int mod = 1e9 + 7;
using namespace std;
ll qpow(ll a, ll b, ll MOD = mod) {
  for (ll ans = 1;; a = a * a % MOD, b >>= 1) {
    if (b & 1)
      ans = ans * a % MOD;
    if (!b)
      return ans;
  }
}
ll inv(ll a, ll MOD = mod) { return qpow(a, MOD - 2, MOD); }
ll __gcm(ll a, ll b) { return a * b / __gcd(a, b); }
ll cnt[MX], ans = 0;
int X[MX], K, dq[MX];
void upd(int x, int pos) {
  for (; pos < MX; pos += pos & -pos) {
    cnt[pos] += x;
  }
}
int get_sum(int pos) {
  ll sum = 0;
  while (pos) {
    sum += cnt[pos];
    pos -= pos & -pos;
  }
  return sum;
}
struct node {
  int x, r, q, L, R;
  void get() {
    cin >> x >> r >> q;
    // x=rand()%3;
    // r=rand()%mod+10;
    // q=rand()%10;
    L = 0, R = 0;
  }
} p[MX];
bool cmp(node a, node b) { return a.r > b.r; }
bool cmp1(node a, node b) { return a.q > b.q; }

void Dic(int l, int r) {
  // cout<<l<<" "<<r<<endl;
  if (l == r)
    return;
  int mid = l + r >> 1;
  Dic(l, mid);
  Dic(mid + 1, r);
  int lt = 0, rt = 0;
  // memset(cnt,0,sizeof cnt);
  for (int i = mid + 1, j = l; i <= r; i++) {
    // cout<<i<<endl;
    while (j <= mid && p[j].q - p[i].q > K)
      j++;
    while (j <= mid && abs(p[j].q - p[i].q) <= K) {
      dq[rt++] = j;
      upd(1, p[j].x);
      j++;
    }
    while (lt < rt && abs(p[dq[lt]].q - p[i].q) > K) {
      upd(-1, p[dq[lt]].x);
      lt++;
    }
    ans += get_sum(p[i].R) - get_sum(p[i].L - 1);
  }
  for (int j = lt; j < rt; j++) {
    upd(-1, p[dq[j]].x);
  }
  inplace_merge(p + l, p + mid + 1, p + r + 1, cmp1);
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int n;
  cin >> n >> K;
  int top = 0;
  for (int i = 1; i <= n; i++) {
    p[i].get();
    X[++top] = p[i].x;
    X[++top] = p[i].x + p[i].r;
    X[++top] = p[i].x - p[i].r;
  }
  sort(X + 1, X + top + 1);
  top = unique(X + 1, X + top + 1) - X - 1;
  for (int i = 1; i <= n; i++) {
    p[i].L = lower_bound(X + 1, X + top + 1, p[i].x - p[i].r) - X;
    p[i].R = lower_bound(X + 1, X + top + 1, p[i].x + p[i].r) - X;
    p[i].x = lower_bound(X + 1, X + top + 1, p[i].x) - X;
  }
  sort(p + 1, p + n + 1, cmp);
  Dic(1, n);
  cout << ans << endl;
}
