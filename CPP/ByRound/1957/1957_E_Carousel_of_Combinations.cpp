// Problem: CF 1957 E - Carousel of Combinations
// https://codeforces.com/contest/1957/problem/E

/*
 * Code Purpose: This program calculates the sum of C(i, j) mod j for all i from 1 to n and j from 1 to i,
 * where C(i, j) is the number of ways to arrange j distinct numbers from {1, 2, ..., i} in a circle.
 * The result is computed modulo 10^9 + 7.
 *
 * Algorithms/Techniques:
 * - Sieve-based computation for Euler's totient function (phi) with optimizations.
 * - Prefix sum techniques for efficient query processing.
 *
 * Time Complexity: O(n log n) for preprocessing, O(1) per query
 * Space Complexity: O(n)
 */

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <bitset>
#include <vector>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
const int SZ = 1 << 15;
inline namespace qGet {
char buf[SZ], *S, *T;
inline char gc() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, SZ, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
int re() {
  char ch = gc();
  int x = ch - '0';
  while (isdigit(ch = gc()))
    x = x * 10 + (ch - '0');
  return x;
}
} // namespace qGet
inline namespace qPut {
char buf[SZ], *S = buf, *T = buf + SZ;
inline void flush() {
  fwrite(buf, 1, S - buf, stdout);
  S = buf;
}
inline void pc(char c) {
  *S++ = c;
  if (S == T)
    flush();
}
struct NTR {
  ~NTR() { flush(); }
} ztr;
void wr(int x) {
  if (!x)
    pc('0');
  static int sta[45];
  int top = 0;
  while (x)
    sta[++top] = x % 10, x /= 10;
  while (top)
    pc('0' + sta[top--]);
  pc('\n');
}
} // namespace qPut
const int n = 1e6 + 1;
int main() {
  int p = 1e9 + 7;
  vector<int> f(n);
  bitset<n> b;
  // Sieve-based calculation of Euler's totient function (phi)
  for (int i = 2; i < n; ++i)
    if (!b[i])
      for (int j = i, t = 0; j < n; j += i) {
        t ? --t, --f[j] : f[j] += t = i - 1;
        b[j] = 1;
      }
  // Adjust some values based on modular arithmetic and pattern
  for (int k = 1, i = 2; i < n; ++i) {
    if (++k == 4)
      f[i] += 2;
    else if (k == 8) {
      f[i] -= 2;
      k = 0;
    }
    f[i] += f[i - 1];
    if (f[i] >= p)
      f[i] -= p;
  }
  // Compute the prefix sum of the array to answer queries efficiently
  for (int i = 2; i < n; ++i) {
    f[i] += f[i - 1];
    if (f[i] >= p)
      f[i] -= p;
  }
  p = re();
  while (p--)
    wr(f[re()]);
}


// https://github.com/VaHiX/CodeForces/