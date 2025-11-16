// Problem: CF 1725 E - Electrical Efficiency
// https://codeforces.com/contest/1725/problem/E

/*
 * Problem: Electrical Efficiency
 * Algorithm: Tree Dynamic Programming + Sieve of Primes + Modular Arithmetic
 * 
 * Time Complexity: O(N * sqrt(MAX_A) + N)
 * Space Complexity: O(N * sqrt(MAX_A))
 * 
 * Approach:
 * - The tree structure allows us to use dynamic programming on trees.
 * - For each node, we track prime factors of the values assigned to factories.
 * - We maintain counts of how many times each prime factor appears in the subtree.
 * - For each triple (x, y, z), we calculate f(x, y, z) as the minimum number of lines 
 *   to turn on to allow communication between all three nodes.
 * - We also compute g(x, y, z) as the number of distinct primes in GCD(A_x, A_y, A_z).
 * - The calculation uses inclusion-exclusion principle over prime factors.
 * 
 * Key Techniques:
 * - Sieve-like prime factorization for numbers up to 2e5
 * - DFS with subtree DP
 * - Modular exponentiation for inverse
 * - Efficient swapping of maps for size optimization during merge
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#define int long long
using namespace std;
const int MAXN = 3e5 + 10;
const int mod = 998244353;
unordered_map<int, int> mp[MAXN];  // Maps prime factors to their counts in subtree
int n, colcnt[MAXN], res[MAXN], ans = 0, inv;  // colcnt stores count of each prime factor in entire tree
vector<int> col[MAXN];  // col[i] stores prime factors of A[i]
struct node {
  int nxt, to;
} e[MAXN * 4];
int head[MAXN], tot = 0;

// Add edge to adjacency list
void add(int x, int y) {
  e[++tot].nxt = head[x];
  e[tot].to = y;
  head[x] = tot;
}

// Fast exponentiation for modular inverse
int qpow(int base, int ret) {
  int ans = 1;
  while (ret) {
    if (ret & 1)
      ans = ans * base % mod;
    base = base * base % mod;
    ret /= 2;
  }
  return ans;
}

// DFS for computing contribution of each node
void dfs(int x, int fa) {
  for (int i = head[x]; i; i = e[i].nxt) {
    int v = e[i].to;
    if (v == fa)
      continue;
    dfs(v, x);
    // Optimize by ensuring mp[x] has size >= mp[v]
    if (mp[x].size() < mp[v].size()) {
      swap(mp[x], mp[v]);
      swap(res[x], res[v]);
    }
    // Merge results from child v into x
    for (auto i : mp[v]) {
      // Remove contribution of v's prime usage from x
      res[x] -= (colcnt[i.first] - 2) * mp[x][i.first] % mod *
                (colcnt[i.first] - mp[x][i.first]) % mod * inv % mod;
      res[x] = (res[x] + mod) % mod;
      // Update count of primes in x
      mp[x][i.first] += i.second;
      // Add new contribution
      res[x] += (colcnt[i.first] - 2) * mp[x][i.first] % mod *
                (colcnt[i.first] - mp[x][i.first]) % mod * inv % mod;
      res[x] = (res[x] + mod) % mod;
    }
  }
  ans += res[x];
  ans %= mod;
}

signed main() {
  ios::sync_with_stdio(0);
  cin >> n;
  inv = qpow(2, mod - 2); // Modular inverse of 2
  // Factorize each A[i] and track prime counts across all nodes
  for (int k = 1; k <= n; k++) {
    int x;
    cin >> x;
    for (int i = 2; i <= sqrt(x); i++) {
      if (x % i == 0) {
        col[k].emplace_back(i);
        colcnt[i]++;
      }
      while (x % i == 0)
        x /= i;
    }
    if (x != 1)
      col[k].emplace_back(x), colcnt[x]++;
  }
  // Build adjacency list
  for (int i = 1; i < n; i++) {
    int x, y;
    cin >> x >> y;
    add(x, y);
    add(y, x);
  }
  // Initialize for each node with its prime factors
  for (int i = 1; i <= n; i++) {
    for (auto j : col[i]) {
      mp[i][j]++;
      res[i] += (colcnt[j] - 2) * (colcnt[j] - 1) % mod * inv % mod;
      res[i] %= mod;
    }
  }
  dfs(1, 0); // Start DFS from root node 1
  cout << ans % mod;
  return 0;
}


// https://github.com/VaHiX/CodeForces/