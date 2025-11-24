// Problem: CF 2035 G1 - Go Learn! (Easy Version)
// https://codeforces.com/contest/2035/problem/G1

/*
 * Problem: G1. Go Learn! (Easy Version)
 *
 * Algorithms/Techniques:
 * - Binary search simulation on arrays with constraints
 * - Dynamic programming with interval-based processing using segment tree-like logic
 * - Modular arithmetic for combinatorics and counting
 * - Tree decomposition for handling test conditions efficiently
 *
 * Time Complexity: O(n^2 * log n) per test case
 * Space Complexity: O(n^2) for storing intermediate structures like l[], r[], mul[]
 *
 */

#include <algorithm>
#include <assert.h>
#include <stdio.h>
#include <vector>
using namespace std;

const int mod = 998244353;

// Fast exponentiation with modular arithmetic
int power(int x, int y = mod - 2) {
  if (!y)
    return 1;
  int tmp = power(x, y >> 1);
  tmp = 1ll * tmp * tmp % mod;
  if (y & 1)
    tmp = 1ll * tmp * x % mod;
  return tmp;
}

int n, invn, m, a[300001], pos[300001], cur[300001], curmul[300001];
vector<int> l[300001], r[300001], mul[300001];

// Custom node structure for DP
struct Node {
  int len, cnt;
  Node() : len(0), cnt(0) {}
  Node(int _len, int _cnt) : len(_len), cnt(_cnt) {}
  
  // Addition operator for nodes (used in max/min decision)
  inline friend Node operator+(const Node x, const Node y) {
    if (x.len > y.len)
      return x;
    if (y.len > x.len)
      return y;
    return Node(x.len, (x.cnt + y.cnt) % mod);
  }

  // Subtraction operator ensuring same length
  inline friend Node operator-(const Node x, const Node y) {
    assert(x.len == y.len);
    return Node(x.len, (x.cnt - y.cnt + mod) % mod);
  }

  // Multiplication by an integer
  inline friend Node operator*(const Node x, const int y) {
    return Node(x.len, 1ll * x.cnt * y % mod);
  }
};

Node dp[300001], answer, f[300001], g[300001];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    invn = power(n);
    for (int i = 1; i <= n; i++)
      a[i] = pos[i] = 0;
    for (int i = 1; i <= m; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      if (y != 1 || x == 1)
        a[x] = y, pos[y] = x; // Store position of each value in the array
    }

    answer = Node(0, 1); // Initialize result node
    for (int i = 1; i <= n; i++) {
      l[i].clear(), r[i].clear(), mul[i].clear();
      dp[i] = f[i] = g[i] = Node(-1, 1), cur[i] = 0, curmul[i] = 1;
      
      // Build intervals for each index using binary search logic (segmentation)
      int L = 1, R = n;
      while (L < R) {
        int mid = (L + R) >> 1;
        if (i <= mid)
          mid != i ? r[i].push_back(mid) : void(), R = mid;
        else
          mid != i ? l[i].push_back(mid) : void(), L = mid + 1;
      }
      reverse(l[i].begin(), l[i].end());
      reverse(r[i].begin(), r[i].end());
    }

    // Modify intervals based on values assigned to elements
    for (int i = 1; i <= n; i++) {
      mul[i] = l[i];
      for (int &j : mul[i]) {
        int base = 1ll * (n - a[j] + 1) * invn % mod;
        while (cur[j] < (int)r[j].size() && r[j][cur[j]] < i)
          curmul[j] = 1ll * curmul[j] * base % mod, cur[j]++;
        j = curmul[j];
      }
    }

    // Calculate DP using interval propagation and update functions
    for (int i = 1; i <= n; i++) {
      if (!pos[i])
        continue;
      int x = pos[i], now = 1, base = 1ll * (i - 1) * invn % mod;
      
      // Update forward propagation to current node
      for (int j = 0; j < (int)l[x].size(); j++) {
        int y = l[x][j];
        dp[x] = dp[x] + (f[y] * i - g[y]) * now * invn;
        if (a[y])
          dp[x] = dp[x] + dp[y] * mul[x][j] * now;
        now = 1ll * now * base % mod;
      }
      
      dp[x] = dp[x] + Node(0, now), dp[x].len++;
      now = 1, base = 1ll * (n - i + 1) * invn % mod;

      // Update backward propagation from current node to children
      for (int j = 0; j < (int)r[x].size(); j++) {
        int y = r[x][j];
        f[y] = f[y] + dp[x] * now;
        g[y] = g[y] + dp[x] * now * i;
        now = 1ll * now * base % mod;
      }
      
      answer = answer + dp[x] * now; // Accumulate final answer
    }

    // Output required values
    printf("%d %lld\n", m - answer.len,
           1ll * answer.cnt * power(n, n - answer.len) % mod);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/