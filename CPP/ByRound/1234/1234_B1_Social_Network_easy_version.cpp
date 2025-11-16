// Problem: CF 1234 B1 - Social Network (easy version)
// https://codeforces.com/contest/1234/problem/B1

#include <cstdio>
#include <set>
#include <vector>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::set<long> s;                    // Set to store current conversations (for fast lookup)
  std::vector<long> v(k, 0);           // Vector to maintain order of conversations on screen
  long idx(0);                         // Index to track where next element should be inserted
  for (long p = 0; p < n; p++) {
    long w;
    scanf("%ld", &w);
    if (s.count(w)) {                  // If conversation already exists, do nothing
      continue;
    }
    if (!v[idx]) {                     // If the position is empty, no need to erase
      // Do nothing
    } else {
      s.erase(v[idx]);                 // Remove the conversation that will be pushed out
    }
    s.insert(w);                       // Insert new conversation
    v[idx++] = w;                      // Place it in the array and increment index
    idx %= k;                          // Wrap around if necessary
  }
  printf("%ld\n", s.size());           // Print number of conversations shown
  long start = (idx - 1 + k) % k;      // Calculate start position for printing (last inserted)
  for (long p = 0; p < k; p++) {
    long id = v[(k + start - p) % k];  // Traverse backwards to get correct order
    if (id <= 0) {                     // Skip empty slots
      continue;
    }
    printf("%ld ", id);                // Print conversation ID
  }
  puts("");                            // Newline after output
  return 0;
}
/*
 * Problem: Social Network (easy version)
 *
 * Purpose:
 * This program simulates a social network conversation list on a smartphone that can show at most k conversations.
 * It processes a sequence of messages and updates the displayed conversation list accordingly.
 *
 * Algorithm:
 * - Uses a sliding window approach with a vector to maintain order of current conversations.
 * - Simulates insertion and removal from the front/back of a list using an array with modulo indexing.
 * - Uses a set for fast lookup of whether a conversation is currently displayed.
 *
 * Time Complexity: O(n * log k) where n is number of messages and k is max conversations.
 * Space Complexity: O(k) as we store at most k conversations.
 */

// https://github.com/VaHiX/codeForces/