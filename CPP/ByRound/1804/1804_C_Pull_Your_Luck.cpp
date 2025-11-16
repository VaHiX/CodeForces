// Problem: CF 1804 C - Pull Your Luck
// https://codeforces.com/contest/1804/problem/C

/*
 * Problem: Pull Your Luck
 *
 * Purpose: Determine if it's possible to spin a roulette wheel such that sector
 * 0 wins, given the number of sectors 'n', current sector 'x', and maximum pull
 * force 'p'.
 *
 * Algorithm:
 * - For each possible force from 1 to min(p, 5*n), calculate the total sectors
 * moved.
 * - Total sectors moved for force f is f*(f+1)/2 (sum of arithmetic sequence).
 * - Check if this total, modulo n, equals (n - x) % n, which is the required
 * offset to reach sector 0.
 *
 * Time Complexity: O(min(p, n)) per test case, since we iterate up to min(p,
 * 5*n) and each step is O(1). Space Complexity: O(1), only using a few
 * variables.
 *
 * Techniques: Mathematical simulation, modular arithmetic, optimization of loop
 * bounds.
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <set>
#include <shared_mutex>
#include <stdint.h>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <valarray>
#include <variant>
#include <vector>
using namespace std;

template <typename T> T input() {
  T res;
  cin >> res;
  return res;
}

int main() {
  std::iostream::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  for (int t = input<int>(); t; --t) {
    int n, x, p;
    cin >> n >> x >> p;
    bool ok = false;
    // We only need to check up to min(p, 5*n) because beyond that,
    // the pattern repeats due to modular arithmetic and the maximum
    // number of unique sums is bounded.
    for (int i = 1; i <= min(p, 5 * n) and not ok; ++i)
      // Total sectors moved for force i is i*(i+1)/2
      // We check if this moves us to sector 0:
      // (i*(i+1)/2) % n == (n - x) % n
      ok = ((i * int64_t(i + 1) / 2) % n == (n - x) % n);
    cout << (ok ? "Yes\n" : "No\n");
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/