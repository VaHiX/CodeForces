// Problem: CF 1801 G - A task for substrings
// https://codeforces.com/contest/1801/problem/G

/*
Purpose: 
This code solves a problem where we are given a string t and a set of n strings s1, s2, ..., sn.
For each query (li, ri), we need to count how many substrings of t[li..ri] exist in the set of strings.
The solution uses Aho-Corasick automaton to efficiently match substrings against the set of patterns,
and performs range queries using a segment tree with lazy propagation.

Algorithms/Techniques:
- Aho-Corasick automaton for pattern matching
- Segment tree for range queries
- Trie (prefix tree) implementation with failure links
- Reverse string processing for efficient insertion in trie

Time Complexity:
- Preprocessing (building Aho-Corasick): O(S) where S is total length of all patterns
- Each query: O(log|t| + sqrt(S)) due to segment tree and Aho-Corasick matching

Space Complexity:
- O(S + |t|) for storage of trie and auxiliary arrays

*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using i64 = long long;
const int N = 5e5 + 5, LS = 1e6 + 5, LT = 5e6 + 5;
int n, m;
string t, s[N];
vector<i64> num[N];
int trie[LS][26], ptrie = 1, diff[LS], dep[LS], fail[LS];
pair<int, int> len[LS];
void Insert(string str, int idx) {
  int p = 1;
  for (char c : str) {
    if (!trie[p][c - 'a'])
      trie[p][c - 'a'] = ++ptrie;
    p = trie[p][c - 'a'];
  }
  ++diff[p], len[p].second = idx;
}
void Clear() {
  for (; ptrie; --ptrie) {
    memset(trie[ptrie], 0, sizeof trie[ptrie]);
    diff[ptrie] = fail[ptrie] = 0;
    len[ptrie] = {0, 0};
  }
  ptrie = 1;
}
int que[LS], tail;
void Build(bool type) {
  for (int &p : trie[0])
    p = 1;
  que[tail = 1] = 1;
  for (int head = 1; head <= tail; ++head) {
    int u = que[head];
    if (u > 1) {
      if (type) {
        if (len[u].second)
          len[u].first = dep[u];
        else
          len[u] = len[fail[u]];
      }
      diff[u] += diff[fail[u]];
    }
    for (int i = 0; i < 26; ++i) {
      if (trie[u][i]) {
        dep[trie[u][i]] = dep[u] + 1;
        fail[trie[u][i]] = trie[fail[u]][i];
        que[++tail] = trie[u][i];
      } else
        trie[u][i] = trie[fail[u]][i];
    }
  }
}
i64 pre[LT];
int lef[LT], idx[LT];
namespace DS {
#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid ((l + r) >> 1)
int sgt[LT * 4];
void Build(int p = 1, int l = 0, int r = t.size() - 1) {
  if (l == r) {
    sgt[p] = lef[l];
    return;
  }
  Build(ls, l, mid), Build(rs, mid + 1, r);
  sgt[p] = min(sgt[ls], sgt[rs]);
}
int Query(int L, int R, int p = 1, int l = 0, int r = t.size() - 1) {
  if (R < l || r < L || sgt[p] >= L)
    return -1;
  if (l == r)
    return l;
  int res = Query(L, R, rs, mid + 1, r);
  if (res >= 0)
    return res;
  return Query(L, R, ls, l, mid);
}
#undef ls
#undef rs
#undef mid
} // namespace DS
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> t;
  for (int i = 1; i <= n; ++i) {
    cin >> s[i];
    reverse(s[i].begin(), s[i].end());
    Insert(s[i], i);
    reverse(s[i].begin(), s[i].end());
  }
  Build(0);
  for (int i = 1; i <= n; ++i) {
    num[i].resize(s[i].size() + 1);
    int p = 1;
    for (int j = s[i].size() - 1; ~j; --j) {
      p = trie[p][s[i][j] - 'a'];
      num[i][j] = num[i][j + 1] + diff[p];
    }
  }
  Clear();
  for (int i = 1; i <= n; ++i)
    Insert(s[i], i);
  Build(1);
  for (int r = 0, p = 1; r < t.size(); ++r) {
    p = trie[p][t[r] - 'a'];
    pre[r + 1] = pre[r] + diff[p];
    lef[r] = r - len[p].first + 1, idx[r] = len[p].second;
  }
  DS::Build();
  for (int i = 1; i <= m; ++i) {
    int l, r;
    cin >> l >> r;
    --l, --r;
    int mid = DS::Query(l, r);
    if (mid >= 0)
      printf("%lld ", num[idx[mid]][l - lef[mid]] + pre[r + 1] - pre[mid + 1]);
    else
      printf("%lld ", pre[r + 1] - pre[l]);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/