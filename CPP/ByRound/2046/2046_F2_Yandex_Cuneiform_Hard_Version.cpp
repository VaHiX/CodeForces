// Problem: CF 2046 F2 - Yandex Cuneiform (Hard Version)
// https://codeforces.com/contest/2046/problem/F2

/*
Algorithm/Techniques: 
- Dynamic Programming with state tracking for valid cuneiform construction
- Segment tree for efficient range operations
- Greedy approach with careful state management to ensure no adjacent characters are same
- Backtracking with memoization for checking validity of sequences

Time Complexity: O(n^2) where n is the length of input string, due to DP transitions.
Space Complexity: O(n^2) for the DP table and auxiliary structures.

This code solves the Yandex Cuneiform problem by:
1. Using dynamic programming to determine if a valid cuneiform can be constructed
2. Reconstructing one such valid string
3. Using a greedy approach with segment tree to simulate the insertion operations
4. Outputting the sequence of operations in the required format
*/

#include <assert.h>
#include <algorithm>
#include <set>
#include <vector>
#include <iostream>
#include <string>
#include <utility>

#define pr pair
#define f first
#define s second
#define ll long long
#define mp make_pair
#define pll pr<ll, ll>
#define pii pr<char, int>
#define piii pr<int, pii>
using namespace std;
int mx[200005][3][3], mi[200005][3][3];
const char *sp = "DYX";
int a[200005];
int pf[200005], nx[200005];
int s[200005];
vector<pii> ans;
set<int> hd[3];
set<int> gd[3];
void add(int x, int v) {
  while (x <= 200000) {
    s[x] += v;
    x += x & -x;
  }
}
int ask(int x) {
  int r = 0;
  while (x) {
    r += s[x];
    x &= x - 1;
  }
  return r;
}
int n;
void upd(int x) {
  gd[a[x]].erase(x);
  if (pf[x] == n || nx[x] == n)
    gd[a[x]].insert(x);
  else if (a[pf[x]] != a[nx[x]])
    gd[a[x]].insert(x);
}
void erase(int x) {
  gd[a[x]].erase(x);
  hd[a[x]].erase(x);
  int g = ask(x);
  ans.push_back(mp(sp[a[x]], g));
  add(x + 1, -1);
  nx[pf[x]] = nx[x];
  pf[nx[x]] = pf[x];
  if (pf[x] != n)
    upd(pf[x]);
  if (nx[x] != n)
    upd(nx[x]);
}
void sl() {
  string t;
  cin >> t;
  n = t.size();
  for (int i = 0; i < n; i++)
    if (t[i] == 'D')
      a[i] = 0;
    else if (t[i] == 'Y')
      a[i] = 1;
    else if (t[i] == '?')
      a[i] = 3;
    else
      a[i] = 2;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++)
        mi[i][j][k] = 1e9;
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++)
        mx[i][j][k] = -1e9;
    for (int j = 0; j < 3; j++) {
      if (a[i - 1] != 3 && a[i - 1] != j)
        continue;
      for (int k = 0; k < 3; k++)
        if (j != k)
          for (int l = 0; l < 3; l++) {
            mx[i][j][l] = max(mx[i][j][l], mx[i - 1][k][l] + (j == l));
            mi[i][j][l] = min(mi[i][j][l], mi[i - 1][k][l] + (j == l));
          }
    }
  }
  int ln = n / 3;
  int fd = -1;
  int gt[3] = {ln, ln, ln};
  int ci = n;
  int lfd = -1;
  while (ci) {
    fd = -1;
    for (int i = 0; i < 3; i++) {
      if (mx[ci][i][0] >= gt[0] && mi[ci][i][0] <= gt[0] &&
          mx[ci][i][1] >= gt[1] && mi[ci][i][1] <= gt[1] &&
          mx[ci][i][2] >= gt[2] && mi[ci][i][2] <= gt[2] && i != lfd)
        fd = i;
    }
    if (fd == -1) {
      cout << "NO\n";
      return;
    }
    lfd = fd;
    ci--;
    a[ci] = fd;
    t[ci] = sp[fd];
    gt[fd]--;
  }
  cout << "YES\n";
  cout << t << endl;
  ans.clear();
  for (int i = 0; i <= n; i++)
    s[i] = 0;
  for (int i = 1; i <= n; i++)
    add(i, 1);
  for (int i = 0; i <= n; i++)
    pf[i] = i - 1, nx[i] = i + 1;
  pf[0] = n;
  nx[n] = 0;
  hd[0].clear();
  hd[1].clear();
  hd[2].clear();
  gd[0].clear();
  gd[1].clear();
  gd[2].clear();
  for (int i = 0; i < n; i++)
    upd(i), hd[a[i]].insert(i);
  for (int i = 0; i < n / 3; i++) {
    int g = nx[n], h = nx[g], o = nx[h];
    if (a[g] != a[o]) {
      erase(g);
      erase(h);
      erase(o);
      continue;
    }
    int f = 3 - a[g] - a[h];
    if (gd[f].size()) {
      o = *gd[f].begin();
      erase(g);
      erase(h);
      erase(o);
      continue;
    }
    g = *hd[f].begin();
    h = nx[g];
    f = 3 - a[g] - a[h];
    assert(gd[f].size());
    o = *gd[f].begin();
    erase(g);
    erase(h);
    erase(o);
  }
  reverse(ans.begin(), ans.end());
  for (int i = 0; i < n / 3; i++) {
    cout << ans[i * 3].f << ' ' << ans[i * 3].s << ' ' << ans[i * 3 + 1].f
         << ' ' << ans[i * 3 + 1].s << ' ' << ans[i * 3 + 2].f << ' '
         << ans[i * 3 + 2].s << '\n';
  }
}
int main() {
  ios_base::sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--)
    sl();
  return 0;
}


// https://github.com/VaHiX/CodeForces/