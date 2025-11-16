// Problem: CF 1949 C - Annual Ants' Gathering
// https://codeforces.com/contest/1949/problem/C

/*
Algorithm: Tree Dynamic Programming + Greedy
Purpose: Determine if all ants in a tree can be gathered into a single house by moving ants along branches.
Approach:
1. Build the tree from input edges.
2. Calculate subtree sizes using DFS.
3. Use a recursive DFS on the tree to evaluate if gathering is possible:
   - For each node, check all subtrees rooted at its children.
   - Use greedy strategy to decide which subtree to move ants from.
   - Maintain a validity check to determine whether an ant movement is beneficial.
Time Complexity: O(n log n) due to sorting operations in DFS traversal.
Space Complexity: O(n) for storing the tree structure and auxiliary vectors.

Key Techniques:
- Tree DFS traversal
- Greedy subset selection
- Subtree size calculation
- Validity checks based on subtree sizes
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define debug(x) cerr << #x << " == " << x << endl
#define el '\n'
#define fir first
#define sec second
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 1000000007;
const int inf = 0x3f3f3f3f;
const int N = 200010;
const int M = 200010;
int n;
struct Node {
  int id, x;
  Node() {}
  Node(int _id, int _x) : id(_id), x(_x) {}
  inline bool operator<(const Node that) { return x < that.x; }
};
struct Graph {
  int tot, head[N], suiv[M << 1], ver[M << 1], fa[N], siz[N], valid[N];
  vector<Node> stk[N], stk2[N];
  inline void lnk(int x, int y) {
    ver[++tot] = y;
    suiv[tot] = head[x];
    head[x] = tot;
  }
  inline void dfs1(int x) {
    siz[x] = 1;
    for (int i = head[x]; i; i = suiv[i]) {
      int y = ver[i];
      if (y == fa[x])
        continue;
      fa[y] = x;
      dfs1(y);
      siz[x] += siz[y];
    }
  }
  inline int dfs2(int x) {
    if (valid[x])
      return valid[x];
    stk2[x].clear();
    int res = 1;
    for (int i = head[x]; i; i = suiv[i]) {
      int y = ver[i];
      if (y == fa[x])
        continue;
      dfs2(y);
      if (valid[y] == 2)
        res = 2;
      stk2[x].push_back(Node(y, siz[y]));
    }
    if (res == 2)
      return valid[x] = 2;
    int pos = 1;
    sort(stk2[x].begin(), stk2[x].end());
    for (int i = 0, lim = stk2[x].size(); i < lim; i++) {
      if (stk2[x][i].x > pos) {
        res = 2;
        break;
      } else
        pos += stk2[x][i].x;
    }
    return valid[x] = res;
  }
  inline bool dfs(int x, int lst = -1) {
    stk[x].clear();
    for (int i = head[x]; i; i = suiv[i]) {
      int y = ver[i];
      if (y == fa[x])
        continue;
      stk[x].push_back(Node(y, siz[y]));
    }
    if (~lst)
      stk[x].push_back(Node(-2, lst));
    sort(stk[x].begin(), stk[x].end());
    int pos = 1, nxt = -1;
    for (int i = 0, lim = stk[x].size(); i < lim; i++) {
      if (stk[x][i].x <= pos && (stk[x][i].id == -2 || dfs2(stk[x][i].id) == 1))
        pos += stk[x][i].x;
      else {
        if (nxt != -1 || stk[x][i].id == -2)
          return 0;
        nxt = stk[x][i].id;
      }
    }
    if (nxt == -1)
      return 1;
    return dfs(nxt, n - siz[nxt]);
  }
} e;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> n;
  for (int i = 1, x, y; i < n; i++)
    cin >> x >> y, e.lnk(x, y), e.lnk(y, x);
  e.dfs1(1);
  puts(e.dfs(1) ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/