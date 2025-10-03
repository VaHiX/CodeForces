/*
 * Problem URL : https://codeforces.com/problemset/problem/1949/A
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(a) (a).begin(), (a).end()
#ifdef DEBUG
template <class T> ostream &operator<<(ostream &out, vector<T> a) {
  out << '[';
  for (T x : a)
    out << x << ',';
  return out << ']';
}
template <class T> vector<T> ary(T *a, int l, int r) {
  return vector<T>{a + l, a + 1 + r};
}
template <class T> void debug(T x) { cerr << x << endl; }
template <class T, class... S> void debug(T x, S... y) {
  cerr << x << ' ', debug(y...);
}
#else
#define debug(...) void()
#endif
const int N = 405;
struct MaxClique {
  bool g[N][N];
  int n, dp[N], st[N][N], ans, res[N];
  void init(int n) {
    this->n = n;
    memset(g, false, sizeof(g));
  }

  void addedge(int u, int v, int w) { g[u][v] = w; }
  int stk[N];
  bool dfs(int sz, int num) {
    if (sz == 0) {
      if (num > ans) {
        ans = num;
        copy(stk + 1, stk + 1 + num, res + 1);
        return true;
      }
      return false;
    }
    for (int i = 0; i < sz; i++) { // 在第num层的集合中枚举一个点i
      if (sz - i + num <= ans)
        return false; // 剪枝1
      int u = st[num][i];
      if (dp[u] + num <= ans)
        return false; // 剪枝2
      int cnt = 0;
      for (
          int j = i + 1; j < sz;
          j++) { // 在第num层遍历在i之后的且与i所相连的点，并且加入第num+1层集合
        if (g[u][st[num][j]])
          st[num + 1][cnt++] = st[num][j];
      }
      stk[num + 1] = u;
      if (dfs(cnt, num + 1))
        return true;
    }
    return false;
  }

  int solver() {
    ans = 0;
    memset(dp, 0, sizeof(dp));
    for (int i = n; i >= 1; i--) {
      int cnt = 0;
      for (int j = i + 1; j <= n; j++) { // 初始化第1层集合
        if (g[i][j])
          st[1][cnt++] = j;
      }
      stk[1] = i;
      dfs(cnt, 1);
      dp[i] = ans;
    }
    return ans;
  }
} S;
const double eps = 1e-9;
int n, k, id[N][N];
pair<int, int> p[N * N];
double r;
int main() {
  scanf("%d%lf", &n, &r);
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      if (min({i, j, n - i, n - j}) > r - eps) {
        id[i][j] = ++k, p[k] = {i, j};
      }
    }
  }
  S.init(k);
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      if (!id[i][j])
        continue;
      for (int x = 0; x <= n; x++) {
        for (int y = 0; y <= n; y++) {
          if (!id[x][y])
            continue;
          int dx = i - x, dy = j - y;
          double dis = sqrt(dx * dx + dy * dy);
          if (dis + eps > r + r)
            S.addedge(id[i][j], id[x][y], 1);
        }
      }
    }
  }
  int ans = S.solver();
  cout << ans << endl;
  for (int i = 1; i <= ans; i++) {
    auto [x, y] = p[S.res[i]];
    printf("%d %d\n", x, y);
  }
  return 0;
}