// Problem: CF 1423 N - BubbleSquare Tokens
// https://codeforces.com/contest/1423/problem/N

/*
Algorithm/Techniques: Graph coloring, greedy assignment
Time Complexity: O(n + k) where n is number of members and k is number of friendships
Space Complexity: O(n + k) for storing graph and auxiliary arrays

This solution assigns tokens to members of a social network such that:
- Each member gets one personal token
- Each member gets 2 additional tokens for each friend
- Each member ends up with a different number of tokens than all their friends
- Members can return tokens to satisfy the constraint
*/

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

#pragma GCC optimize(2)
#define F(i, j, k) for (register int i = (j); i <= (k); i++)
using namespace std;
inline char gc(void) {
  static char buf[100000], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2)
             ? EOF
             : *p1++;
}
template <class T> inline void read(T &x) {
  T f = 1;
  x = 0;
  static char c = gc();
  for (; !isdigit(c); c = gc())
    if (c == '-')
      f = -f;
  for (; isdigit(c); c = gc())
    x = (x << 1) + (x << 3) + (c & 15);
  x *= f;
}
inline void readstr(char *s) {
  do
    *s = gc();
  while ((*s == ' ') || (*s == '\n') || (*s == '\r'));
  do
    *(++s) = gc();
  while ((~*s) && (*s != ' ') && (*s != '\n') && (*s != '\r'));
  *s = 0;
  return;
}
inline void readch(char &x) {
  while (isspace(x = gc()))
    ;
}
char pf[100000], *o1 = pf, *o2 = pf + 100000;
#define ot(x)                                                                  \
  (o1 == o2 ? fwrite(pf, 1, 100000, stdout), *(o1 = pf)++ = x : *o1++ = x)
template <class T> inline void writeln(T x, char c = '\n') {
  if (x < 0)
    ot(45), x = -x;
  static char s[15], *b;
  b = s;
  if (!x)
    *b++ = 48;
  for (; x; *b++ = x % 10 + 48, x /= 10)
    ;
  for (; b-- != s; ot(*b))
    ;
  ot(c);
}
template <class T> inline void chkmax(T &x, const T y) {
  x > y ? x = x : x = y;
}
template <class T> inline void chkmin(T &x, const T y) {
  x < y ? x = x : x = y;
}
#define Ms(arr, opt) memset(arr, opt, sizeof(arr))
#define Mp(x, y) make_pair(x, y)
typedef long long ll;
const int N = 1e6 + 100;
int x[N], y[N], w[N], s[N], v[N];
bool in[N * 2];
vector<pair<int, int>> e[N];
vector<int> res;
int n, m;
int main() {
  read(n), read(m);
  F(i, 1, m) {
    read(x[i]), read(y[i]);
    w[i] = 1;
    s[x[i]]++;
    s[y[i]]++;
    e[max(x[i], y[i])].push_back(make_pair(min(x[i], y[i]), i));
  }
  F(i, 1, n) {
    for (auto it : e[i]) {
      if (!v[it.first]) {
        v[it.first] = 1;
        w[it.second] = 0;
        s[i]--;
      }
      in[s[it.first]] = 1;
    }
    for (auto it : e[i]) {
      if (!in[s[i]])
        break;
      s[i]++;
      v[it.first] = 0;
      w[it.second]++;
    }
    for (auto it : e[i])
      in[s[it.first]] = 0;
  }
  F(i, 1, n) if (v[i]) res.push_back(i);
  writeln(int(res.size()));
  for (auto it : res)
    writeln(it, ' ');
  puts("");
  F(i, 1, m) writeln(x[i], ' '), writeln(y[i], ' '), writeln(w[i]);
  fwrite(pf, 1, o1 - pf, stdout);
  return 0;
}


// https://github.com/VaHiX/CodeForces/