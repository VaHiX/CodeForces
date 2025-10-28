// Problem: CF 2030 G1 - The Destruction of the Universe (Easy Version)
// https://codeforces.com/contest/2030/problem/G1

/*
G1. The Destruction of the Universe (Easy Version)
time limit per test4 seconds
memory limit per test512 megabytes

Algorithms/Techniques:
- Sweep line technique with coordinate compression
- Dynamic programming with inclusion-exclusion principle
- Binomial coefficient precomputation with modular arithmetic
- Bit manipulation for power of 2 computation

Time Complexity: O(n^2 log n)
Space Complexity: O(n)

Problem Summary: 
We have n planets, each with an interval of vulnerability [l, r].
We want to compute the sum of minimum number of expansions over all non-empty subsets of planets such that the intervals of all planets in the subset intersect at least one common point.

Each expansion can shift a planet's interval left or right by 1 unit. For any subset, score = minimal expansions needed.
We use sweep line + inclusion-exclusion to efficiently calculate results.
*/

#include <algorithm>
#include <stdio.h>
#include <tuple>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
using tup = tuple<int, int, int>;
const int N = 200005, P = 998244353;
int n, l[N], r[N], fac[N], inv[N], pr[N], su[N], f[N], g[N], f2[N];
tup p[2 * N];

void Inc(int &x, int y) {
  if ((x += y) >= P)
    x -= P;
}
void Dec(int &x, int y) {
  if ((x -= y) < 0)
    x += P;
}

int bp(int x, int y) {
  int r = 1;
  for (; y; y = y >> 1, x = 1ll * x * x % P)
    if (y & 1)
      r = 1ll * r * x % P;
  return r;
}

int C(int x, int y) {
  if (x < y)
    return 0;
  return 1ll * fac[x] * inv[y] % P * inv[x - y] % P;
}

void solve() {
  scanf("%d", &n), fac[0] = inv[0] = 1;
  rep(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % P, inv[i] = bp(fac[i], P - 2);
  f2[0] = 1;
  rep(i, 1, n) f2[i] = 2ll * f2[i - 1] % P;

  int m = 0;
  rep(i, 1, n) scanf("%d%d", &l[i], &r[i]), p[++m] = {l[i], 0, i}, // event start
                                            p[++m] = {r[i], 1, i}; // event end

  sort(p + 1, p + m + 1); // Sort events by x coordinate, then by type (end before start)

  pr[0] = f[0] = 0;
  rep(i, 1, m) {
    pr[i] = pr[i - 1], f[i] = f[i - 1];
    if (get<1>(p[i]) == 1) { // if event is an end point
      Inc(pr[i], 1);
      Inc(f[i], get<0>(p[i]));
    }
  }

  su[m + 1] = g[m + 1] = 0;
  per(i, m, 1) {
    su[i] = su[i + 1], g[i] = g[i + 1];
    if (get<1>(p[i]) == 0) { // if event is a start point
      Inc(su[i], 1);
      Inc(g[i], get<0>(p[i]));
    }
  }

  int as = 0;
  rep(i, 1, m - 1) {
    int c1 = pr[i];     // Number of active intervals ending before p[i]
    int c2 = su[i + 1]; // Number of active intervals starting after p[i]

    int x, y, z; // x: point, y: event type (0=start, 1=end), z: planet index
    tie(x, y, z) = p[i];

    if (y == 0) { // If it's a start event
      int tp = 0;
      Inc(tp, 1ll * g[i + 1] * C(c1 + c2 - 1, c2) % P); // contribution due to end events after
      Dec(tp, 1ll * f[i] * C(c1 + c2 - 1, c1) % P);     // contribution due to start events before
      Inc(as, 1ll * tp * f2[n - c1 - c2 - 1] % P);       // Multiply by number of ways to choose other intervals
    } else { // If it's an end event
      int tp = 0;
      Dec(tp, 1ll * x * C(c1 + c2 - 1, c1) % P); // Subtract cost of shrinking left side
      if (c1 > 1)
        Dec(tp, 1ll * f[i - 1] * C(c1 + c2 - 2, c1) % P); // Adjust for previous start events
      Inc(tp, 1ll * g[i + 1] * C(c1 + c2 - 2, c1 - 1) % P); // Add cost of extending right side
      Inc(as, 1ll * tp * f2[n - c1 - c2] % P);               // Multiply by combinations of uninvolved intervals
    }
  }

  printf("%d\n", as);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    solve();
}


// https://github.com/VaHiX/codeForces/