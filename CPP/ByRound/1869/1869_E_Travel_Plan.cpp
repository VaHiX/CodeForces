// Problem: CF 1869 E - Travel Plan
// https://codeforces.com/contest/1869/problem/E

/*
 * Problem: E. Travel Plan
 * 
 * Purpose: 
 *   Calculate the sum of scores of all possible travel plans where each city can be assigned 
 *   a value from 1 to m, and the score is the sum of maximum values along all simple paths 
 *   between pairs of cities.
 *
 * Algorithm/Techniques:
 *   - Tree structure modeling: Cities form a binary tree where node i connects to 2*i and 2*i+1.
 *   - Dynamic Programming with precomputed paths and distances for each level
 *   - Fast exponentiation to calculate powers
 *   - Modular arithmetic for all computations
 *
 * Time Complexity: O(log(n) * m) per test case due to preprocessing and iteration over m values
 * Space Complexity: O(log(n) * log(n)) for precomputed path and distance arrays
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define mod 998244353
#define oo 1000000010
const int N = 200010;
const int LOG = 63;
int fastpower(int num, long long po) {
  int fres = 1;
  while (po > 0) {
    if (po & 1)
      fres = (long long)fres * num % mod;
    po >>= 1;
    num = (long long)num * num % mod;
  }
  return fres;
}
long long n;
int m;
int lastpo[N];
vector<int> paths[LOG], dist[LOG];
inline void add(int &x, int val) {
  x += val;
  if (x >= mod)
    x -= mod;
}
inline void rem(int &x, int val) {
  x -= val;
  if (x < 0)
    x += mod;
}
void solve() {
  scanf("%lld%d", &n, &m);
  long long leaves = 1, tmp;
  long long cur = 1;
  int lvl = 0;
  while (cur < n) {
    cur *= 2;
    cur++;
    leaves *= 2;
    lvl++;
  }
  leaves -= cur - n;
  vector<int> v((lvl + 1) * 2, 0);
  v[1] = leaves % mod;
  if (lvl > 0) {
    for (int tmp2, i = 0; (1LL << i) < leaves; i++) {
      tmp2 = (1LL << i) % mod;
      tmp = leaves / (1LL << (i + 1));
      tmp %= mod;
      add(v[i * 2 + 3],
          ((long long)(((long long)tmp * tmp2) % mod) * tmp2) % mod);
      tmp = leaves % (1LL << (i + 1));
      if (tmp > (1LL << i)) {
        tmp -= (1LL << i);
        tmp %= mod;
        add(v[i * 2 + 3], (long long)tmp * tmp2 % mod);
      }
    }
    for (int i = 0; i < (int)paths[lvl - 1].size(); i++) {
      add(v[i], paths[lvl - 1][i]);
    }
    leaves %= mod;
    add(v[2], leaves);
    for (int i = 0; i <= lvl - 2; i++) {
      add(v[i + 3], leaves);
      for (int j = 0; j < (int)dist[i].size(); j++) {
        add(v[i + j + 4], leaves * dist[i][j] % mod);
      }
    }
  }
  vector<int> po((int)v.size(), 0);
  for (int i = 0; i < (int)v.size(); i++) {
    po[i] = fastpower(m, n - i);
  }
  int ans = 0;
  for (int cur2, last, j = 1; j <= m; j++) {
    cur2 = 1;
    for (int cur, i = 1; i < (int)v.size(); i++) {
      if (j == 1)
        lastpo[i] = 0;
      cur2 = (long long)cur2 * j % mod;
      last = cur2 - lastpo[i];
      lastpo[i] = cur2;
      if (last < 0)
        last += mod;
      cur = (long long)last * po[i] % mod;
      cur = (long long)cur * v[i] % mod;
      add(ans, (long long)j * cur % mod);
    }
  }
  printf("%d\n", ans);
}
int main() {
  paths[0] = {0, 1};
  dist[0] = {1};
  for (int lvl = 1; lvl < LOG; lvl++) {
    dist[lvl].resize(lvl + 1, 0);
    paths[lvl].resize((lvl + 1) * 2, 0);
    dist[lvl][0] = 1;
    paths[lvl][1] = 1;
    for (int i = 0; i < (int)dist[lvl - 1].size(); i++) {
      add(dist[lvl][i + 1], dist[lvl - 1][i] * 2LL % mod);
      add(paths[lvl][i + 2], dist[lvl - 1][i] * 2LL % mod);
    }
    for (int i = 0; i < (int)paths[lvl - 1].size(); i++) {
      add(paths[lvl][i], paths[lvl - 1][i] * 2LL % mod);
    }
    for (int i = 0; i < (int)dist[lvl - 1].size(); i++) {
      for (int j = 0; j < (int)dist[lvl - 1].size(); j++) {
        add(paths[lvl][i + j + 3],
            (long long)dist[lvl - 1][i] * dist[lvl - 1][j] % mod);
      }
    }
  }
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/