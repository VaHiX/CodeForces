/*
 * Problem URL : https://codeforces.com/contest/1267/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
#define fi first
#define se second
typedef long long ll;
priority_queue<pair<ll, int>> q;
int n;
ll t[N];
bool v[N];
struct ch {
  ll x;
  int id, tp;
  bool operator<(const ch &a) const { return x < a.x; }
} p[N * 2];
ll ans;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  ll x, y;
  for (int i = 1; i <= n; i++) {
    cin >> x >> y >> t[i];
    p[i * 2 - 1] = {x + t[i], i, 1}, p[i * 2] = {y, i, -1};
  }
  sort(p + 1, p + n * 2 + 1);
  x = 0;
  for (int i = 1; i <= n * 2; i++) {
    while (q.size() && v[q.top().se])
      q.pop();
    if (q.size())
      ans += (p[i].x - x) / (-q.top().fi),
          x += ((p[i].x - x) / (-q.top().fi)) * (-q.top().fi);
    if (p[i].tp == 1) {
      q.push({-t[p[i].id], p[i].id});
      if (x + t[p[i].id] <= p[i].x)
        x = p[i].x, ans++;
    } else
      v[p[i].id] = 1; // cout<<ans<<" "<<x<<"\n";
  }
  cout << ans << '\n';
  return 0;
}