/******************************************************************************
 * Problem: 1916 G - Optimizations From Chelsu
 * https://codeforces.com/contest/1916/problem/G
 *
 * Description:
 * Given a weighted tree, find the maximum value of GCD(P) * |P|, where P is any
 * path in the tree, GCD(P) is the GCD of weights on that path, and |P| is the
 * length of the path (number of edges).
 *
 * Time Complexity Analysis:
 * - Overall: O(T * N * log N * log W)
 *   where T is number of test cases
 *   N is number of nodes in the tree
 *   W is maximum weight on edges
 * - Tree centroid decomposition: O(N log N)
 * - GCD calculations: O(log W) per path
 *
 * Space Complexity:
 * - O(N) for tree storage
 * - O(N) for path information and centroid decomposition
 * - Additional O(N) for hash maps and temporary calculations
 *
 * Key Components:
 * 1. Fast I/O implementation
 * 2. Centroid decomposition of tree
 * 3. GCD path optimization
 * 4. Path length tracking
 * 5. Dynamic programming with hash map
 *
 * Author: [Your Name]
 * Date: November 3, 2025
 ******************************************************************************/

#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
namespace Fread {
const int SZ = 1 << 18;
char buf[SZ], *S, *T;
inline char getchar() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, SZ, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SZ = 1 << 12;
char buf[SZ], *S = buf, *T = buf + SZ;
inline void flush() {
  fwrite(buf, 1, S - buf, stdout);
  S = buf;
}
inline void putchar(char c) {
  *S++ = c;
  if (S == T)
    flush();
}
struct NTR {
  ~NTR() { flush(); }
} ztr;
} // namespace Fwrite
#define getchar Fread ::getchar
#define putchar Fwrite ::putchar
// Fast I/O implementation for optimized input/output operations
namespace Fast {
// Custom Reader class for fast integer input
struct Reader {
  template <typename T> Reader &operator>>(T &x) {
    char c = getchar();
    while (!isdigit(c))
      c = getchar();
    x = 0;
    while (isdigit(c))
      x = x * 10 + (c - '0'), c = getchar();
    return *this;
  }
} cin;
struct Writer {
  template <typename T> Writer &operator<<(T x) {
    static int sta[45];
    int top = 0;
    while (x) {
      sta[++top] = x % 10;
      x /= 10;
    }
    while (top) {
      putchar(sta[top] + '0');
      --top;
    }
    return *this;
  }
  Writer &operator<<(char c) {
    putchar(c);
    return *this;
  }
} cout;
} // namespace Fast
#define cin Fast ::cin
#define cout Fast ::cout
#define ll long long
#define f first
#define s second
// Constants and Global Variables
const int N = 1e5 + 1; // Maximum number of nodes

// Tree representation using adjacency lists
ll we[N];      // Edge weights
int tot = 1;   // Total edges counter (1-based)
int hd[N];     // Head of adjacency list for each node
int nd[2 * N]; // Node IDs in edge list
int nx[2 * N]; // Next edge in adjacency list

