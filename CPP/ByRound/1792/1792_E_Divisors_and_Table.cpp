// Problem: CF 1792 E - Divisors and Table
// https://codeforces.com/contest/1792/problem/E

/*
 * Problem: E. Divisors and Table
 * 
 * Approach:
 * 1. Factorize m = m1 * m2 into prime factors.
 * 2. Generate all divisors of m using the prime factorization.
 * 3. For each divisor d that can appear in an n×n multiplication table, 
 *    determine the minimum row index where it occurs.
 * 4. Count how many such divisors exist and compute their XOR.
 *
 * Time Complexity: O(√(m1 + m2) + d(m)) where d(m) is the number of divisors of m.
 * Space Complexity: O(d(m)) for storing the divisors and related arrays.
 * 
 * Algorithms/Techniques:
 * - Prime factorization
 * - Subset generation using bit manipulation
 * - Dynamic programming to find min row for each divisor
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <utility>

using namespace std;
inline int read() {
  int x = 0, f = 1;
  char ch = 0;
  while (!isdigit(ch)) {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
typedef long long ll;
const int mod = 998244353;
const int maxn = 1e5 + 10;
int T, m;
ll s, m1, m2;
int prm[100], tt[100];
ll nn[100], dd[maxn << 1], aa[maxn << 1];
int cnt;
int main() {
  T = read();
  while (T--) {
    s = read(), m1 = read(), m2 = read();
    cnt = 0;
    // Factorize m1 and m2 into prime factors
    for (int i = 2; i * i <= m1 || i * i <= m2; i++) {
      if (m1 % i == 0 || m2 % i == 0) {
        prm[++cnt] = i;
        int t = 0;
        while (m1 % i == 0) {
          m1 /= i;
          t++;
        }
        while (m2 % i == 0) {
          m2 /= i;
          t++;
        }
        tt[cnt] = t;
      }
    }
    // Handle remaining prime factors
    if (m1 == m2) {
      if (m1 != 1) {
        prm[++cnt] = m1;
        tt[cnt] = 2;
      }
    } else {
      if (m1 > m2)
        swap(m1, m2);
      if (m1 > 1)
        prm[++cnt] = m1, tt[cnt] = 1;
      if (m2 > 1)
        prm[++cnt] = m2, tt[cnt] = 1;
    }
    // Generate all divisors of m
    nn[0] = dd[0] = 1;
    for (int c = 1; c <= cnt; c++) {
      for (int i = nn[c - 1]; i < nn[c - 1] * (tt[c] + 1); i++) {
        dd[i] = dd[i - nn[c - 1]] * prm[c];
      }
      nn[c] = nn[c - 1] * (tt[c] + 1);
    }
    // Initialize array to store min row index for each divisor
    memset(aa, -1, nn[cnt] * sizeof(*aa));
    for (int i = 0; i < nn[cnt]; i++)
      if (dd[i] <= s)
        aa[i] = dd[i];
    // Dynamic Programming step to update minimum rows
    for (int c = 1; c <= cnt; c++) {
      for (int i = nn[c - 1]; i < nn[cnt]; i++) {
        if (i % nn[c] >= nn[c - 1])
          aa[i] = max(aa[i], aa[i - nn[c - 1]]);
      }
    }
    // Compute count of valid divisors and their XOR
    ll ans1 = 0, ans2 = 0;
    for (int i = 0; i < nn[cnt]; i++)
      if (aa[i] > 0 && dd[i] / aa[i] <= s)
        ans1++, ans2 ^= dd[i] / aa[i];
    printf("%lld %lld\n", ans1, ans2);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/