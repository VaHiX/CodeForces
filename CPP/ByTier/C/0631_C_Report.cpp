// Problem: CF 631 C - Report
// https://codeforces.com/contest/631/problem/C

/* 
 * C. Report
 * 
 * Purpose: Simulates a sequence of sorting operations on the first r elements of an array,
 *          where each operation sorts in either ascending (t=1) or descending (t=2) order.
 *          The final sorted array is output in reverse order as per the problem's requirement.
 * 
 * Algorithms/Techniques:
 *   - Uses a deque to efficiently perform operations on both ends of a segment.
 *   - Maintains a stack-like structure to optimize processing of overlapping operations.
 *   - Sorting operations applied from last to first in the operation list to determine
 *     how elements flow through the process.
 * 
 * Time Complexity: O(n log n + m)
 * Space Complexity: O(n + m)
 */
#include <algorithm>
#include <cstdio>
#include <deque>
#include <vector>
#include <utility>

int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<std::pair<int, long>> v;  // Stores operations in a compacted form
  long right(0);  // Tracks the furthest index affected by any operation so far
  for (long p = 0; p < m; p++) {
    int t;
    long r;
    scanf("%d %ld", &t, &r);
    --r;
    right = (right > r) ? right : r;
    // Remove redundant operations that are fully covered by the current one
    while (!v.empty() && v.back().second <= r) {
      v.pop_back();
    }
    // Skip if the same type of operation on the same range is already applied
    if (!v.empty() && v.back().first == t) {
      continue;
    }
    v.push_back(std::make_pair(t, r));
  }
  std::deque<long> d;  // Deque for efficient operations on both ends
  std::vector<long> b; // Vector for elements not affected by any operation
  for (long p = n - 1; p >= 0; p--) {
    if (p > right) {
      b.push_back(a[p]);  // Elements beyond the last operation are copied directly
    } else {
      d.push_back(a[p]);  // Elements within the range get added to deque for sorting
    }
  }
  sort(d.begin(), d.end());  // Sort the elements in the deque (they will be reorganized accordingly)
  for (long p = 0; p < v.size(); p++) {
    int t = v[p].first;   // Type of operation: 1 for ascending, 2 for descending
    long r = v[p].second; // Index up to which current operation applies
    long q = (p + 1 < v.size()) ? v[p + 1].second : -1; // Next operation's reach
    long diff = r - q;   // Number of elements this operation affects
    while (diff--) {
      if (d.empty()) break;
      if (t == 1) {    // Ascending order: take from the back of the sorted deque
        b.push_back(d.back());
        d.pop_back();
      } else {         // Descending order: take from the front of the sorted deque
        b.push_back(d.front());
        d.pop_front();
      }
    }
  }
  for (long p = n - 1; p >= 0; p--) {
    printf("%ld ", b[p]); // Output in reverse to match expected format
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/