// Global variables for tree processing
int T;      // Number of test cases
int node;   // Current centroid node
int n;      // Number of nodes in current tree
int sum;    // Subtree size
int vis[N]; // Visited nodes in centroid decomposition
int sz[N];  // Subtree sizes
int mx[N];  // Maximum subtree size for centroid calculation
// Locate the centroid of the current subtree
// A centroid is a node that, when removed, leaves no component larger than half
// the tree
void locate(int u, int pa) {
  sz[u] = 1; // Initialize subtree size
  mx[u] = 0; // Initialize maximum child subtree size

  // Traverse adjacency list
  for (int i = hd[u], last = 0; i; last = i, i = nx[i]) {
    int v = nd[i];
    // Skip visited nodes and maintain list structure
    if (vis[v]) {
      last ? nx[last] = nx[i] : hd[u] = nx[i];
      continue;
    }
    // Skip parent node
    if (v == pa)
      continue;
    locate(v, u);
    if (node)
      return;
    sz[u] += sz[v];
    mx[u] = max(mx[u], sz[v]);
  }
  mx[u] = max(mx[u], sum - sz[u]);
  if (2 * mx[u] <= sum) {
    node = u;
    sz[pa] = sum - sz[u];
  }
}
// Variables for path and GCD tracking
ll ans;                    // Maximum answer (GCD * path length)
ll GCD[N];                 // Array to store unique GCD values
int cnt;                   // Counter for unique GCD values
int which;                 // Current child being processed
int fi[N];                 // First maximum path length for each GCD
int se[N];                 // Second maximum path length for each GCD
int pos[N];                // Track which subtree gave each maximum
unordered_map<ll, int> mp; // Map GCD values to their indices
void dfs(int u, int pa, ll gcd, int len) {
  if (mp.find(gcd) == mp.end()) {
    GCD[mp[gcd] = ++cnt] = gcd;
    fi[cnt] = se[cnt] = pos[cnt] = 0;
  }
  int k = mp[gcd];
  if (len >= fi[k]) {
    if (pos[k] != which) {
      pos[k] = which;
      if (fi[k])
        se[k] = fi[k];
    }
    fi[k] = len;
  } else if (len >= se[k] && pos[k] != which)
    se[k] = len;
  ans = max(ans, gcd * len);
  for (int i = hd[u], last = 0; i; last = i, i = nx[i]) {
    int v = nd[i];
    if (vis[v]) {
      last ? nx[last] = nx[i] : hd[u] = nx[i];
      continue;
    }
    if (v == pa)
      continue;
    ll w = we[i >> 1];
    dfs(v, u, __gcd(gcd, w), len + 1);
  }
}
// Process a centroid node to find maximum GCD * path length
// This function implements the core algorithm of the solution
// by processing paths through the current centroid
void calc(int u) {
  mp.clear(); // Clear GCD map for new centroid
  cnt = 0;    // Reset unique GCD counter
  for (int i = hd[u]; i; i = nx[i]) {
    int v = nd[i];
    ll w = we[i >> 1];
    which = v;
    dfs(v, u, w, 1);
  }
  // Process all collected GCD values to find optimal paths
  for (int i = 1; i <= cnt; i++)
    // Optimization: only process if potential answer could be better than
    // current
    if (GCD[i] * fi[i] * 2 > ans)
      // Check all possible GCD values that could form with current path
      for (ll j = GCD[i]; j <= GCD[i] * fi[i]; j += GCD[i])
        if (mp.find(j) != mp.end()) {
          int k = mp[j];
          if (pos[k] == pos[i]) {
            if (se[k])
              ans = max(ans, GCD[i] * (fi[i] + se[k]));
          } else
            ans = max(ans, GCD[i] * (fi[i] + fi[k]));
        }
  vis[u] = 1;
  // Process each subtree of the current centroid
  for (int i = hd[u]; i; i = nx[i]) {
    int v = nd[i];
    sum = sz[v]; // Size of current subtree
    // Handle leaf nodes
    if (sum == 1) {
      vis[v] = 1;
      continue;
    } else if (sum == 2) {
      for (int i = hd[v]; i; i = nx[i]) {
        int x = nd[i];
        if (!vis[x]) {
          ans = max(ans, we[i >> 1]);
          vis[v] = 1;
          vis[x] = 1;
          break;
        }
      }
      continue;
    }
    node = 0;
    locate(v, u);
    calc(node);
  }
}
// Main solution function for each test case
// Handles tree construction and initiates centroid decomposition
void solve() {
  cin >> n; // Read number of nodes
  auto add = [&](int u, int v) {
    nd[++tot] = v;
    nx[tot] = hd[u];
    hd[u] = tot;
  };
  auto adde = [&](int u, int v, ll w) {
    add(u, v);
    we[tot >> 1] = w;
    add(v, u);
  };
  for (int i = 1; i < n; i++) {
    int u, v;
    ll w;
    cin >> u >> v >> w;
    adde(u, v, w);
  }
  node = 0;
  sum = n;
  locate(1, 0);
  ans = 0;
  calc(node);
  cout << ans << '\n';
  if (T) {
    tot = 1;
    fill(hd, hd + n + 1, 0);
    fill(vis, vis + n + 1, 0);
  }
}
int main() {
  cin >> T;
  while (T--)
    solve();
}

// https://github.com/VaHiX/CodeForces/