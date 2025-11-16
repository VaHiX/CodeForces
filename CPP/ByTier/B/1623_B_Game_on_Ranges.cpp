// Problem: CF 1623 B - Game on Ranges
// https://codeforces.com/contest/1623/problem/B

/*
 * Problem: Game on Ranges
 * 
 * Purpose: Given a sequence of ranges picked by Alice during a game, 
 *          determine the number 'd' that Bob picked at each turn.
 * 
 * Algorithm:
 * - For each range [l, r] picked by Alice, we track how many times each number 
 *   in that range is "visited" (how many times it appears in a range).
 * - The number that Bob picked in a turn must have been visited the maximum 
 *   number of times among all numbers in that particular range.
 * - By sorting these counts (in descending order), we can infer Bob's picks 
 *   by using a greedy approach with a set of active ranges.
 * 
 * Time Complexity: O(n^2 * log n) in worst case due to sorting and set operations,
 *                   where n is the size of the range [1, n].
 * Space Complexity: O(n) for storing the vector and set of ranges.
 * 
 * Techniques:
 * - Set-based simulation of the game state
 * - Counting how often each element is picked using prefix-style incrementing
 * - Greedy assignment of 'd' to elements with highest visit counts
 */

#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<std::pair<long, long>> v(n + 1); // v[i].first = count, v[i].second = value i
    for (long p = 1; p <= n; p++) {
      v[p].second = p; // Initialize each element's value
    }
    for (long p = 0; p < n; p++) {
      long a, b;
      scanf("%ld %ld", &a, &b);
      for (long u = a; u <= b; u++) {
        ++v[u].first; // Increment visit count for each number in the range
      }
    }
    sort(v.begin(), v.end()); // Sort by visit count (ascending, so largest counts come last)
    std::set<std::pair<long, long>> s; // Set of active ranges [left, right]
    s.insert(std::make_pair(1, n)); // Initially, the whole range [1, n] exists
    for (long p = 1; p <= n; p++) {
      long d = v[p].second; // Get the number with the p-th highest count
      long left, right;
      for (std::set<std::pair<long, long>>::iterator it = s.begin();
           it != s.end(); it++) {
        left = it->first;
        right = it->second;
        if (left <= d && d <= right) { // If d is within current range
          s.erase(it); // Remove that range
          if (d > left) {
            s.insert(std::make_pair(left, d - 1)); // Add left sub-range
          }
          if (d < right) {
            s.insert(std::make_pair(d + 1, right)); // Add right sub-range
          }
          break;
        }
      }
      printf("%ld %ld %ld\n", left, right, d); // Output the range and Bob's pick
    }
    puts(""); // Print blank line between test cases
  }
}


// https://github.com/VaHiX/CodeForces/