// Problem: CF 1778 F - Maximizing Root
// https://codeforces.com/contest/1778/problem/F

/*
 * Problem: Maximizing Root
 * 
 * Purpose: Given a rooted tree with integer values at each node, we can perform at most k operations.
 * Each operation allows choosing a subtree and multiplying all values in that subtree by a common divisor 
 * of all values in the subtree. Goal is to maximize the value of the root node after at most k operations.
 * 
 * Algorithm:
 * - Use DFS traversal to compute minimum operations needed to make each node divisible by each of
 *   its divisors (using dynamic programming).
 * - Precompute primes and divisors for optimization.
 * - For each node, use a DP table to store minimum operations to make each divisor of the node's value
 *   achievable by combining subtree operations.
 * - Finally, find the maximum value of the root by trying all divisors of root's initial value.
 *
 * Time Complexity: O(n * sqrt(V) * log(V) + T * sqrt(V) * log(V))
 * where n is number of nodes, V is max value (1000), and T is number of test cases.
 * 
 * Space Complexity: O(V * sqrt(V) + n)
 */
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define m_p(a, b) make_pair(a, b)
#define pb(a) push_back(a)
#define ll long long
#define ull unsigned long long
#define inf 0x7FFFFFFF
#define inff 9223372036854775807
#define rep(i, l, r) for (int i = l; i < r; ++i)
#define repp(i, l, r) for (int i = l; i <= r; ++i)
#define per(i, r, l) for (int i = r - 1; i >= l; --i)
#define go(i, x, y) for (int i = fir[x], y = e[i]; i; y = e[i = nxt[i]])
#define pii pair<int, int>
#define fi first
#define se second
#define p_q priority_queue
#define Kill(x)                                                                \
  {                                                                            \
    cout << x << endl;                                                         \
    return 0;                                                                  \
  }
#define all(x) x.begin(), x.end()
#define mod 1000000007
using namespace std;
inline int rd() {
  int x(0), f(1);
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-')
      f = -f;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + (ch ^ 48);
    ch = getchar();
  }
  return x * f;
}
inline void out(int X) {
  if (X < 0) {
    X = ~(X - 1);
    putchar('-');
  }
  if (X > 9)
    out(X / 10);
  putchar(X % 10 + '0');
}
ll pw(int x, int d) {
  if (!d)
    return 1;
  ll t = pw(x, d >> 1);
  t = t * t % mod;
  if (d & 1)
    return t * x % mod;
  return t;
}
#define MAX 100005
#define V 1005
#define sqrtV 65
int dp[MAX][sqrtV]; // dp[i][j] - min operations to make node i have value divisible by divisor j
int yz[sqrtV];      // array to store divisors of root's value
int num[V];         // num[i] = index of divisor i in yz array
int prm[V];         // primes up to V
bool isp[V];        // sieve array for prime detection
int frn[V];         // smallest prime factor of i
int frnyz[sqrtV];   // mapping from yz[i] to index of frn[yz[i]]
vector<int> pshyz[sqrtV]; // list of prime factors for yz[i]
vector<int> psh[V];   // prime factors of i
int frnp[V];        // largest prime factor of i
int a[MAX];         // values of vertices
int yzcnt;          // number of divisors
vector<int> v[MAX]; // adjacency list for tree
void dfs(int x, int fa) {
  // Update node value with gcd of its value and parent's value
  a[x] = __gcd(a[x], a[fa]);
  // Initialize dp for current node
  rep(i, 0, yzcnt) dp[x][i] = 1000000;
  // Mark divisors of current node's value as achievable in 0 operations
  repp(i, 0, num[a[x]]) {
    if (a[x] % yz[i] == 0) {
      dp[x][i] = 0;
    }
  }
  // Process each child
  for (auto to : v[x]) {
    if (to == fa)
      continue;
    dfs(to, x); // Recurse
    // Update dp for current node by combining with child's dp
    repp(i, 0, num[a[x]]) {
      if (a[x] % yz[i] == 0) {
        dp[x][i] =
            min(1000000, dp[x][i] + min(dp[to][frnyz[i]] + 1, dp[to][i]));
      }
    }
  }
  // Propagate from larger divisors to smaller ones for optimization
  per(i, num[a[x]] + 1, 0) {
    for (auto itm : pshyz[i])
      dp[x][itm] = min(dp[x][itm], dp[x][i]);
  }
  return;
}
signed main() {
#ifdef pp_orange
  freopen("in.in", "r", stdin);
  freopen("out.out", "w", stdout);
#endif
  rep(i, 2, V) isp[i] = 1;
  int pcnt = 0;
  int x, y;
  rep(i, 2, V) {
    if (isp[i]) {
      prm[pcnt++] = i;
      frn[i] = i;
      frnp[i] = i;
      psh[i].pb(i);
    }
    for (int j = 0; j < pcnt && (x = prm[j] * i) < V; j++) {
      isp[x] = 0;
      if (i % prm[j] == 0) {
        if (frnp[i] != 1) {
          frn[x] = frn[i];
          frnp[x] = 1;
        } else {
          frn[x] = frn[i] * prm[j];
          frnp[x] = prm[j];
        }
        break;
      }
      frn[x] = frn[i] * prm[j];
      frnp[x] = prm[j];
      psh[x] = psh[i];
      psh[x].pb(prm[j]);
    }
  }
  int T = rd();
  while (T--) {
    int n = rd();
    int k = rd();
    repp(i, 1, n) a[i] = rd();
    repp(i, 1, n) v[i].clear();
    rep(i, 1, n) {
      x = rd();
      y = rd();
      v[x].pb(y);
      v[y].pb(x);
    }
    // Initialize divisors of root value
    yzcnt = 0;
    for (int i = 1; i * i <= a[1]; i++) {
      if (a[1] % i == 0) {
        yz[yzcnt++] = i;
        if (i * i != a[1]) {
          yz[yzcnt++] = a[1] / i;
        }
      }
    }
    sort(yz, yz + yzcnt);
    rep(i, 0, yzcnt) num[yz[i]] = i;
    rep(i, 0, yzcnt) {
      frnyz[i] = num[frn[yz[i]]];
      pshyz[i] = psh[yz[i]];
      for (auto &itm : pshyz[i])
        itm = num[yz[i] / itm];
    }
    dfs(1, 1);
    int ans = a[1];
    per(i, yzcnt, 0) {
      if (dp[1][i] < k) {
        ans = a[1] * yz[i];
        break;
      }
    }
    cout << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/