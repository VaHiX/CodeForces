/*
 * Problem URL : https://codeforces.com/problemset/problem/2061/H2
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h> //0xnnb
using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
const int N = 4005, M = 20005;
int T, n, m, ee, vex[N], nums[N], tot, vis[N], mchx[N], mchy[N];
int ee2, vex2[N], mchs[N], mcht[N], rt[N], cnt, anscnt, ans[N][N];
int nows, nowt, cnt1, cnt2, dep[N], las[N], q[N], hh, tt;
char s[N], t[N];
bool flag0, flag1, flag, poss[N], post[N], vis2[N];
struct Node {
  int u, v, next;
} e[M], e2[M];
void add(int u, int v) {
  e[++ee].u = u, e[ee].v = v;
  e[ee].next = vex[u], vex[u] = ee;
}
void add2(int u, int v) {
  e2[++ee2].u = u, e2[ee2].v = v;
  e2[ee2].next = vex2[u], vex2[u] = ee2;
}
void dfs(int u, int val) {
  vis[u] = val;
  nums[++tot] = u;
  for (int i = vex[u]; i; i = e[i].next) {
    int v = e[i].v;
    if (vis[v]) {
      if (vis[v] == val)
        flag = 0;
      continue;
    }
    dfs(v, 3 - val);
  }
}
bool dfs2(int u) {
  for (int i = vex[u]; i; i = e[i].next) {
    int v = e[i].v;
    if (vis2[v])
      continue;
    vis2[v] = 1;
    if ((!mchy[v]) || dfs2(mchy[v])) {
      mchx[u] = v, mchy[v] = u;
      return 1;
    }
  }
  return 0;
}
bool dfs3(int u) {
  vis[u] = 1;
  int v = mchs[u];
  int u2 = mcht[v];
  if ((!u2) || vis[u2] == 2) {
    vis[u] = 2;
    return 0;
  }
  if (vis[u2] == 1 || dfs3(u2)) {
    mcht[u] = v;
    mcht[v] = u;
    vis[u] = 2;
    return 1;
  }
  vis[u] = 2;
  return 0;
}
int find(int x) {
  if (rt[x] == x)
    return x;
  return rt[x] = find(rt[x]);
}
void unionn(int x, int y) {
  int xx = find(x), yy = find(y);
  if (rt[xx] != yy) {
    rt[xx] = yy;
    add2(x, y), add2(y, x);
  }
}
void dfs4(int u, int fa) {
  dep[u] = dep[fa] + 1;
  for (int i = vex2[u]; i; i = e2[i].next) {
    int v = e2[i].v;
    if (v == fa)
      continue;
    dfs4(v, u);
  }
}
int bfs(int u, bool op) {
  for (int i = 1; i <= n * 2; i++)
    vis[i] = las[i] = 0;
  hh = 1, tt = 0;
  q[++tt] = u;
  vis[u] = 1;
  while (hh <= tt) {
    int u = q[hh++];
    if ((op == 0 && mchs[u]) || (op == 1 && mcht[u])) {
      return u;
    }
    for (int i = vex2[u]; i; i = e2[i].next) {
      int v = e2[i].v;
      if (vis[v])
        continue;
      q[++tt] = v;
      las[v] = u;
      vis[v] = 1;
    }
  }
}
bool cmp(int x, int y) { return dep[x] > dep[y]; }
void solve() {
  n = read(), m = read();
  scanf("%s%s", s + 1, t + 1);
  for (int i = 1; i <= m; i++) {
    int u = read(), v = read();
    add(u, v), add(v, u);
  }
  flag = 1;
  for (int i = 1; i <= n; i++) {
    if (s[i] != t[i]) {
      flag = 0;
      break;
    }
  }
  if (flag) {
    printf("Yes\n0\n");
    tot = 0;
    for (int i = 1; i <= n; i++) {
      if (s[i] == '1')
        nums[++tot] = i;
    }
    for (int i = 1; i <= tot; i++) {
      printf("%d ", nums[i]);
    }
    printf("\n");
    return;
  }
  flag0 = flag1 = 1;
  for (int i = 1; i <= n; i++) {
    if (vis[i])
      continue;
    flag = 1, tot = 0;
    dfs(i, 1);
    int sums = 0, sumt = 0;
    for (int j = 1; j <= tot; j++) {
      int u = nums[j];
      if (s[u] == '1')
        sums++;
      if (t[u] == '1')
        sumt++;
    }
    if (sums != sumt) {
      flag0 = flag1 = 0;
      break;
    }
    if (flag) {
      int sums1 = 0, sumt1 = 0;
      int sums2 = 0, sumt2 = 0;
      for (int j = 1; j <= tot; j++) {
        int u = nums[j];
        if (s[u] == '1') {
          if (vis[u] == 1)
            sums1++;
          else
            sums2++;
        }
        if (t[u] == '1') {
          if (vis[u] == 1)
            sumt1++;
          else
            sumt2++;
        }
      }
      if (sums1 != sumt1 || sums2 != sumt2)
        flag0 = 0;
      if (sums1 != sumt2 || sums2 != sumt1)
        flag1 = 0;
    }
    for (int j = 1; j <= tot; j++) {
      int u = nums[j];
      if (s[u] == '0')
        continue;
      for (int k = 1; k <= tot; k++)
        vis2[nums[k]] = 0;
      if (!dfs2(u)) {
        flag0 = flag1 = 0;
        break;
      }
    }
    for (int j = 1; j <= tot; j++) {
      int u = nums[j];
      mchs[u] = mchx[u], mchs[u + n] = mchy[u];
      if (mchs[u])
        mchs[u] += n;
      mchx[u] = mchy[u] = 0;
    }
    for (int j = 1; j <= tot; j++) {
      int u = nums[j];
      if (t[u] == '0')
        continue;
      for (int k = 1; k <= tot; k++)
        vis2[nums[k]] = 0;
      if (!dfs2(u)) {
        flag0 = flag1 = 0;
        break;
      }
    }
    for (int j = 1; j <= tot; j++) {
      int u = nums[j];
      mcht[u] = mchx[u], mcht[u + n] = mchy[u];
      if (mcht[u])
        mcht[u] += n;
      mchx[u] = mchy[u] = 0;
    }
  }
  if ((!flag0) && (!flag1)) {
    printf("No\n");
    return;
  }
  printf("Yes\n");
  for (int i = 1; i <= n; i++) {
    vis[i] = 0;
    if (!flag0) {
      swap(mcht[i], mcht[i + n]);
      if (mcht[i])
        mcht[i] += n;
      if (mcht[i + n])
        mcht[i + n] -= n;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i])
      dfs3(i);
  }
  for (int i = 1; i <= n * 2; i++)
    rt[i] = i;
  for (int i = 1; i <= n; i++) {
    if (mchs[i]) {
      unionn(i, mchs[i]);
      poss[i] = 1;
    }
    if (mcht[i]) {
      unionn(i, mcht[i]);
      if (flag0)
        post[i] = 1;
      else
        post[mcht[i]] = 1;
    }
  }
  for (int i = 1; i <= ee; i++) {
    int u = e[i].u, v = e[i].v;
    unionn(u, v + n);
  }
  anscnt = n * 2;
  if (!flag0)
    anscnt--;
  for (int i = 1; i <= n * 2; i++) {
    nums[i] = i;
    if (rt[i] == i)
      dfs4(i, 0);
  }
  sort(nums + 1, nums + n * 2 + 1, cmp);
  for (int i = 1; i <= n * 2; i++) {
    int u = nums[i];
    if ((!mchs[u]) && (!mcht[u]))
      continue;
    cnt++;
    if (mcht[u]) {
      nowt = u;
      if (!post[nowt])
        nowt = mcht[nowt];
      nows = bfs(nowt, 0);
      if (!poss[nows]) {
        nows = mchs[nows];
        las[nows] = mchs[nows];
      }
      int tmp = 0;
      ans[tmp][cnt] = nows;
      for (int j = 1; j <= cnt1 * 2; j++) {
        tmp++;
        ans[tmp][cnt] = mchs[ans[tmp - 1][cnt]];
      }
      for (int j = las[nows]; j; j = las[j]) {
        ans[++tmp][cnt] = j;
      }
      while (tmp < anscnt) {
        tmp++;
        ans[tmp][cnt] = mcht[ans[tmp - 1][cnt]];
      }
      cnt1++;
    } else {
      nows = u;
      if (!poss[nows])
        nows = mchs[nows];
      nowt = bfs(nows, 1);
      if (!post[nowt]) {
        nowt = mcht[nowt];
        las[nowt] = mcht[nowt];
      }
      int tmp = anscnt;
      ans[tmp][cnt] = nowt;
      for (int j = 1; j <= cnt2 * 2; j++) {
        tmp--;
        ans[tmp][cnt] = mcht[ans[tmp + 1][cnt]];
      }
      for (int j = las[nowt]; j; j = las[j]) {
        ans[--tmp][cnt] = j;
      }
      while (tmp > 0) {
        tmp--;
        ans[tmp][cnt] = mchs[ans[tmp + 1][cnt]];
      }
      cnt2++;
    }
    mchs[mchs[nows]] = 0;
    mchs[nows] = 0;
    mcht[mcht[nowt]] = 0;
    mcht[nowt] = 0;
  }
  printf("%d\n", anscnt);
  for (int i = 0; i <= anscnt; i++) {
    for (int j = 1; j <= cnt; j++) {
      if (ans[i][j] > n)
        ans[i][j] -= n;
      printf("%d ", ans[i][j]);
    }
    printf("\n");
  }
}
void clear() {
  for (int i = 1; i <= n * 2; i++) {
    vex[i] = vis[i] = mchs[i] = mcht[i] = vex2[i] = poss[i] = post[i] = 0;
  }
  ee = ee2 = anscnt = cnt = cnt1 = cnt2 = 0;
}
int main() {
  T = read();
  while (T--) {
    solve();
    clear();
  }
  return 0;
}
