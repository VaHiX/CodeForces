// Problem: CF 1874 A - Jellyfish and Game
// https://codeforces.com/contest/1874/problem/A

/*
 * Problem: Jellyfish and Game
 * Algorithms/Techniques: Greedy strategy, Observation on parity of k
 * Time Complexity: O(n + m) per test case
 * Space Complexity: O(1)
 *
 * Description:
 * Two players (Jellyfish and Gellyfish) have n and m apples respectively.
 * They play k rounds. Odd rounds: Jellyfish can swap; even rounds: Gellyfish can swap.
 * Both try to maximize their own apple sum.
 * The solution analyzes the optimal swaps based on min/max values of apples,
 * and leverages that for large k (even), only parity matters.
 */

#include <algorithm>
#include <cstdio>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k;
    scanf("%ld %ld %ld", &n, &m, &k);
    long amn(1e9 + 7), amx(0), bmn(1e9 + 7), bmx(0);
    long long sa(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      sa += x; // Accumulate Jellyfish's initial sum
      amn = std::min(amn, x); // Track min value of Jellyfish's apples
      amx = std::max(amx, x); // Track max value of Jellyfish's apples
    }
    for (long p = 0; p < m; p++) {
      long x;
      scanf("%ld", &x);
      bmn = std::min(bmn, x); // Track min value of Gellyfish's apples
      bmx = std::max(bmx, x); // Track max value of Gellyfish's apples
    }
    if (bmx > amn) {
      sa += (bmx - amn); // If Gellyfish's max > Jellyfish's min, swap for gain
    }
    if (k % 2 == 0) {
      // For even k, after many rounds,
      // both players will have optimized their apples.
      // If k is large enough, we only care about final difference.
      sa += (std::min(bmn, amn) - std::max(bmx, amx));
    }
    printf("%lld\n", sa);
  }
}


// https://github.com/VaHiX/codeForces/