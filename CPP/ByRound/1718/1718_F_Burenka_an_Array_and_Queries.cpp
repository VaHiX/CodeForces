// Problem: CF 1718 F - Burenka, an Array and Queries
// https://codeforces.com/contest/1718/problem/F

/*
Purpose:
This code solves the problem of answering queries about the count of integers from 1 to C that are coprime with the product of elements in a given subarray.

It uses a technique combining:
1. Preprocessing primes up to 20000 using sieve
2. Segment-based optimization with sqrt(n) blocks
3. Inclusion-exclusion principle combined with bitmask DP for fast computation

Time Complexity: O(n * sqrt(n) + q * sqrt(n) * 13 + m * log(log(m)) + C * log(C))
Space Complexity: O(n + m + C + q)
*/

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
typedef pair<int, int> pii;
typedef unsigned int u32;
#define fi first
#define se second
const int S = 2e4, B = 320; // S is max number for sieve, B is block size for sqrt decomposition
int pri[20004], num, w[800], tot;
bool f[20004]; // sieve boolean array
int n, m, C, q, id[100004], ID[100004], a[100004];
int cnt, CNT, p0[8000], p1[8000], v[8000]; // Prime factor info for preprocessing
u32 dp[8192][800]; // bitmask DP table for inclusion-exclusion
vector<int> fac[100004]; // Factor list for each element
int vis[100004]; // Visited prime counts for current window
u32 ans[100004]; // Final answer array
vector<pair<pii, int>> vec; // Query buffer with index for sorting

void init() {
  // Generate primes up to S using sieve of Eratosthenes
  for (int i = 2; i <= S; i++) {
    if (!f[i])
      pri[num++] = i;
    for (int j = 0; j < num && pri[j] * i <= S; j++) {
      f[pri[j] * i] = 1;
      if (i % pri[j] == 0)
        break;
    }
  }
  // Preprocess primes larger than 41 which can contribute to valid divisors
  for (int i = 0; i < num; i++)
    if (pri[i] > 41)
      if (pri[i] <= C && pri[i] <= m)
        ++cnt, p0[cnt] = pri[i], v[cnt] = pri[i];
  CNT = cnt;
  // Precompute products of two distinct primes (within C limit)
  for (int i = 0; i < num; i++)
    if (pri[i] > 41)
      for (int j = i + 1; j < num && pri[j] <= m; j++) {
        int t = pri[i] * pri[j];
        if (t > C)
          break;
        ++CNT, p0[CNT] = pri[i], p1[CNT] = pri[j], v[CNT] = t;
      }
}

void getfac(int p) {
  // Factorize array element
  int X = a[p];
  for (int i = 0; i < num && pri[i] * pri[i] <= X; i++)
    if (X % pri[i] == 0) {
      fac[p].push_back(pri[i]);
      while (X % pri[i] == 0)
        X /= pri[i];
    }
  if (X > 1)
    fac[p].push_back(X);
}

bool cmp(pair<pii, int> a, pair<pii, int> b) {
  // Custom comparator for block-based sorting of queries
  int ta = (a.fi.fi - 1) / B, tb = (b.fi.fi - 1) / B;
  return ta != tb ? (ta < tb) : (a.fi.se < b.fi.se);
}

void add(int p) {
  // Add prime factors to current window
  for (auto x : fac[p])
    vis[x]++;
}

void del(int p) {
  // Remove prime factors from current window
  for (auto x : fac[p])
    vis[x]--;
}

u32 calc(int p, int msk) {
  // Fast inclusion-exclusion with precomputed DP
  u32 ans = dp[msk][tot];
  for (int i = 1; i <= cnt; i++)
    if (vis[p0[i]])
      ans -= dp[msk][ID[v[i]]];
  for (int i = cnt + 1; i <= CNT; i++)
    if (vis[p0[i]] && vis[p1[i]])
      ans += dp[msk][ID[v[i]]];
  return ans;
}

int main() {
  scanf("%d%d%d%d", &n, &m, &C, &q), init();
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), getfac(i);
  // Preprocessing for divisors
  for (int i = 1; i <= C; i++)
    id[C / i] = 1;
  for (int i = 1; i <= C; i++)
    if (id[i])
      id[i] = ++tot, w[tot] = i;
  for (int i = 1; i <= C; i++)
    ID[i] = id[C / i];
  // DP table initialization
  for (int i = 1; i <= tot; i++)
    dp[0][i] = w[i];
  for (int i = 1; i < (1 << 13); i++) {
    int t = __builtin_ffs(i) - 1, j = i ^ (1 << t);
    for (int k = 1; k <= tot; k++)
      dp[i][k] = dp[j][k] - dp[j][id[w[k] / pri[t]]];
  }
  // Read queries into buffer
  for (int i = 0; i < q; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    vec.push_back({{l, r}, i});
  }
  sort(vec.begin(), vec.end(), cmp);
  int L = 1, R = 0;
  // Process queries
  for (auto [p, i] : vec) {
    auto [l, r] = p;
    while (R < r)
      add(++R);
    while (L > l)
      add(--L);
    while (R > r)
      del(R--);
    while (L < l)
      del(L++);
    int msk = 0;
    for (int j = 0; j < 13; j++)
      if (vis[pri[j]])
        msk |= (1 << j);
    ans[i] = calc(i, msk);
  }
  for (int i = 0; i < q; i++)
    printf("%u\n", ans[i]);
}


// https://github.com/VaHiX/CodeForces/