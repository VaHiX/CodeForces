// Problem: CF 749 D - Leaving Auction
// https://codeforces.com/contest/749/problem/D

/*
 * Purpose: Solve the auction problem where participants may be absent and
 *          we need to determine the winner based on the final valid bids.
 *
 * Algorithm:
 * 1. Process all bids and store them per participant.
 * 2. Identify the last bid of each participant from the original sequence.
 * 3. For each query:
 *    - Remove bids from absent participants.
 *    - Find the highest bid in the remaining sequence.
 *    - Determine the winner among non-absent participants based on valid bids.
 *
 * Time Complexity: O(n log n + q * n) where n is the number of bids and q is
 * number of queries. Space Complexity: O(n) for storing bids and order of
 * participants.
 */

#include <algorithm>
#include <iostream>
#include <random>
#include <set>
#include <stddef.h>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n;
  std::cin >> n;
  // Store bids for each participant
  std::vector<std::vector<int>> person(n);
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i] >> b[i];
    a[i]--;
    person[a[i]].push_back(b[i]);
  }
  // Determine the order of participants who made final bids
  std::vector<int> order;
  for (int i = n - 1; i >= 0; i--) {
    // If this is the last bid of the participant, add to order
    if (b[i] == person[a[i]].back()) {
      order.push_back(a[i]);
    }
  }
  int q;
  std::cin >> q;
  while (q--) {
    int k;
    std::cin >> k;
    std::set<int> got;
    while (k--) {
      int x;
      std::cin >> x;
      got.insert(x - 1); // Convert to 0-indexed
    }
    std::vector<int> wtf;
    // Find first valid participant who is not absent
    for (int i = 0; i < (int)order.size() && (int)wtf.size() < 2; i++) {
      if (!got.count(order[i])) {
        wtf.push_back(order[i]);
      }
    }
    // Output the result
    if (wtf.size() == 0) {
      std::cout << "0 0\n";
    } else if (wtf.size() == 1) {
      // Only one valid participant, output his first bid
      std::cout << wtf[0] + 1 << ' ' << person[wtf[0]][0] << '\n';
    } else {
      // Two valid participants, use first's bid to determine winner
      std::cout << wtf[0] + 1 << ' ';
      // Find the first bid of wtf[0] that is larger than wtf[1]'s last bid
      std::cout << *std::lower_bound(person[wtf[0]].begin(),
                                     person[wtf[0]].end(),
                                     person[wtf[1]].back())
                << '\n';
    }
  }
}

// https://github.com/VaHiX/CodeForces/