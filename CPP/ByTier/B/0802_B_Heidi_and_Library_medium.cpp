// Problem: CF 802 B - Heidi and Library (medium)
// https://codeforces.com/contest/802/problem/B

/*
 * Problem: Heidi and Library (medium)
 * 
 * Algorithm: 
 *   - Use a greedy approach with a set to manage the "next occurrence" of each element.
 *   - For each position, we track when the element at that position will next appear.
 *   - Maintain a set of these "next occurrences" to simulate a cache with capacity k.
 *   - If the element is already in the set, we don't need to pay for it.
 *   - Otherwise, we increment the cost and possibly evict the largest "next occurrence" 
 *     to respect the capacity k.
 * 
 * Time Complexity: O(n * log n) due to set operations (insert, erase, find)
 * Space Complexity: O(n) for storing vectors and the set
 */

#include <cstdio>
#include <set>
#include <vector>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> a(n + 1, 0), next(n + 1, n + 1), last(n + 1, n + 1);
  for (int p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  // Preprocess: for each element, find the next occurrence
  for (int p = n - 1; p >= 0; p--) {
    next[p] = last[a[p]];  // Store the previous occurrence of a[p]
    last[a[p]] = p;        // Update the latest occurrence of a[p]
  }
  long cost(0);
  std::set<long> s;
  for (int p = 0; p < n; p++) {
    // If current position is in the set, remove it (it's being accessed)
    if (s.count(p)) {
      s.erase(p);
    } else {
      // Otherwise, this is a new access - increment cost
      ++cost;
    }
    // If the set is at capacity, remove the largest element (furthest next occurrence)
    if (s.size() >= k) {
      s.erase(--s.end());
    }
    // Insert the next occurrence of the current element into the set
    s.insert(next[p]);
  }
  printf("%ld\n", cost);
  return 0;
}


// https://github.com/VaHiX/CodeForces/