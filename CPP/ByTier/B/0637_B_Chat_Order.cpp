// Problem: CF 637 B - Chat Order
// https://codeforces.com/contest/637/problem/B

/*
 * Purpose: Process a sequence of chat messages and output the final order of chats,
 *          where each chat moves to the top when a message is sent to that user.
 *          If the chat already exists, it is moved to the top without duplication.
 *
 * Algorithm: Use a set to track which users have been seen, and iterate from the end
 *            of the message list to the beginning. When a user is first encountered,
 *            output them and mark them as seen. This ensures the correct order is printed
 *            with the most recent chat at the top.
 *
 * Time Complexity: O(n log n) where n is the number of messages. Each insertion and lookup
 *                  in the set takes O(log n) time. We perform at most n such operations.
 *
 * Space Complexity: O(n) for storing the message sequence and the set of seen names.
 */

#include <iostream>
#include <set>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::vector<std::string> seq(n);
  std::set<std::string> names;
  for (long p = 0; p < n; p++) {
    std::cin >> seq[p];
  }
  for (long p = n - 1; p >= 0; p--) {
    // If the name has already been added, skip it to avoid duplication
    if (names.count(seq[p]) > 0) {
      continue;
    }
    // Insert the name into the set to mark as seen
    names.insert(seq[p]);
    // Output the name, which will be in reverse order due to iteration from end
    std::cout << seq[p] << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/