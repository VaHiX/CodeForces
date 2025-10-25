/*
 * Problem URL : https://codeforces.com/contest/1192/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;
int n, type;
int dx[8] = {1, 0, 0, -1, 1, -1, 1, -1};
int dy[8] = {0, 1, -1, 0, 1, -1, -1, 1};
struct node {
  int x, y;
} A[1500005];
bool vis[1500005];
pair<int, int> G[1500005];
int tot, pos;
int N, M;
int id(int i, int j) { return (i - 1) * M + j; }
int need;

map<int, int> mp[500005];
int ljb[1500005][8];
class UFS {
public:
  int father[1500005];
  void init(int n) {
    for (int i = 1; i <= n; i++)
      father[i] = i;
    return;
  }
  int find(int x) { return father[x] == x ? x : father[x] = find(father[x]); }
  void unionn(int x, int y) { return father[find(x)] = find(y), void(); }
} S;

void init() {
  vector<int> D;
  for (int i = 1; i <= n; i++) {
    D.push_back(A[i].x - 1);
    D.push_back(A[i].x);
    D.push_back(A[i].x + 1);
  }
  sort(D.begin(), D.end());
  vector<int> E;
  for (int i = 0; i < D.size(); i++) {
    if (!i)
      E.push_back(D[i]);
    else if (D[i] xor D[i - 1])
      E.push_back(D[i]);
  }
  D = E;
  for (int i = 1; i <= n; i++) {
    int lt = -1, rt = D.size();
    while (lt + 1 < rt) {
      int mid = lt + rt >> 1;
      if (D[mid] <= A[i].x)
        lt = mid;
      else
        rt = mid;
    }
    A[i].x = lt;
  }
  N = D.size() - 1;
  D.clear(), E.clear();
  for (int i = 1; i <= n; i++) {
    D.push_back(A[i].y - 1);
    D.push_back(A[i].y);
    D.push_back(A[i].y + 1);
  }
  sort(D.begin(), D.end());
  for (int i = 0; i < D.size(); i++) {
    if (!i)
      E.push_back(D[i]);
    else if (D[i] xor D[i - 1])
      E.push_back(D[i]);
  }
  // exit(0);
  D = E;
  for (int i = 1; i <= n; i++) {
    int lt = -1, rt = D.size();
    while (lt + 1 < rt) {
      int mid = lt + rt >> 1;
      if (D[mid] <= A[i].y)
        lt = mid;
      else
        rt = mid;
    }
    A[i].y = lt;
  }
  M = E.size() - 1;
  N += 2, M += 2;
  for (int i = 1; i <= n; i++) {
    A[i].x++, A[i].y++;
  }
  for (int i = 1; i <= n; i++) {
    mp[A[i].x][A[i].y] = i;
  }
  for (int i = 1; i <= n; i++) {
    for (int k = 0; k < 8; k++) {
      if (mp[A[i].x + dx[k]][A[i].y + dy[k]]) {
        continue;
      }
      G[++tot] = make_pair(A[i].x + dx[k], A[i].y + dy[k]);
    }
  }
  sort(G + 1, G + 1 + tot);
  pos = n;
  for (int i = 1; i <= tot; i++) {
    if (G[i] != G[i - 1]) {
      A[++pos] = node{G[i].first, G[i].second};
    }
  }
  for (int i = 1; i <= pos; i++)
    mp[A[i].x][A[i].y] = i;
  need = pos;
  for (int i = 1; i <= pos; i++) {
    for (int k = 0; k < 8; k++) {
      ljb[i][k] = mp[A[i].x + dx[k]][A[i].y + dy[k]];
    }
  }
  S.init(pos);
  for (int i = 1; i <= n; i++) {
    for (int k = 0; k < 8; k++) {
      int v = ljb[i][k];
      if (!v || v > n)
        continue;
      S.unionn(i, v);
    }
  }
  for (int i = n + 1; i <= pos; i++) {
    for (int k = 0; k < 4; k++) {
      int v = ljb[i][k];
      if (!v || v <= n)
        continue;
      S.unionn(i, v);
    }
  }
  cerr << N << ' ' << M << '\n';
  return;
}

vector<int> L[6], R[6], qeta[6];

bool check(int cur) {
  for (int i = 0; i < 6; i++) {
    bool flg = false;
    for (int v : L[i]) {
      if (vis[ljb[cur][v]])
        flg = true;
    }
    if (!flg)
      continue;
    flg = false;
    for (int v : R[i]) {
      if (vis[ljb[cur][v]])
        flg = true;
    }
    if (!flg)
      continue;
    flg = false;
    for (int v : qeta[i]) {
      if (vis[ljb[cur][v]])
        flg = true;
    }
    if (flg)
      continue;
    if (S.find(ljb[cur][qeta[i][0]]) == S.find(ljb[cur][qeta[i][1]])) {
      return true;
    }
  }
  for (int i = 0; i < 4; i++) {
    int v = ljb[cur][i];
    if (!v)
      continue;
    if (S.find(v) == S.find(need)) {
      return false;
    }
  }
  return true;
}

class ddd {
public:
  priority_queue<int> A, D;
  void push(int x) { return A.push(x), void(); }
  void del(int x) { return D.push(x), void(); }
  int top() {
    while (D.size() && A.top() == D.top())
      A.pop(), D.pop();
    return A.top();
  }
  int size() { return A.size() - D.size(); }
} Q;
bool in[150005];

bool tag[1500005];

void getin(int cur) {
  tag[cur] = true;
  for (int i = 0; i < 4; i++) {
    if (!ljb[cur][i])
      continue;
    if (vis[ljb[cur][i]]) {
      if (!in[ljb[cur][i]]) {
        Q.push(ljb[cur][i]);
        in[ljb[cur][i]] = true;
      }
      continue;
    }
    if (tag[ljb[cur][i]])
      continue;
    getin(ljb[cur][i]);
  }
  return;
}

int main() {
  L[0] = {7}, R[0] = {5, 2, 6, 0, 4}, qeta[0] = {1, 3};
  L[1] = {5}, R[1] = {6, 0, 4, 1, 7}, qeta[1] = {2, 3};
  L[2] = {6}, R[2] = {5, 3, 7, 1, 4}, qeta[2] = {2, 0};
  L[3] = {4}, R[3] = {6, 2, 5, 3, 7}, qeta[3] = {0, 1};
  L[4] = {5, 3, 7}, R[4] = {6, 0, 4}, qeta[4] = {1, 2};
  L[5] = {5, 2, 6}, R[5] = {7, 1, 4}, qeta[5] = {0, 3};
  scanf("%d%d", &n, &type);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &A[i].x, &A[i].y);
  }
  init();
  int chk = 0;
  for (int i = 1; i <= n; i++) {
    if (S.find(i) == i) {
      chk++;
    }
  }
  if (chk > 1) {
    puts("NO");
    return 0;
  }
  for (int i = 1; i <= n; i++)
    S.father[i] = i;
  for (int i = 1; i <= n; i++)
    vis[i] = true;
  int tim = n;
  vector<int> ans;
  for (int i = 1; i <= n; i++)
    Q.push(i), in[i] = true;
  while (tim--) {
    while (Q.size()) {
      int tmp = Q.top();
      Q.del(tmp);
      in[tmp] = false;
      if (check(tmp))
        continue;
      if (!vis[tmp])
        continue;
      vis[tmp] = false;
      for (int j = 0; j < 4; j++) {
        if (!vis[ljb[tmp][j]])
          S.unionn(tmp, ljb[tmp][j]);
      }
      if (S.find(need) == S.find(tmp)) {
        getin(tmp);
      }
      ans.push_back(tmp);
      for (int j = 0; j < 8; j++) {
        if (vis[ljb[tmp][j]]) {
          if (!in[ljb[tmp][j]]) {
            Q.push(ljb[tmp][j]);
            in[ljb[tmp][j]] = true;
          }
        }
      }
      break;
    }
  }
  puts("YES");
  for (int i = ans.size() - 1; i >= 0; i--) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
