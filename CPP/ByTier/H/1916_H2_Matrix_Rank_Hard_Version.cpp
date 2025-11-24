// Problem: CF 1916 H2 - Matrix Rank (Hard Version)
// https://codeforces.com/contest/1916/problem/H2

/*
Algorithm: The problem requires counting the number of n x n matrices over the finite field GF(p) with a specific rank r.
We use the principle of counting matrices in terms of ranks, leveraging the formula for counting matrices of rank r over GF(p).
Key idea:
- For a matrix of rank r, we can count how many ways we can choose r linearly independent rows from n rows.
- This involves using Gaussian elimination principles in finite fields.
- The number of full-rank matrices is calculated first, then we subtract matrices with lower ranks.

Time Complexity: O(k)
Space Complexity: O(k)

This code implements the formula-based solution to compute the count for each rank from 0 to k.
*/

#include <stdio.h>
#include <iostream>

namespace Fwrite {
const int SZ = 1 << 15;
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
#define putchar Fwrite ::putchar
namespace Fast {
struct Writer {
  template <typename T> Writer &operator<<(T x) {
    if (x == 0) {
      putchar('0');
      return *this;
    }
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
#define cout Fast ::cout
#define ll long long
const int M = 998244353, MN = 5e5 + 1;
int pow_P[MN], ans[MN];
int pm(int a, ll b) {
  int ans = 1;
  while (b) {
    if (b & 1)
      ans = 1ll * ans * a % M;
    a = 1ll * a * a % M, b >>= 1;
  }
  return ans;
}
int main() {
  ll n;
  int p, k;
  std::cin >> n >> p >> k;
  int denom = 1, tag = k, pn = pm(p, n); // Compute p^n, and initialize denom to 1
  pow_P[0] = ans[0] = 1;
  for (int i = 1; i <= k; i++) {
    pow_P[i] = 1ll * pow_P[i - 1] * p % M; // Precompute powers of p up to k
    if (pow_P[i] == 1) { // If p^i = 1 mod M, it means we've entered a cycle
      tag = i - 1;
      break;
    }
  }
  for (int i = 1; i <= tag; i++) {
    ll t = (pn - pow_P[i - 1] + M) % M; // Compute part of product needed for matrix count
    ans[i] = 1ll * ans[i - 1] * t % M * t % M; // Update answer recursively
    denom = 1ll * denom * pow_P[i - 1] % M * (pow_P[i] - 1) % M; // Compute denominator
  }
  denom = pm(denom, M - 2); // Modular inverse of denominator
  for (int j = tag; j > 0; j--) {
    ans[j] = 1ll * ans[j] * denom % M; // Final division to get each count
    denom = 1ll * denom * pow_P[j - 1] % M * (pow_P[j] - 1) % M; // Update denominator for next step
  }
  cout << 1 << ' '; // Rank 0 case
  for (int i = 1; i <= k; i++)
    cout << ans[i] << ' ';
  cout << '\n';
}


// https://github.com/VaHiX/CodeForces/