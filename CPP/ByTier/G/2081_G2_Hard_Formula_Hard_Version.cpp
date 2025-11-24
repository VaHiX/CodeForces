// Problem: CF 2081 G2 - Hard Formula (Hard Version)
// https://codeforces.com/contest/2081/problem/G2

/*
Algorithm: 
This solution implements a complex algorithm for computing the sum of k mod φ(k) for k from 1 to n,
using a combination of number theory techniques such as:
1. Sieve of Euler for computing Euler's totient function φ(k)
2. Memoization and recursive decomposition
3. Digit dynamic programming principles
4. Fast computation using precomputed tables and mathematical identities
5. Optimized segment tree like structure for range queries

Time Complexity: O(n^(2/3)) - The algorithm uses a combination of sieve, recursive decomposition, and precomputed 
tables which gives it sub-linear complexity, specifically bounded by the cube root of n complexity of the main 
calculation.
Space Complexity: O(n^(2/3)) - The space is dominated by the arrays used for sieving and memoization tables.
*/

#include <cmath>
#include <cstdio>
#include <ctime>
#include <vector>
#include <algorithm>

using std::max;
using std::min;
typedef unsigned uint;
typedef unsigned long long ull;
namespace Sol {
const uint M = 3162277 + 5, Pi = 1001258 + 5, M2 = 15506304 + 5;
uint sum;
ull N;
uint F[M], G[M], F0[M], G0[M], F1[M], G1[M];
uint top, Sp[Pi], pri[Pi], pi[M], phi[M], pos[M2];
double g[Pi];
uint B, K, B2, n6, m, limit, lim, BIT[M2];
double st, ed;
struct nb {
  ull n;
  uint phi;
  nb(const ull &n = 1, const uint &phi = 1) : n(n), phi(phi) {}
};
std::vector<nb> d[Pi];
inline ull div(const ull &n, const ull &m) { return n * 1. / m; }
inline void Add(uint n, const uint &V) {
  while (n <= limit)
    BIT[n] += V, n += n & -n;
}
inline uint Qry(uint n) {
  uint ans(0);
  while (n)
    ans += BIT[n], n -= n & -n;
  return ans;
}
inline bool check(double P, ull n, uint k) {
  ull x(1);
  while (P > 1 && k <= m && x * pri[k] <= n)
    P *= g[k], x *= pri[k++];
  return P > 1;
}
inline bool DFS1(const ull &n, uint k, const ull &phi) {
  const ull &T = div(N, n);
  const uint &w = int(1. * n / phi) + 1;
  if (check(w * phi * 1. / n, T, k))
    return true;
  const uint &R = pi[min(div(w * phi, w * phi - n), min(ull(B), T))];
  for (; k <= m; ++k) {
    const uint &p = pri[k];
    if (p * p > T)
      break;
    if (k <= R)
      d[k].push_back(nb(n, phi)), n *p <= K && (lim = max(lim, k));
    for (ull x = n, tp = phi * (p - 1); x * p <= N; tp *= p)
      if (DFS1(x *= p, k + 1, tp))
        break;
  }
  if (k <= R)
    sum += phi * (Sp[R] - Sp[k - 1]);
  return false;
}
inline void DFS2(const uint &n, uint k, const uint &phi) {
  const uint &T = div(B2, n);
  (n <= B ? G[n] : F[div(N, n)]) += phi - n + 1;
  for (; k <= m; ++k) {
    const uint &p = pri[k], &T2 = div(B2, p);
    if (p > T)
      return;
    for (uint x = n, tp = phi * (p - 1); x <= T2; tp *= p)
      DFS2(x *= p, k + 1, tp);
  }
}
inline void DFS3(const uint &n, uint k, const uint &phi) {
  const uint &T = div(limit, n);
  Add(n, phi);
  for (; k <= m; ++k) {
    const uint &p = pri[k], &T2 = div(limit, p);
    if (p > T)
      return;
    for (uint x = n, tp = phi * (p - 1); x <= T2; tp *= p)
      DFS3(x *= p, k + 1, tp);
  }
}
void sieve(const uint &n) {
  phi[1] = 1;
  for (uint i = 2; i <= n; ++i) {
    if (!pos[i]) {
      pri[pos[i] = ++top] = i;
      if (i <= B)
        phi[i] = i - 1, g[top] = 1. * (i - 1) / i,
        Sp[top] = Sp[top - 1] + phi[i], pi[i] = 1;
    }
    for (uint x, j = 1; j <= pos[i] && (x = i * pri[j]) <= n; ++j) {
      pos[x] = j;
      if (x <= B)
        phi[x] = pos[i] == j ? phi[i] * pri[j] : phi[i] * phi[pri[j]];
    }
    if (i <= B)
      pi[i] += pi[i - 1];
  }
}
void Getphi(const ull &n) {
  std::vector<uint> id;
  for (uint i = 1; i <= B; ++i) {
    const ull &w = div(n, i);
    G1[i] = i * (i + 1ull) / 2;
    G0[i] = i;
    F1[i] = w * (w + 1) / 2;
    F0[i] = w;
  }
  for (uint i = 1; i <= pi[n6]; ++i) {
    const uint &p = pri[i], &lim = div(B, p);
    const ull &T = div(n, p);
    for (uint i = 1; i <= lim; ++i)
      F1[i] -= p * F1[i * p], F0[i] -= F0[i * p];
    for (uint i = lim + 1, j; i <= B; ++i)
      j = div(T, i), F1[i] -= p * G1[j], F0[i] -= G0[j];
    for (uint i = B, j = div(i, p); j; --j)
      for (uint e = j * p, V1 = p * G1[j], V0 = G0[j]; i >= e; --i)
        G1[i] -= V1, G0[i] -= V0;
  }
  fprintf(stderr, "DP of Getphi done %lf\n", ((ed = clock()) - st) / 1000);
  st = ed;
  DFS2(1, pi[n6] + 1, 1);
  for (uint i = n6 + 1; i <= B; ++i)
    if (pri[pos[i]] > n6)
      id.push_back(i);
  fprintf(stderr, "DFS of Getphi done %lf\n", ((ed = clock()) - st) / 1000);
  st = ed;
  for (uint i = 1 + 1; i <= B; ++i)
    G[i] += G[i - 1];
  F[B] += G[B];
  for (uint i = B - 1; i >= 1; --i)
    F[i] += F[i + 1];
  for (uint i = 1; i <= B; ++i)
    F[i] += F1[i] - F0[i], G[i] += G1[i] - G0[i];
  for (uint i = div(n, B2); i >= 1; --i) {
    const ull &T = div(n, i);
    const uint &lim = sqrt(T);
    F[i] = G0[lim] * G[lim] + F1[i] - F0[i];
    for (uint &x : id) {
      if (x > lim)
        break;
      const uint &w = div(T, x);
      F[i] -=
          i * x <= B ? F[i * x] + phi[x] * F0[i * x] : G[w] + phi[x] * G0[w];
    }
  }
  for (uint i = 1; i <= B; ++i)
    F1[i] = F[i], G1[i] = G[i];
  fprintf(stderr, "sieve of Getphi done %lf\n", ((ed = clock()) - st) / 1000);
  st = ed;
}
uint Solve(const ull &n) {
  st = clock();
  N = n;
  B = sqrt(N);
  n6 = pow(N, 1. / 6);
  B2 = n6 * B;
  K = min(uint(pow(N, 1. / 3) * log(N)), B);
  limit = div(N, K);
  sieve(limit);
  m = pi[B];
  fprintf(stderr, "sieve(%d) done %lf\n", limit, ((ed = clock()) - st) / 1000);
  st = ed;
  DFS1(1, 1, 1);
  fprintf(stderr, "DFS done %lf\n", ((ed = clock()) - st) / 1000);
  st = ed;
  Getphi(N);
  for (uint i = pi[n6]; i >= 1; --i) {
    const uint &p = pri[i], &T = B / p;
    const ull &k = div(N, p);
    if (i <= lim)
      for (nb &x : d[i])
        sum -= x.phi * (x.n <= B ? F[x.n] : G[div(N, x.n)]);
    for (uint i = 1; i <= T; ++i)
      F[i] -= F[i * p];
    for (uint i = T + 1; i <= B; ++i)
      F[i] -= G[div(k, i)];
    for (uint i = B, j = div(i, p); j; --j)
      for (uint e = j * p, V = G[j]; i >= e; --i)
        G[i] -= V;
    for (uint i = p, j = 1; i <= B; ++j)
      for (uint e = min(i + p, B + 1), V = p * G[j]; i < e; ++i)
        G[i] += V;
    for (uint i = B; i > T; --i)
      F[i] += p * G[div(k, i)];
    for (uint i = T; i >= 1; --i)
      F[i] += p * F[i * p];
    if (i <= lim)
      for (nb &x : d[i])
        sum += x.phi * (x.n <= B ? F[x.n] : G[div(N, x.n)]);
  }
  for (uint i = pi[n6] + 1; i <= lim; ++i) {
    const uint &p = pri[i], &T = B / p;
    const ull &k = div(N, p);
    for (nb &x : d[i])
      sum += x.phi * (x.n <= B ? F1[x.n] : G1[div(N, x.n)]);
    for (uint i = 1; i <= T; ++i)
      F1[i] -= p * F1[i * p];
    for (uint i = T + 1; i <= B; ++i)
      F1[i] -= p * G1[div(k, i)];
    for (uint i = B, j = div(i, p); j; --j)
      for (uint e = j * p, V = p * G1[j]; i >= e; --i)
        G1[i] -= V;
    for (uint i = p, j = 1; i <= B; ++j)
      for (uint e = min(i + p, B + 1), V = G1[j]; i < e; ++i)
        G1[i] += V;
    for (uint i = B; i > T; --i)
      F1[i] += G1[div(k, i)];
    for (uint i = T; i >= 1; --i)
      F1[i] += F1[i * p];
    for (nb &x : d[i])
      sum -= x.phi * (x.n <= B ? F1[x.n] : G1[div(N, x.n)]);
  }
  fprintf(stderr, "case1 done %lf\n", ((ed = clock()) - st) / 1000);
  st = ed;
  Add(1, 1);
  for (uint i = top; i > m; --i)
    Add(pri[i], pri[i] - 1);
  for (uint i = m; i > lim; --i) {
    const uint &p = pri[i];
    for (nb &x : d[i]) {
      ull n = N / x.n / p, phi = x.phi * (p - 1);
      while (n)
        sum += phi * Qry(n), n /= p, phi *= p;
    }
    for (ull x = p, phi = p - 1; x <= limit; x *= p, phi *= p)
      DFS3(x, i + 1, phi);
  }
  fprintf(stderr, "case2 done %lf\n", ((ed = clock()) - st) / 1000);
  st = ed;
  sum += F[1];
  return n * (n + 1) / 2 - sum;
}
} // namespace Sol
namespace sol {
uint top, pri[10005], pos[10005], phi[10005];
inline uint solve(const uint &N) {
  uint sum(0);
  phi[1] = 1;
  for (uint i = 2; i <= N; ++i) {
    if (!pos[i])
      pri[pos[i] = ++top] = i, phi[i] = i - 1;
    for (uint x, j = 1; j <= pos[i] && (x = i * pri[j]) <= N; ++j)
      phi[x] = (pos[x] = j) == pos[i] ? phi[i] * pri[j] : phi[i] * (pri[j] - 1);
    sum += i % phi[i];
  }
  return sum;
}
} // namespace sol
signed main() {
  ull n;
  scanf("%llu", &n);
  if (n <= 10000)
    return printf("%u\n", sol::solve(n)), 0;
  printf("%u\n", Sol::Solve(n));
}


// https://github.com/VaHiX/CodeForces/