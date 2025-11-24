// Problem: CF 1685 D2 - Permutation Weight (Hard Version)
// https://codeforces.com/contest/1685/problem/D2

/*
算法/技术: 
- 构造性算法 + 图论 + 回溯搜索
- 使用并查集构建循环结构，然后通过回溯的方式构造字典序最小的解
- 利用图的连通性判断是否形成合法循环
时间复杂度: O(n^3)
空间复杂度: O(n^2)
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 550;
int T, n, p[N], mp[N]; // p: 原排列，mp: p的逆映射
int col[N], id; // col[i]表示i属于第几个循环，id表示循环总数
int in[N], out[N]; // in[i]表示有多少个元素指向i，out[i]表示i指向多少个元素
int ans[N]; // 记录答案序列
int L[N], R[N]; // L[i]表示i左边有多少个元素，R[i]表示i右边有多少个元素
vector<int> G[N]; // 图的邻接表表示
bool vis[N]; // 访问标记

// DFS遍历图
void dfs(int u) {
  if (vis[u])
    return;
  vis[u] = 1;
  for (int i = 0; i < (int)G[u].size(); i++)
    dfs(G[u][i]);
}

// 检查当前状态是否合法
bool check() {
  // 检查每个点的入度和出度是否超过1
  for (int i = 1; i <= n; i++)
    if (L[i] > 1 || R[i] > 1)
      return 0;
  // 检查孤立点
  for (int i = 1; i <= n; i++)
    if (!in[i] && !out[i] && L[i] && R[i])
      return 0;
  // 清空图
  for (int i = 1; i <= id; i++)
    G[i].clear(), vis[i] = 0;
  int ct = 0, num = 0;
  // 构造图
  for (int i = 1; i < n; i++) {
    if (L[i + 1] || R[i]) {
      ct++;
      G[col[i]].push_back(col[i + 1]);
      G[col[i + 1]].push_back(col[i]);
    }
  }
  // 计算连通分量数
  for (int i = 1; i <= id; i++) {
    if (vis[i])
      continue;
    num++;
    dfs(i);
  }
  if (num + ct > id)
    return 0; // 非法结构
  
  // 清空图
  for (int i = 1; i <= id; i++)
    G[i].clear(), vis[i] = 0;
  num = 0;
  // 构造图（另一种方式）
  for (int i = 1; i < n; i++) {
    if (!(in[i] && out[i] && (in[i] <= i && out[i] <= i)) &&
        !(in[i + 1] && out[i + 1] && in[i + 1] >= i + 1 &&
          out[i + 1] >= i + 1)) {
      G[col[i]].push_back(col[i + 1]);
      G[col[i + 1]].push_back(col[i]);
    }
  }
  // 计算连通分量数
  for (int i = 1; i <= id; i++) {
    if (vis[i])
      continue;
    num++;
    dfs(i);
  }
  if (num > 1)
    return 0; // 不是连通图或者图中存在多个环
  return 1;
}

// 添加边
void add(int u, int v) {
  out[u] = v, in[v] = u;
  // 更新路径统计
  if (v < u)
    for (int j = u; j > v; j--)
      L[j]++;
  else
    for (int j = u; j < v; j++)
      R[j]++;
}

// 删除边
void del(int u, int v) {
  out[u] = in[v] = 0;
  // 恢复路径统计
  if (v < u)
    for (int j = u; j > v; j--)
      L[j]--;
  else
    for (int j = u; j < v; j++)
      R[j]--;
}

int main() {
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++)
      scanf("%d", &p[i]), mp[p[i]] = i; // 构建原数组及其反向映射
    
    id = 0;
    for (int i = 1; i <= n; i++)
      col[i] = in[i] = out[i] = L[i] = R[i] = 0; // 初始化
    
    // 分解环
    for (int i = 1; i <= n; i++) {
      if (col[i])
        continue;
      col[i] = ++id;
      int cur = mp[i];
      while (cur != i)
        col[cur] = id, cur = mp[cur];
    }
    
    ans[1] = 1;
    for (int t = 2; t <= n; t++) {
      int u = ans[t - 1];
      for (int i = 1; i <= n; i++) {
        int v = p[i];
        if (in[v])
          continue; // 如果v已经被使用，跳过
        add(u, v);
        if (check()) {
          ans[t] = i;
          break;
        }
        del(u, v);
      }
    }
    for (int i = 1; i <= n; i++)
      printf("%d ", ans[i]);
    putchar('\n');
  }
}



// https://github.com/VaHiX/CodeForces/