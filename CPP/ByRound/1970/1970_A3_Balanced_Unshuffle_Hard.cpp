// Problem: CF 1970 A3 - Balanced Unshuffle (Hard)
// https://codeforces.com/contest/1970/problem/A3

/*
 * Problem: Balanced Unshuffle (Hard)
 *
 * Algorithm/Techniques:
 * - This solution reconstructs the original balanced parentheses sequence from its balanced shuffle.
 * - The key idea is to simulate the process of building a tree from the shuffle sequence:
 *   - Each opening parenthesis '(' in the shuffle represents a new subtree.
 *   - The closing parenthesis ')' represents the end of a subtree.
 * - Using a BFS-like approach, we build a tree of nested parentheses where:
 *   - Each node corresponds to a level in the nested structure.
 *   - The tree is traversed in a way that mirrors the balanced shuffle operation.
 * - The final traversal of the tree yields the original sequence.
 *
 * Time Complexity: O(n), where n is the length of the input string.
 * Space Complexity: O(n), for storing the tree structure and recursion stack.
 */
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;
#define il inline
namespace FastIO {
const int LEN = 1 << 20;
char buf[LEN], obuf[LEN], *p1 = buf, *p2 = buf, *p3 = obuf;
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, LEN, stdin), p1 == p2)         \
       ? EOF                                                                   \
       : *p1++)
#define flush() (fwrite(obuf, 1, p3 - obuf, stdout), p3 = obuf)
il void read(string &s) {
  char ch = getchar();
  s = "";
  while (ch != '(' && ch != ')')
    ch = getchar();
  while (ch == '(' || ch == ')')
    s += ch, ch = getchar();
}
} // namespace FastIO
using namespace FastIO;
const int N = 5e5 + 5;
int n, p = 1, cnt, num, head[N], nxt[N], to[N];
string s;
queue<int> q;
il void AddEdge(int u, int v) {
  nxt[++cnt] = head[u], to[cnt] = v, head[u] = cnt;
}
il void Dfs(int u) {
  for (int i = head[u], v; v = to[i], i; i = nxt[i])
    *p3++ = '(', Dfs(v), *p3++ = ')';
}
int main() {
  read(s), n = s.length(), s = ' ' + s, q.push(0); // Add dummy head for 1-based indexing
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    while (s[p++] == '(')
      AddEdge(u, ++num), q.push(num);
  }
  Dfs(0), flush();
}


// https://github.com/VaHiX/CodeForces/