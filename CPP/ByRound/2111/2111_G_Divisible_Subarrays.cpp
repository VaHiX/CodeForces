/*
 * Problem URL : https://codeforces.com/problemset/problem/2111/G
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;
#define UL unsigned long long
#define L long long
#define LD long double
#define REP(i, a, b) for (int i = a; i < (b); ++i)
#define RREP(i, a, b) for (int i = a; i > (b); --i)
#define SZ(x) (int)(x).size()
#define YES "YES\n"
#define NO "NO\n"
#define COUT cout <<
template <class T = L> vector<T> pullN(int n) {
  vector<T> res(n);
  for (T &v : res)
    cin >> v;
  return res;
}
#define LOG2(x) (63 - __builtin_clzll(x))
#define MAX(x, v) x = max(x, v)
#define MIN(x, v) x = min(x, v)

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  auto nums = pullN<int>(n);
  vector<int> pos(n);
  REP(i, 0, n) {
    nums[i]--;
    pos[nums[i]] = i;
  }
  vector<vector<int>> rng(n, vector<int>(4));
  set<int> occ;
  RREP(v, n - 1, -1) {
    int i = pos[v];
    auto p = occ.lower_bound(i);
    rng[i][1] = (p == occ.begin()) ? 0 : *prev(p) + 1;
    rng[i][2] = (p == occ.end()) ? n : *p;
    occ.insert(i);
  }
  occ.clear();
  REP(v, 0, n) {
    int i = pos[v];
    auto p = occ.lower_bound(rng[i][1]);
    rng[i][0] = (p == occ.begin()) ? 0 : *prev(p) + 1;
    auto p2 = occ.lower_bound(rng[i][2]);
    rng[i][3] = (p2 == occ.end()) ? n - 1 : *p2 - 1;
    occ.insert(i);
  }
  int pw = LOG2(n) + 1;
  vector<vector<int>> resL(pw, vector<int>(n, -1)), resR(pw, vector<int>(n, n));
  auto push = [&](int l, int m, int r) {
    REP(j, 1, pw) {
      int o = max(l, m - (1 << j) + 1);
      MAX(resL[j][o], r);
      if (o == l)
        break;
    }
    REP(j, 1, pw) {
      int o = min(r, (m - 1) + (1 << j) - 1);
      MIN(resR[j][o], l);
      if (o == r)
        break;
    }
  };
  REP(i, 0, n) {
    if (rng[i][2] != n) {
      push(rng[i][1], rng[i][2], rng[i][3]);
    }
    if (rng[i][1] != 0) {
      push(rng[i][0], rng[i][1], rng[i][2] - 1);
    }
  }
  REP(j, 2, pw) {
    int o = (1 << (j - 1));
    deque<pair<int, int>> curr;
    REP(i, 0, n) {
      int v = resL[j][i];
      if (v != -1) {
        while (curr.size() && curr.back().first <= v) {
          curr.pop_back();
        }
        curr.push_back({v, i});
      }
      while (curr.size() && curr.front().second + o <= i) {
        curr.pop_front();
      }
      if (curr.size()) {
        resL[j][i] = curr.front().first;
      }
    }
    curr.clear();
    RREP(i, n - 1, -1) {
      int v = resR[j][i];
      if (v != -1) {
        while (curr.size() && curr.back().first >= v) {
          curr.pop_back();
        }
        curr.push_back({v, i});
      }
      while (curr.size() && curr.front().second - o >= i) {
        curr.pop_front();
      }
      if (curr.size()) {
        resR[j][i] = curr.front().first;
      }
    }
    REP(i, 0, n) {
      MIN(resR[j][i], resR[j - 1][i]);
      MAX(resL[j][i], resL[j - 1][i]);
    }
  }
  int q;
  cin >> q;
  REP(qi, 0, q) {
    if (qi && !(qi % 10)) {
      cout.flush();
    }
    int l, r;
    cin >> l >> r;
    l--;
    r--;
    if (l == r) {
      COUT NO;
      continue;
    }
    int sz = r - l + 1;
    int p = LOG2(sz);
    if (resL[p][l] >= r || resR[p][r] <= l) {
      COUT YES;
      continue;
    }
    COUT NO;
  }
}
/*


10
8 10 5 6 7 9 3 2 4 1
1
3 9


*/