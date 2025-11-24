// Problem: CF 2018 F3 - Speedbreaker Counting (Hard Version)
// https://codeforces.com/contest/2018/problem/F3

/*
F3. Speedbreaker Counting (Hard Version)
Algorithms/Techniques: Dynamic Programming, Modular Arithmetic, Preprocessing Factorials
Time Complexity: O(n^2) per test case
Space Complexity: O(n^2)

This problem counts the number of valid arrays a[1], ..., a[n] such that for each i,
city i is conquered at time no later than a[i], under specific constraints. This is solved
using dynamic programming with precomputed factorials and modular inverses to count the number
of solutions for different values of k (number of good starting cities).
*/

#include <ctype.h>
#include <iosfwd>
#include <stdio.h>
#define For(i, a, b) for (int i = (a), en = (b); i <= en; ++i)
#define Rof(i, a, b) for (int i = (a), en = (b); i >= en; --i)
#define Tra(u, i) for (int i = hd[u]; ~i; i = e[i].net)
#define cst const
#define LL long long
#define DD double
#define LD long double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define inf 0x3f3f3f3f
#define Inf 0x3f3f3f3f3f3f3f3f
#define eps 1e-12
using namespace std;

template <class T> void read(T &x) {
  char ch;
  bool ok;
  for (ok = 0, ch = getchar(); !isdigit(ch); ch = getchar())
    if (ch == '-')
      ok = 1;
  for (x = 0; isdigit(ch); x = x * 10 + ch - '0', ch = getchar())
    ;
  if (ok)
    x = -x;
}

#define maxn 3000
int T, n, P;
int f[maxn + 5], g[maxn + 5][maxn + 5], as[maxn + 5], fac[maxn + 5],
    ifac[maxn + 5];

// Fast power function for modular exponentiation
int fp(int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1)
      res = 1ll * res * x % P;
    x = 1ll * x * x % P;
    y >>= 1;
  }
  return res;
}

void mian() {
  read(n);
  read(P);
  fac[0] = 1;
  For(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % P;
  ifac[n] = fp(fac[n], P - 2); // Modular inverse of factorial
  Rof(i, n - 1, 0) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P; // Precompute inverses

  int sum = 0, sum_as[2] = {0, 0}; // sum: current running sum of inverse factorials, sum_as: accumulated sums
  Rof(len, n, 1) {
    if (len != n)
      f[len] = (1ll * (n - len) * f[len + 1] % P +
                1ll * fac[n - len - 1] * sum % P) %
               P; // DP recurrence for function f
    else
      f[len] = 1; // Base case
    sum = (sum + 1ll * ifac[n - len] * f[len] % P) % P; // Update the running sum
    as[len] = 1ll * f[len] * fac[n - len + len / 2] % P * ifac[n - len] % P *
              fac[n - len / 2] % P * ifac[n - len] % P; // Compute contribution of this length
    as[len] = (as[len] - sum_as[1] + P) % P; // Subtract previous accumulated sum
    sum_as[0] = (sum_as[0] + as[len]) % P;
    sum_as[1] = (1ll * sum_as[1] + as[len] + sum_as[0]) % P;
  }
  as[0] = 1;
  For(i, 1, n) as[0] = 1ll * as[0] * n % P; // Compute total number of valid sequences with all starting cities
  For(i, 1, n) as[0] = (as[0] - as[i] + P) % P;
  For(i, 0, n) printf("%d ", as[i]);
  puts("");
}

int main() {
  read(T);
  while (T--) {
    mian();
  }
}


// https://github.com/VaHiX/codeForces/