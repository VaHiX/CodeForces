// Problem: CF 1746 G - Olympiad Training
// https://codeforces.com/contest/1746/problem/G

/*
 * Problem: G. Olympiad Training
 * 
 * Purpose:
 *   This solution determines the maximum total usefulness of tasks Anton can solve 
 *   under given constraints on task types and deadlines, while respecting the 
 *   constraint that he can solve at most one task per day.
 * 
 * Algorithm:
 *   - For each topic, sort tasks by usefulness (descending).
 *   - Binary search on the maximum achievable usefulness using a randomized 
 *     approach combined with greedy selection.
 *   - The core idea is to simulate a greedy selection process where we try to 
 *     select tasks for each topic, using the deadline constraint to determine 
 *     if it's valid to place a task on a given day.
 * 
 * Techniques:
 *   - Greedy algorithm with randomized optimization.
 *   - Binary search on the answer.
 *   - Union-Find (Disjoint Set Union) for efficiently managing task scheduling.
 *   - Sorting by usefulness for topic-specific greedy selection.
 * 
 * Time Complexity: O(n * log(n) * log(max_val)) where n is the number of tasks and 
 *                   max_val is a large constant for the randomization.
 * 
 * Space Complexity: O(n) for storing tasks and auxiliary structures.
 */

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#define For(i, a, b) for (int i = (a); i <= (b); ++i)
#define Rep(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
using namespace std;
inline int read() {
  char c = getchar();
  int x = 0;
  bool f = 0;
  for (; !isdigit(c); c = getchar())
    f ^= !(c ^ 45);
  for (; isdigit(c); c = getchar())
    x = (x << 1) + (x << 3) + (c ^ 48);
  return f ? -x : x;
}
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
typedef pair<int, int> pii;
typedef vector<int> vi;
#define maxn 1000005
#define inf 0x3f3f3f3f
int n, a[3];
vector<pii> s[3];
int bound[3][2];
mt19937_64 rnd(1919810);
int cnt[3], mid[3];
int res;
int tp[3];
int fa[maxn];
int gf(int x) {
  while (x ^ fa[x])
    x = fa[x] = fa[fa[x]];
  return x;
}
void check() {
  For(i, 0, 2) cnt[i] = 0, tp[i] = s[i].size();
  For(i, 0, n + 1) fa[i] = i;
  int sum = 0;
  res = 0;
  while (sum < a[0] + a[1] + a[2]) {
    int t = -1, mx = -(1ll << 63);
    For(i, 0, 2) if (tp[i] && s[i][tp[i] - 1].se + mid[i] > mx) mx =
        s[i][tp[i] - 1].se + mid[i],
                                                                t = i;
    if (t == -1)
      break;
    int d = s[t][tp[t] - 1].fi;
    --tp[t];
    d = gf(n - d);
    if (d < n)
      fa[d] = d + 1, ++cnt[t], ++sum, res += ((mx - mid[t]) >> 25);
  }
}
int work() {
  n = read();
  For(i, 0, 2) s[i].clear();
  For(i, 0, 2) a[i] = read();
  int V = n * 200 + 1;
  For(i, 0, n - 1) {
    int r = read(), t = read(), d = read();
    r = (r << 25) | (rnd() % V);
    s[t - 1].pb(mkp(d, r));
  }
  For(i, 0, 2)
      sort(s[i].begin(), s[i].end(), [](pii a, pii b) { return a.se < b.se; });
  if (!a[0] && !a[1] && !a[2])
    return 0;
  For(i, 0, 2) bound[i][1] = (1ll << 56), bound[i][0] = -bound[i][1];
  while (1) {
    int r = 0;
    For(i, 0, 2) mid[i] = 0;
    For(i, 0, 2) For(a, 0, 1) For(b, 0, 1) {
      int j = (i + 1) % 3, k = (j + 1) % 3;
      int x = bound[j][a], y = -bound[k][b];
      if (bound[i][0] <= y - x && y - x <= bound[i][1])
        mid[j] += y, mid[k] += x, ++r;
    }
    For(i, 0, 2) mid[i] /= r;
    For(i, 0, 2) {
      int j = (i + 1) % 3, k = (j + 1) % 3;
      if (bound[i][0] > mid[j] - mid[k] || mid[j] - mid[k] > bound[i][1])
        return -1;
    }
    check();
    if (cnt[0] + cnt[1] + cnt[2] != a[0] + a[1] + a[2])
      return -1;
    if (cnt[0] == a[0] && cnt[1] == a[1] && cnt[2] == a[2])
      return res;
    For(i, 0, 2) {
      int j = (i + 1) % 3, k = (j + 1) % 3;
      if (cnt[j] > a[j] && cnt[k] < a[k])
        bound[i][1] = min(bound[i][1], mid[j] - mid[k] - 1);
      if (cnt[j] < a[j] && cnt[k] > a[k])
        bound[i][0] = max(bound[i][0], mid[j] - mid[k] + 1);
    }
  }
}
signed main() {
  int T = read();
  while (T--)
    cout << work() << "\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/