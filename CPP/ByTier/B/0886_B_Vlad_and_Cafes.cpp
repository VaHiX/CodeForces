// Problem: CF 886 B - Vlad and Cafes
// https://codeforces.com/contest/886/problem/B

#include <cstdio>
#include <set>
#include <vector>
/**
 * @brief Finds the cafe index that Vlad hasn't visited for the longest time.
 * 
 * Algorithm:
 * - Traverse the list of cafe visits from the end to the beginning.
 * - Use a set to keep track of cafe indices already seen.
 * - When encountering a cafe index for the first time in this backward traversal,
 *   it means this is the last time this cafe was visited before any other cafe
 *   that will be visited later.
 * - The first such cafe index encountered in backward traversal is the answer.
 * 
 * Time Complexity: O(n log n) due to set operations (insert and count).
 * Space Complexity: O(n) for the vector and set storage.
 */
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::set<long> s;
  long res(0);
  for (long p = n - 1; p >= 0; p--) {
    if (s.count(a[p])) {
      // If cafe was already seen in backward traversal, skip it
      continue;
    }
    res = a[p]; // Update result to this cafe index
    s.insert(a[p]); // Mark this cafe as seen
  }
  printf("%ld\n", res);
  return 0;
}

// https://github.com/VaHiX/CodeForces/