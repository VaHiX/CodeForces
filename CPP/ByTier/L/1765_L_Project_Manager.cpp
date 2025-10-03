/*
 * Problem URL : https://codeforces.com/contest/1765/problem/L
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define all(x) x.begin(), x.end()
const int mod = 998244353;
const int iinf = (int)1e9 + 10;
const ll linf = (ll)1e18 + 10;
//-----------------------------------------------------------------------------------------
const int multitest = 0;

const int maxn = 2e5 + 10, N = 3e6;
int h[N];
map<int, int> m[maxn];
int ok[7][maxn];
vector<int> w[7];
int to[7][N];

vector<string> kek{"Monday", "Tuesday",  "Wednesday", "Thursday",
                   "Friday", "Saturday", "Sunday"};

int get(int i, int d) {
  if (!m[i][d])
    return d;
  return m[i][d] = get(i, m[i][d]);
}

int nxt(int i, int d) {
  int res = N;
  for (int j = 0; j < 7; j++) {
    if (ok[j][i]) {
      res = min(res, to[j][d]);
    }
  }
  return res;
}

void ch(int i, int d) {
  int dd = nxt(i, d + 1);
  m[i][d] = get(i, dd);
}

int do_query(int i, int d) {
  d = nxt(i, d);
  int res = get(i, d);
  ch(i, res);
  return res;
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 0; i < n; i++) {
    int c;
    cin >> c;
    while (c--) {
      string s;
      cin >> s;
      for (int j = 0; j < 7; j++) {
        if (kek[j] == s)
          ok[j][i] = 1;
      }
    }
  }
  for (int i = 0; i < m; i++) {
    int a;
    cin >> a;
    a--;
    if (a < N)
      h[a] = 1;
  }
  for (int i = 0; i < N; i++) {
    if (!h[i])
      w[i % 7].push_back(i);
  }
  for (int j = 0; j < 7; j++) {
    int lst = 0;
    for (int x : w[j]) {
      while (lst <= x) {
        to[j][lst] = x;
        lst++;
      }
    }
  }

  for (int i = 0; i < k; i++) {
    int c;
    cin >> c;
    int st = 0;
    while (c--) {
      int j;
      cin >> j;
      j--;
      st = do_query(j, st) + 1;
    }
    cout << st << " ";
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int t = 1;
  if (multitest)
    cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}