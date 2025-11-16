// Problem: CF 1780 G - Delicious Dessert
// https://codeforces.com/contest/1780/problem/G

/*
Algorithm: Suffix Automaton + DFS + Divisor Enumeration
Time Complexity: O(n * sqrt(n) + n)
Space Complexity: O(n)

This solution uses a suffix automaton to efficiently compute the number of 
delicious substrings. A substring is delicious if its occurrence count is divisible 
by its length. For each state in the suffix automaton, we calculate how many 
divisors of its total occurrence count are valid for its length.

The key idea is to:
1. Build a suffix automaton for the input string.
2. For each node in the automaton (representing a set of substrings), count occurrences.
3. Enumerate all divisors of occurrence counts and check divisibility conditions.
4. Use DFS on the automaton tree to accumulate counts.
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define F(i, x, y) for (int i = x; i <= y; ++i)
#define Get(x, y) lower_bound(x.begin(), x.end(), y) - x.begin()
enum { N = 2000010 };
struct node {
  array<int, 26> ch;
  int len, tot, fa;
} a[N];
vector<int> G[N], Fact[N];
int n, p, q, tot = 1, las = 1, Cnt[N];
string str;
void Insert(int k) {
  int w = ++tot;
  a[w].len = -~a[las].len, a[w].tot = 1;
  while (las && !a[las].ch[k])
    a[las].ch[k] = w, las = a[las].fa;
  if (las == 0)
    return a[las = w].fa = 1, void();
  p = a[las].ch[k];
  if (a[p].len == -~a[las].len)
    return a[las = w].fa = p, void();
  q = ++tot;
  a[q].len = -~a[las].len, a[q].fa = a[p].fa, a[p].fa = a[w].fa = q;
  a[q].ch = a[p].ch;
  while (p == a[las].ch[k])
    a[las].ch[k] = q, las = a[las].fa;
  las = w;
}
void dfs(int u, int fa) {
  for (int v : G[u])
    if (v ^ fa)
      dfs(v, u), a[u].tot += a[v].tot;
}
int main() {
  cin >> n >> str, str = " " + str;
  F(i, 1, n) F(j, 1, n / i) Fact[i * j].push_back(i);
  F(i, 1, n) Insert(str[i] - 'a');
  F(i, 1, tot) G[a[i].fa].push_back(i);
  dfs(1, 0);
  long long res = 0;
  F(i, 1, tot) {
    p = Get(Fact[a[i].tot], -~a[a[i].fa].len);
    q = Get(Fact[a[i].tot], -~a[i].len);
    res += 1ll * (q - p) * a[i].tot;
  }
  cout << res << endl;
}


// https://github.com/VaHiX/CodeForces/