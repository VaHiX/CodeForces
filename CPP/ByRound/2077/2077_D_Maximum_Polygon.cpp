/*
 * Problem URL : https://codeforces.com/problemset/problem/2077/D
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
int T;
int n;
typedef long long ll;
const int MAXN = 2e5 + 10;
int a[MAXN], b[MAXN];
vector<int> max(vector<int> a, vector<int> b) {
  for (int i = 0; i < min(a.size(), b.size()); ++i) {
    if (a[i] > b[i])
      return a;
    if (b[i] > a[i])
      return b;
  }
  return a.size() > b.size() ? a : b;
}
int st[MAXN], top;
vector<int> solve(int x) {
  vector<int> v;
  v.push_back(0);
  for (int i = 1; i <= n; ++i)
    if (a[i] <= x)
      v.push_back(a[i]);
  int m = v.size() - 1;
  vector<int> pos(m + 1);
  top = 0;
  for (int i = m; i; --i) {
    while (top && v[st[top]] <= v[i])
      --top;
    pos[i] = st[top];
    st[++top] = i;
  }
  vector<ll> sum(m + 1);
  for (int i = 1; i <= m; ++i) {
    sum[i] = sum[i - 1] + v[i];
  }
  ll ret = sum[m];
  if (2 * x >= ret)
    return vector<int>();
  int p = 1;
  vector<int> ans;
  while (p <= m) {
    ll s = sum[pos[p] - 1] - sum[p - 1];
    if (pos[p] && 2 * x < ret - s) {
      ret -= s;
      p = pos[p] - 1;
    } else
      ans.push_back(v[p]);
    ++p;
  }
  return ans;
}
int main() {
  // freopen("subsequence.in", "r", stdin);
  // freopen("subsequence.out", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
      b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    vector<int> ans;
    for (int i = 1; i <= n; ++i) {
      if (i == n || 2 * b[i] < b[i + 1])
        ans = max(ans, solve(b[i]));
    }
    if (ans.empty())
      cout << "-1\n";
    else {
      cout << ans.size() << '\n';
      for (auto v : ans)
        cout << v << ' ';
      cout << '\n';
    }
  }
  return 0;
}