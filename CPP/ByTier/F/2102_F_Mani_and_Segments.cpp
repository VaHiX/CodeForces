/*
 * Problem URL : https://codeforces.com/problemset/problem/2102/F
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define pii pair<int, int>
#define f first
#define s second
#define chmin(a, b) a = min(a, b)
#define chmax(a, b) a = max(a, b)
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define all(x) x.begin(), x.end()
#define vec vector

void solve() {
  int n;
  cin >> n;
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vec<vec<int>> bound(2, vec<int>(n));

  auto fillin = [&](int m) {
    vec<int> hi(n), lo(n);
    stack<int> sh, sl;
    for (int i = 0; i < n; i++) {
      while (sh.size() && a[i] > a[sh.top()]) {
        sh.pop();
      }
      while (sl.size() && a[i] < a[sl.top()]) {
        sl.pop();
      }
      hi[i] = (sh.empty() ? -1 : sh.top());
      lo[i] = (sl.empty() ? -1 : sl.top());
      sh.push(i);
      sl.push(i);
    }
    bound[m][0] = 0;
    for (int i = 1; i < n; i++) {
      bound[m][i] = bound[m][i - 1];
      if (a[i] > a[i - 1] && hi[i] < hi[i - 1]) {
        chmax(bound[m][i], hi[i - 1] + 1);
      }
      if (a[i] < a[i - 1] && lo[i] < lo[i - 1]) {
        chmax(bound[m][i], lo[i - 1] + 1);
      }
    }
    if (m == 1) {
      vec<int> b2 = bound[1];
      for (int i = 0; i < n; i++) {
        bound[m][i] = n - b2[n - i - 1] - 1;
      }
    }
    reverse(all(a));
  };
  fillin(0);
  fillin(1);

  int last_r = bound[1][0];
  ll ans = last_r + 1;
  for (int i = 1; i < n; i++) {
    // cout<<ans<<'\n';
    // cout<<bound[0][i]+1<<' '<<bound[1][i]+1<<'\n';
    ans += (bound[1][i] - i + 1);
    ans += (ll)(bound[1][i] - last_r) * (i - bound[0][i]);
    last_r = bound[1][i];
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;
  while (t--) {
    solve();
  }

  /*
  lis and lds share one element
  fix the element i
  calc L: min left bound possible (it's monotonic)
  the lds and lis leading to this element are greedily calculated
  as i increases, L increases

  calculate R too

  count is (i-L+1)*(R-i+1)
  avoid duplicates

  as i increases, L is non-dec, R is non-inc
  so first add all ranges not including prev element
  then add all ranges including new right bounds

  o(n)
  */
}