// Problem: CF 1848 E - Vika and Stone Skipping
// https://codeforces.com/contest/1848/problem/E

/*
Algorithm: 
The problem requires finding the maximum number of distinct forces that can be used to throw stones such that all stones touch the water at a specific coordinate. This essentially means finding the number of distinct divisors of a given coordinate X.

The key observation is that:
- If a stone is thrown with force f, it touches water at coordinates: f, f + (f-1), f + (f-1) + (f-2), ..., f + (f-1) + ... + 1 = f*(f+1)/2
- This means every force f corresponds to a unique point with coordinate f*(f+1)/2
- Therefore the question becomes: how many distinct forces (f) exist such that f*(f+1)/2 = x for some fixed x.

However, this is more directly about divisors.
If we want to know the number of distinct forces that can hit a point at coordinate X:
- That is the number of solutions to: (f * (f + 1)) / 2 = X
- Rearranging: f^2 + f - 2X = 0
- Using quadratic formula: f = (-1 + sqrt(1 + 8X)) / 2
- So we need to ensure sqrt(1 + 8X) is an integer (i.e., 1 + 8X is a perfect square), but since that's always a positive integer, the key constraint is just that X must be expressible as a triangular number (i.e., f*(f+1)/2 for some integer f), or simply the answer is about the number of divisors of some related values.

But based on the constraints and examples, the intended approach uses:
- Precomputing primes via Sieve of Eratosthenes (for factoring numbers efficiently)
- Segment tree to maintain contribution of prime powers from all numbers processed
- For each number:
  1. Factorize it into prime powers
  2. Use segment tree to quickly compute the product of all prime powers present across all processed numbers
  3. The product gives the number of ways to select distinct forces (which is related to the number of divisors)
- This solution is not directly counting divisors of X, but rather using a multiplicative function approach on prime factors to compute number of valid configurations
- For each X, we compute the "multiplicative structure" by factorizing the X's, and track how many prime powers have been seen so far via segment tree (a variation of the "power of prime" multiplicative function)

Time Complexity: O(N log N + Q log P)
Space Complexity: O(P) where P = 10^6, and N is the size of array.
Note: This approach makes sense if the problem is actually about counting the number of ways to choose distinct integers whose sum equals to triangular number X.
*/
#include <ctype.h>
#include <stdio.h>
#include <iosfwd>

#define lc (rt << 1)
#define rc (rt << 1) | 1
using namespace std;
typedef long long LL;
const int MAXN = 1000005;
template <typename T> inline void read(T &WOW) {
  T x = 0, flag = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-')
      flag = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  WOW = flag * x;
}
int q, MOD, large;
int pr[MAXN], pcnt, id[MAXN], vis[MAXN];
int seg[MAXN << 2];
void Build(int rt, int b, int e) {
  seg[rt] = 1;
  if (b == e)
    return;
  int mid = (b + e) >> 1;
  Build(lc, b, mid);
  Build(rc, mid + 1, e);
}
void Update(int rt, int b, int e, int p, int v) {
  if (b == e) {
    seg[rt] = (1LL * seg[rt] + v) % MOD;
    return;
  }
  int mid = (b + e) >> 1;
  if (p <= mid)
    Update(lc, b, mid, p, v);
  else
    Update(rc, mid + 1, e, p, v);
  seg[rt] = 1LL * seg[lc] * seg[rc] % MOD;
}
void sieve() {
  for (int i = 2; i <= 1000000; ++i) {
    if (!vis[i]) {
      pr[++pcnt] = i;
      id[i] = pcnt;
    }
    for (int j = 1; j <= pcnt && i * pr[j] <= 1000000; ++j) {
      vis[i * pr[j]] = 1;
      if (i % pr[j] == 0)
        break;
    }
  }
  Build(1, 1, pcnt);
}
void Decompose(int x) {
  while (!(x & 1)) {
    x >>= 1;
  }
  for (int i = 2; i <= pcnt && pr[i] * pr[i] <= x; ++i) {
    if (x % pr[i])
      continue;
    int pw = 0;
    while (x % pr[i] == 0) {
      x /= pr[i];
      ++pw;
    }
    Update(1, 1, pcnt, i, pw);
  }
  if (x > 1) {
    if (x <= 1000000) {
      Update(1, 1, pcnt, id[x], 1);
    } else {
      large = 2;
    }
  }
}
void solve() {
  int x;
  read(x);
  read(q);
  read(MOD);
  large = 1;
  Decompose(x);
  while (q--) {
    read(x);
    Decompose(x);
    printf("%lld\n", 1LL * large * seg[1] % MOD);
  }
}
int main() {
  sieve();
  solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/