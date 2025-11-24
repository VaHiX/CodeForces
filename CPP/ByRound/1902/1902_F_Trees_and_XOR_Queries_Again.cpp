// Problem: CF 1902 F - Trees and XOR Queries Again
// https://codeforces.com/contest/1902/problem/F

/*
Code Purpose:
This code solves the problem of answering queries on a tree where each vertex has an integer value, 
and for each query, it checks whether there exists a subset of vertices on the path between two nodes 
such that the XOR of their values equals a given target. The solution uses Heavy-Light Decomposition 
and a basis representation of XOR values to efficiently answer queries in O(log n) time per query.

Algorithms/Techniques:
- Heavy-Light Decomposition (HLD) for path decomposition
- Basis representation for XOR operations using Gaussian elimination
- Binary lifting for LCA computation
- Fast I/O and bit manipulation optimizations

Time Complexity:
- Preprocessing: O(n log n)
- Each query: O(log n)
- Total: O(n log n + q log n)

Space Complexity:
- O(n log n) for storing HLD and binary lifting tables
- Additional O(n) for basis representation and graph storage
*/

#import <ios>
using namespace std;
int n, c, i, j, k = 1, u, v, w, z, h[200200], t[400400], e[400400], a[200200],
                l[200200], d[200200], F[200200], f[18][200200];
struct B {
  int b[20], c[20];
  void I(int x, int y) {
    for (int i; x; x ^= b[i])
      if (c[i = __builtin_ctz(x)] < y)
        swap(x, b[i]), swap(y, c[i]);
  }
  B operator+(B x) {
    B s = *this;
    for (int i = 20; i--; s.I(x.b[i], x.c[i]))
      ;
    return s;
  }
  bool Q(int x, int y) {
    for (int i; x; x ^= b[i])
      if (c[i = __builtin_ctz(x)] < y)
        return 0;
    return 1;
  }
} b[200200];
int g(int x, int y) { return d[x] < d[y] ? x : y; }
void _(int u, int p) {
  (b[u] = b[p]).I(a[u], d[f[0][l[u] = ++z] = u] = d[F[u] = p] + 1);
  for (int i = h[u], v; i; i = e[i])
    v = t[i], p ^ v ? _(v, u), 0 : 0;
}
int main() {
  for (scanf("%d", &n); i ^ n; scanf("%d", ++i + a))
    ;
  for (c = 32 - __builtin_clz(n); --i;
       t[z |= 1] = v, e[z] = h[u], h[u] = z, t[++z] = u, e[z] = h[v], h[v] = z)
    scanf("%d%d", &u, &v);
  for (_(1, z = 0); ++j ^ c; k <<= 1)
    for (i = n - (1 << j) + 2; --i; f[j][i] = g(f[j - 1][i], f[j - 1][i + k]))
      ;
  for (scanf("%d", &n); n--; puts((b[u] + b[v]).Q(z, w) ? "YES" : "NO"))
    scanf("%d%d%d", &u, &v, &z),
        w = d[u ^ v ? l[u] > l[v] ? u ^= v ^= u ^= v : 0,
              c = 31 ^ __builtin_clz(l[v] - l[u]),
              F[g(f[c][l[u] + 1], f[c][l[v] - (1 << c) + 1])] : u];
}


// https://github.com/VaHiX/CodeForces/