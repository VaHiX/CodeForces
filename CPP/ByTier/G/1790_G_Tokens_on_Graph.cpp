// Problem: CF 1790 G - Tokens on Graph
// https://codeforces.com/contest/1790/problem/G

/*
Algorithm: BFS-based reachability check with bonus interaction handling
Time Complexity: O(N + M) per test case, where N is vertices and M is edges
Space Complexity: O(N + M) for graph storage and auxiliary arrays

This solution determines if a token can reach vertex 1 (finish) in the described
game. Key ideas:
1. First check if any token is already at vertex 1 (win immediately)
2. Check if any token is directly adjacent to vertex 1 (can reach in one move)
3. If more than one token, analyze bonus interactions:
   - Identify connected bonuses (bonuses that can be used to chain moves)
   - Run BFS from vertex 1 to find reachable positions
   - For each reachable token, calculate if it can be reached with the bonus
chain
*/

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;
char *__abc147, *__xyz258, __ma369[100000];
#define __hv007()                                                              \
  ((__abc147 == __xyz258) && (__xyz258 = (__abc147 = __ma369) +                \
                                         fread(__ma369, 1, 100000, stdin),     \
                              __abc147 == __xyz258)                            \
       ? EOF                                                                   \
       : *__abc147++)
int getInt() {
  int sgn = 1;
  char ch = __hv007();
  while (ch != '-' && (ch < '0' || ch > '9'))
    ch = __hv007();
  if ('-' == ch) {
    sgn = 0;
    ch = __hv007();
  }
  int ret = (int)(ch - '0');
  while ('0' <= (ch = __hv007()) && ch <= '9')
    ret = ret * 10 + (int)(ch - '0');
  return sgn ? ret : -ret;
}
char getChar() {
  char ch = __hv007();
  while (ch != 'o' && ch != 'x')
    ch = __hv007();
  return ch;
}
using llt = long long;
using vi = vector<int>;
using vll = vector<llt>;
using edge_t = tuple<int, int, int, int>;
using ve = vector<edge_t>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
llt const MOD = 1E9 + 7LL;
int N, M;
int P, B;
vvi G;
vi Token, Bonus;
vi IsBonus;
vi IsToken;
vi D;
vi Can;
bool proc() {
  IsToken.assign(N + 1, 0);
  for (int i : Token)
    IsToken[i] = 1;
  if (IsToken[1])
    return true;
  for (int i : G[1]) {
    if (IsToken[i])
      return true;
  }
  if (1 == Token.size())
    return false;
  IsBonus.assign(N + 1, 0);
  for (int i : Bonus)
    IsBonus[i] = 1;
  for (int i : Bonus) {
    for (int v : G[i]) {
      if (IsBonus[v]) {
        IsBonus[i] = IsBonus[v] = 2;
      }
    }
  }
  D.assign(N + 1, -1);
  queue<int> q;
  D[1] = 0;
  for (int i : G[1]) {
    if (IsBonus[i]) {
      D[i] = 1;
      q.push(i);
    }
  }
  Can.clear();
  int k = 1, sz;
  while (sz = q.size()) {
    ++k;
    while (sz--) {
      auto h = q.front();
      q.pop();
      assert(IsBonus[h]);
      for (auto v : G[h]) {
        if (D[v] != -1)
          continue;
        D[v] = k;
        if (IsToken[v]) {
          Can.emplace_back(v);
          IsToken[v] = 2;
        }
        if (IsBonus[v]) {
          q.push(v);
        }
      }
    }
  }
  if (0 == Can.size())
    return false;
  auto node = Can[0];
  int c = 0;
  for (int i : Token) {
    if (i == node)
      continue;
    int st = 0;
    for (int v : G[i]) {
      if (IsBonus[v]) {
        st |= IsBonus[v];
        if (st & 2)
          break;
      }
    }
    if (st & 2)
      c = 20000000;
    else if (st & 1)
      ++c;
  }
  if (c + 1 >= D[node])
    return true;
  return false;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int nofkase = getInt();
  for (int kase = 1; kase <= nofkase; ++kase) {
    N = getInt();
    M = getInt();
    P = getInt();
    B = getInt();
    G.assign(N + 1, vi());
    Token.assign(P, 0);
    Bonus.assign(B, 0);
    for (int &i : Token)
      i = getInt();
    for (int &i : Bonus)
      i = getInt();
    for (int a, b, i = 0; i < M; ++i) {
      a = getInt();
      b = getInt();
      G[a].emplace_back(b);
      G[b].emplace_back(a);
    }
    puts(proc() ? "YES" : "NO");
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/