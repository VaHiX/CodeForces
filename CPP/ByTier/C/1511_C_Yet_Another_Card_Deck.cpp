// Problem: CF 1511 C - Yet Another Card Deck
// https://codeforces.com/contest/1511/problem/C

/*
C. Yet Another Card Deck
Algorithms/Techniques: Set-based simulation with lazy updates
Time Complexity: O((n + q) * log n)
Space Complexity: O(n)

The problem simulates a card deck where we need to find the first card of a given color from the top,
move it to the top, and repeat this process for multiple queries.

We use a set of pairs (position, color) to maintain cards in order.
For each query:
1. Find the first card with target color by iterating through the set.
2. Print its position.
3. Remove that card and insert a new card at the top (negative position to simulate top placement).
*/

#include <cstdio>
#include <set>
#include <utility>

int main() {
  long N = 57;
  long n, q;
  scanf("%ld %ld", &n, &q);
  std::set<long> k; // Set to track seen colors
  std::set<std::pair<long, long>> s; // Set of {position, color} pairs
  for (long p = 1; p <= n; p++) {
    long x;
    scanf("%ld", &x);
    if (k.count(x)) {
      continue; // Skip duplicate colors (only keep first occurrence)
    }
    s.insert(std::make_pair(p, x)); // Insert card with its position and color
  }
  for (long p = 0; p < q; p++) {
    long target;
    scanf("%ld", &target);
    long cnt(1); // Counter to track position
    std::set<std::pair<long, long>>::iterator it = s.begin(); // Iterator for traversal
    // Find first card with the target color
    for (it = s.begin(); it->second != target && it != s.end(); it++) {
      ++cnt; // Increment counter as we move through set
    }
    printf("%ld ", cnt); // Print the position of the found card
    s.erase(it); // Remove the card from its current place
    s.insert(std::make_pair(-p, target)); // Insert at top with negative index to mark new position
  }
  puts(""); // Print newline at end
}


// https://github.com/VaHiX/codeForces/