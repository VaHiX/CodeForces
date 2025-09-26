/*
 * Problem URL : https://codeforces.com/contest/2034/problem/G1
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<pll> vpll;

#define PB push_back
#define PF push_front
#define PPB pop_back
#define PPF pop_front
#define X first
#define Y second
#define MP make_pair
#define all(x) (x).begin(), (x).end()

const int mod = 1e9 + 7; // 998244353;
const int inf = 1e9 + 7;
const ll INF = 1e18 + 7;
const int logo = 20;
const int MAXN = 1e6 + 7;
const int off = 1 << logo;
const int trsz = off << 1;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct ev {
  int x, y, i;
};

bool cmp(ev &a, ev &b) {
  if (a.x != b.x)
    return a.x < b.x;
  if (a.y != b.y)
    return a.y < b.y;
  return a.i < b.i;
}

vector<ev> a, e;
int ans[MAXN];

void solve() {
  int n;
  cin >> n;
  a.clear(), e.clear();
  for (int i = 1; i <= n; i++) {
    int l, r;
    cin >> l >> r;
    a.PB({l, r, i});
  }
  sort(all(a), cmp);
  bool dobar = 1;
  for (int i = 1; i < n; i++) {
    if (a[i].x <= a[i - 1].y)
      dobar = 0;
  }

  if (dobar) {
    cout << 1 << "\n";
    for (int i = 0; i < n; i++)
      cout << 1 << " ";
    cout << "\n";
    return;
  }

  for (auto &x : a) {
    e.PB({x.x, -x.y, -x.i});
    e.PB({x.y, -x.y, x.i});
  }

  sort(all(e), cmp);
  int c[3] = {0, 0, 0}, to[3] = {0, 0, 0};
  dobar = 1;
  int zadnji = -1;
  for (auto [p, _, i] : e) {
    if (p != zadnji and c[1] != 1 and c[2] != 1 and c[1] + c[2] > 0) {
      dobar = 0;
      break;
    }
    zadnji = p;

    if (i < 0) {
      int ja = 1;
      if (c[1] == 0 or c[1] > 1)
        ja = 1;
      else if (c[2] == 0 or c[2] > 1)
        ja = 2;
      else if (to[1] < to[2])
        ja = 1;
      else
        ja = 2;

      c[ja]++;
      to[ja] = max(to[ja], abs(_));
      ans[-i] = ja;
    } else
      c[ans[i]]--;
  }

  if (dobar) {
    cout << 2 << "\n";
    for (int i = 1; i <= n; i++)
      cout << ans[i] << " ";
    cout << "\n";
    return;
  }

  for (int i = 1; i <= n; i++)
    ans[i] = 0;

  zadnji = -1;
  int col = 1;
  for (int i = 0; i < n;) {
    if (zadnji < a[i].x)
      zadnji = a[i].x;

    int tko = i;
    while (i < n and a[i].x <= zadnji) {
      if (a[i].y > a[tko].y)
        tko = i;
      i++;
    }
    ans[a[tko].i] = col;
    zadnji = a[tko].y;
    col ^= 3;
  }

  cout << "3\n";
  for (int i = 1; i <= n; i++)
    cout << ans[i] + 1 << " ";
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int tt = 1;
  cin >> tt;
  while (tt--)
    solve();
  return 0;
}
