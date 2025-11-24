// Problem: CF 1609 H - Pushing Robots
// https://codeforces.com/contest/1609/problem/H

/*
Problem: H. Pushing Robots
Purpose: Simulate the movement of n robots on a number line according to a cyclic instruction set.
         Answer queries about the position of specific robots at different time points.

Algorithms/Techniques:
- Simulation of robot movements with grouping logic
- Periodic behavior detection using cycle detection
- Mathematical optimization for large time queries

Time Complexity: O(n * k * log(n * k)) where n is number of robots and k is number of instructions
Space Complexity: O(n * k) for storing positions and instructions

The code simulates robot movement by:
1. Processing each time step in a cycle
2. Grouping robots based on instruction sums
3. Determining group movement direction and merging adjacent groups
4. Optimizing repeated cycles to avoid simulating each step individually
*/

#include <limits.h>
#include <string.h>
#include <algorithm>
#include <array>
#include <iostream>

#define For(i, l, r) for (register int i = (l); i <= (r); ++i)
#define For_down(i, r, l) for (register int i = (r); i >= (l); --i)
using namespace std;
constexpr int n_MAX = 100 + 5, k_MAX = 50 + 5, q_MAX = 1000 + 5;
constexpr long long inf_LL = (1LL << 60);
int n, m, k, q, F[k_MAX][n_MAX];
long long x[k_MAX][n_MAX], min_d[n_MAX];
inline long long d(const int t, const int i) {
  return (x[t][i + 1] - x[t][i] - 1);
}
namespace simulate {
long long *cur;
array<int, 3> a[n_MAX << 1];
void move_l(const int l, const int r) { For(i, l, r)-- cur[i]; }
void move_r(const int l, const int r) { For(i, l, r)++ cur[i]; }
void main(const int t) {
  cur = x[t + 1], memcpy(cur, x[t], (n + 1) << 3);
  int l = 1, r = 1, m = 0;
  while (l <= n) {
    while (((r + 1) <= n) && (!d(t, r)))
      ++r;
    const int min = (*min_element(F[t] + (l - 1), F[t] + (r + 1)));
    int p = 0, q = 0;
    For(i, l - 1, r) if (F[t][i] == min) {
      p = i;
      break;
    }
    For_down(i, r, l - 1) if (F[t][i] == min) {
      q = i;
      break;
    }
    a[++m] = {l, p, F[t][l - 1] - min};
    a[++m] = {q + 1, r, F[t][r] - min};
    const int next = (r + 1);
    l = r = next;
  }
  move_l(a[1][0], a[1][1]);
  for (int i = 2; i <= (m - 2); i += 2) {
    const int l0 = a[i][0], r0 = a[i][1];
    const int l1 = a[i + 1][0], r1 = a[i + 1][1];
    if (d(t, r0) == 1) {
      if (a[i + 1][2] >= a[i][2])
        move_l(l1, r1);
      else
        move_r(l0, r0);
    } else
      move_r(l0, r0), move_l(l1, r1);
  }
  move_r(a[m][0], a[m][1]);
}
}; // namespace simulate
struct operation {
  long long t;
  int i, j;
  inline bool operator<(const operation &other) const { return (t < other.t); }
};
operation op[q_MAX];
long long ans[q_MAX];
int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n >> k;
  For(i, 1, n) cin >> x[0][i];
  For(i, 1, n) For(t, 0, k - 1) cin >> F[t][i];
  For(t, 0, k - 1) For(i, 1, n) F[t][i] += F[t][i - 1];
  long long cur = 0;
  cin >> q;
  For(j, 1, q) cin >> op[j].i >> op[j].t, op[j].j = j;
  sort(op + 1, op + q + 1), op[q + 1].t = LONG_LONG_MAX;
  for (int j = 1; j <= q; ++m) {
    For(t, 0, k - 1) simulate::main(t);
    For(i, 1, n - 1) min_d[i] = d(0, i);
    For(t, 1, k - 1) For(i, 1, n - 1) min_d[i] = min(min_d[i], d(t, i));
    long long z = (inf_LL / k);
    For(i, 1, n - 1) {
      const long long d0 = d(0, i), d1 = d(k, i);
      if (d0 == d1)
        continue;
      else if (d0 < d1) {
        if (min_d[i] <= 1) {
          z = 0;
          break;
        }
      } else if (d0 > d1) {
        if (d0 <= (k * 2)) {
          z = 0;
          break;
        }
        z = min(z, (d0 - (k * 2)) / (d0 - d1));
      }
    }
    while (op[j].t <= (cur + (k * (z + 1)))) {
      const int i = op[j].i, t = (op[j].t % k);
      const long long z = ((op[j].t - cur) / k);
      ans[op[j].j] = (x[t][i] + ((x[k][i] - x[0][i]) * z)), ++j;
    }
    cur += (k * (z + 1));
    For(i, 1, n) x[0][i] += ((x[k][i] - x[0][i]) * (z + 1));
  }
  cerr << "m = " << m << '\n';
  For(i, 1, q) cout << ans[i] << '\n';
  return 0;
}


// https://github.com/VaHiX/CodeForces/