// Problem: CF 2039 F2 - Shohag Loves Counting (Hard Version)
// https://codeforces.com/contest/2039/problem/F2

/*
F2. Shohag Loves Counting (Hard Version)
Algorithms/Techniques: 
  - Moebius inversion
  - Suffix array / prefix processing
  - Dynamic programming with preprocessing using sieve-like approach
  - Modular arithmetic and fast input/output

Time Complexity: O(N log N) 
Space Complexity: O(N)

This code computes the number of "good" arrays of arbitrary length such that:
- Each element is in range [1, m]
- For an array of length n, f(k) = GCD of max values of all subarrays of length k
- A good array satisfies f(i) != f(j) for all pairs 1 <= i < j <= n

The solution uses dynamic programming over divisors and Moebius inversion principles to achieve efficient computation.
*/

#include <iosfwd>
#include <stdio.h>
#include <string.h>
using namespace std;
const int mod = 998244353;
const int N = 1e6;
int m, tp[N + 10], mu[N + 10], as[N + 10], f[N + 10];
void ad(int &x, int y) {
  x += y;
  if (x >= mod)
    x -= mod;
}
int ans[N + 10];
void sol() {
  int m;
  scanf("%d", &m);
  printf("%d\n", ans[m]);
}
bool fl[N + 10];
int pr[N + 10], gr[N + 10], gl[N + 10], pl[N + 10];
int id[60010000];
int main() {
  mu[1] = 1;
  for (int i = 1; i <= N; i++) {
    bool is = 0;
    if (i > 1 && !fl[i])
      is = 1;
    for (int j = i; j <= N; j += i) {
      if (is)
        fl[j] = 1;
      gr[j]++;
      if (is)
        pr[j]++;
      if (j != i)
        mu[j] -= mu[i];
    }
  }
  for (int i = 1; i <= N; i++)
    gr[i] += gr[i - 1];
  pr[0] = gr[N];
  for (int i = 1; i <= N; i++)
    pr[i] += pr[i - 1];
  for (int i = 1; i <= N; i++)
    gl[i] = gr[i - 1], pl[i] = pr[i - 1];
  memset(fl, 0, sizeof(fl));
  for (int i = 1; i <= N; i++) {
    bool is = 0;
    if (i > 1 && !fl[i])
      is = 1;
    for (int j = i; j <= N; j += i) {
      if (is)
        fl[j] = 1;
      id[++gl[j]] = i;
      if (is)
        id[++pl[j]] = i;
      if (j != i)
        mu[j] -= mu[i];
    }
  }
  for (int i = 1; i <= N; i++) {
    ans[i] = ans[i - 1];
    for (int t = gr[i - 1] + 1; t <= gr[i]; t++)
      as[id[t]] = tp[id[t]];
    for (int t = pr[i - 1] + 1; t <= pr[i]; t++) {
      int z = id[t], o = i / z;
      for (int d = gr[o - 1] + 1; d <= gr[o]; d++)
        ad(as[id[d] * z], as[id[d]]);
    }
    for (int t = gr[i - 1] + 1; t <= gr[i]; t++) {
      int j = id[t];
      ad(as[j], mod - f[j]);
      ad(as[j], as[j]);
      ad(as[j], 1);
      ad(f[j], as[j]);
      if (j == i)
        ad(ans[i], as[i]);
    }
    for (int t = pr[i - 1] + 1; t <= pr[i]; t++) {
      int z = id[t], o = i / z;
      for (int d = gr[o]; d > gr[o - 1]; d--)
        ad(as[id[d] * z], mod - as[id[d]]);
    }
    for (int t = gr[i - 1] + 1; t <= gr[i]; t++)
      ad(tp[id[t]], as[id[t]]);
  }
  int T;
  scanf("%d", &T);
  while (T--)
    sol();
  return 0;
}


// https://github.com/VaHiX/codeForces/