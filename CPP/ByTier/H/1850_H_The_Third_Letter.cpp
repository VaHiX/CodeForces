// Problem: CF 1850 H - The Third Letter
// https://codeforces.com/contest/1850/problem/H

/*
Algorithm: Union-Find with Distance Tracking
Purpose: Determine if there exists a valid partition of soldiers into camps that satisfies all given conditions. Each condition specifies a relative distance between two soldiers' camps.

Approach:
- Use Union-Find (Disjoint Set Union) data structure to group soldiers into connected components
- Track relative distances between soldiers within the same component
- For each condition, either merge two components or check consistency of existing distances
- A contradiction in distances leads to "NO", otherwise "YES"

Time Complexity: O(m * α(n)) where α(n) is the inverse Ackermann function (nearly constant)
Space Complexity: O(n) for storing parent and distance arrays

The key idea is to use Union-Find with path compression and distance tracking
to detect contradictions in relative positions between soldiers.
*/
#include <ctype.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
#define int long long
#define endl "\n"
#define ull unsigned long long
#define ms(x, y) memset(x, y, sizeof x);
#define debug(x) cout << #x << " = " << x << endl;
#define ios ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define fre                                                                    \
  freopen("input.txt", "r", stdin);                                            \
  freopen("output.txt", "w", stdout);
const int mod = 998244353;
const int inf = 0x3f3f3f3f3f3f3f3f;
const int N = 3e5 + 10;
const double esp = 1e-6;
#define pre(i, a, b) for (int i = a; i <= b; i++)
#define rep(i, a, b) for (int i = a; i >= b; i--)
struct fio {
  inline char gc() {
    static const int IN_LEN = 1 << 18 | 1;
    static char buf[IN_LEN], *s, *t;
    static streambuf *sb = cin.rdbuf();
    return (s == t) && (t = (s = buf) + sb->sgetn(buf, IN_LEN)),
           s == t ? -1 : *s++;
  }
  inline fio &operator>>(string &s) {
    static char ch;
    ch = gc();
    s.clear();
    for (; isspace(ch); ch = gc())
      if (ch == -1)
        return *this;
    for (; !isspace(ch) && ch != -1; ch = gc())
      s += ch;
    return *this;
  }
  inline fio &operator>>(char *s) {
    static char ch;
    ch = gc();
    for (; isspace(ch); ch = gc())
      if (ch == -1)
        return *this;
    for (; !isspace(ch) && ch != -1; ch = gc())
      *(s++) = ch;
    return *this;
  }
  inline void gtline(string &s) {
    static char ch;
    ch = gc();
    s.clear();
    for (; ch != '\n' && ch != -1; ch = gc())
      s += ch;
  }
  template <typename T> inline fio &operator>>(T &n) {
    static char ch, sgn;
    ch = gc(), sgn = 0;
    for (; !isdigit(ch); ch = gc()) {
      if (ch == -1)
        return *this;
      sgn |= ch == '-';
    }
    for (n = 0; isdigit(ch); ch = gc())
      n = n * 10 + (ch ^ '0');
    if (ch == '.') {
      T tmp = 0;
      ch = gc();
      for (; isdigit(ch); ch = gc())
        tmp = tmp * 10 + (ch ^ '0');
      while (tmp > 1)
        tmp /= 10;
      n += tmp;
    }
    sgn && (n = -n);
    return *this;
  }
} io;
void write(int x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x > 9)
    write(x / 10);
  putchar(x % 10 + '0');
  return;
}
int p[N], d[N]; // p[i] is parent of i, d[i] is distance from i to its parent
int n, m;
int a[N], b[N], c[N];
int find(int x) {
  // Find root with path compression and update distance
  if (x != p[x]) {
    int t = find(p[x]);  // Recursively find root
    d[x] += d[p[x]];     // Accumulate distance to root
    p[x] = t;            // Set parent to root
  }
  return p[x];
}
bool flag = 0;
void solve() {
  flag = 0;
  io >> n >> m;
  pre(i, 1, n) p[i] = i, d[i] = 0;  // Initialize each soldier as its own parent with 0 distance
  pre(i, 1, m) { io >> a[i] >> b[i] >> c[i]; }  // Read conditions
  pre(i, 1, m) {
    int pa = find(a[i]), pb = find(b[i]);  // Find roots of both soldiers
    if (pa != pb) {
      // If soldiers are not in same component, unite them
      p[pa] = pb;        // Make pb parent of pa
      d[pa] = d[b[i]] - d[a[i]] + c[i];  // Set distance of pa from pb
    } else {
      // If soldiers are in same component, check if distance is consistent
      if (d[a[i]] - d[b[i]] != c[i]) {
        flag = 1;  // Inconsistency found
        return;
      }
    }
  }
}
void w() {
  cout.tie(0);
  if (flag)
    cout << "NO" << endl;  // Print NO if contradiction found
  else
    cout << "YES" << endl; // Print YES if all conditions are consistent
}
signed main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  auto start = std::chrono::high_resolution_clock::now();
#endif
  int t = 1;
  cin >> t;
  while (t--)
    solve(), w();
#ifdef LOCAL
  auto end = std::chrono::high_resolution_clock::now();
  cout << "Execution time: "
       << std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
              .count()
       << " ms" << '\n';
#endif
  return 0;
}


// https://github.com/VaHiX/CodeForces/