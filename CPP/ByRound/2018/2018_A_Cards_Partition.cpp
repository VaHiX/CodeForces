// Problem: CF 2018 A - Cards Partition
// https://codeforces.com/contest/2018/problem/A

/*
 * Problem: Cards Partition
 * Algorithm: Binary search + Greedy
 * Time Complexity: O(N log N) per test case, where N is the number of distinct card types
 * Space Complexity: O(1)
 *
 * The goal is to find the maximum possible size of a deck after buying up to k cards
 * and partitioning all cards such that:
 * 1. All decks have equal size.
 * 2. No two cards with same value are in the same deck.
 *
 * Approach:
 * - For each possible deck size d, check if it's feasible:
 *   - Total cards = sum of existing + k (max we can buy)
 *   - We must have at least d decks => total cards >= d * (number of decks)
 *   - Each deck needs distinct values, and max number of distinct values is n.
 *   - So a deck size d is valid if (total_cards / d) * d >= sum && (total_cards / d) >= max_card_value
 * - Use binary search over possible deck sizes to find maximum feasible value.
 */

#include <algorithm>
#include <iostream>

using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  const int N = 2e5 + 5;
  long long t, n, k, x, sum, mx;
  for (cin >> t; t--;) {
    cin >> n >> k;
    mx = sum = 0;
    for (int i = 1; i <= n; i++)
      cin >> x, sum += x, mx = max(mx, x); // Read input, compute total sum and max card value
    for (int i = n; i >= 1; i--) {
      // Check if a deck of size i is possible:
      // (sum + k) / i * i >= sum: means we can form at least 'i' decks with available cards
      // (sum + k) / i >= mx: ensures no single card value exceeds max capacity per deck
      if ((sum + k) / i * i >= sum && (sum + k) / i >= mx) {
        cout << i << "\n";
        break;
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/