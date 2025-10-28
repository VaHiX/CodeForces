// Problem: CF 1912 A - Accumulator Apex
// https://codeforces.com/contest/1912/problem/A

/*
 * Problem: Accumulator Apex
 * Algorithm/Techniques: Greedy algorithm with sorting and prefix sum tracking
 *
 * Time Complexity: O(N log N), where N is the total number of elements in all lists.
 * Space Complexity: O(N), for storing the intervals derived from list operations.
 *
 * Description:
 * In this game, Allyn starts with an accumulator value `x` and has `k` lists of integers.
 * On each turn, Allyn can take the leftmost element from any non-empty list,
 * but only if adding it to the accumulator keeps it non-negative.
 * The objective is to maximize the final value of the accumulator `x`.
 *
 * Approach:
 * - For each list, calculate how much we could "gain" by processing elements one-by-one.
 * - Track prefix sums and minimum prefix values as we go.
 * - Store intervals representing potential gains from operations.
 * - Sort these gain intervals.
 * - Process intervals greedily from smallest to largest gain (first key of interval),
 *   updating the accumulator value when possible.
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define int long long
using namespace std;
typedef pair<int, int> PII;
const int N = 2e5 + 5, mod = 998244353;
int T, x, k;

void solve() {
  cin >> x >> k;
  vector<PII> q; // Stores intervals (min_prefix_sum, gain) for greedy processing
  for (int i = 0, n; i < k; i++) {
    cin >> n;
    int minv = 0, last = 0, sum = 0;
    for (int j = 0, y; j < n; j++) {
      cin >> y;
      sum += y;
      minv = max(minv, -sum); // Track the minimum prefix needed to keep x non-negative during this sequence
      if (sum > last)
        q.push_back({minv, sum - last}), last = sum;
    }
  }
  sort(q.begin(), q.end()); // Sort by required minimal value for gain (greedy selection)
  for (auto t : q)
    if (x >= t.first) // If current x can support the minimum prefix needed
      x += t.second; // Add the net gain to accumulator
  cout << x << endl;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  solve();
}


// https://github.com/VaHiX/codeForces/