// Problem: CF 1353 D - Constructing the Array
// https://codeforces.com/contest/1353/problem/D

/*
 * Problem: D. Constructing the Array
 *
 * Algorithm: Greedy with Priority Queue (Set)
 * Time Complexity: O(n log n) - Each element is inserted and removed from the set once, and each operation takes O(log n) time.
 * Space Complexity: O(n) - For storing the array and the set of segments.
 *
 * The algorithm simulates the process where at each step, we select the leftmost 
 * maximum-length segment of zeros and assign the next number to the appropriate middle position.
 * A set is used to efficiently retrieve the largest segment (by length), with tie-breaking by leftmost position.
 */

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
    std::vector<long> a(n, 0); // Initialize array with zeros
    std::set<std::pair<long, std::pair<long, long>>> s; // Set to store segments: {-length, {left, right}}
    s.insert(std::make_pair(n, std::make_pair(0, n - 1))); // Insert initial segment [0, n-1] of length n
    long cnt(0); // Counter for action numbers (1 to n)
    while (!s.empty()) {
      std::pair<long, std::pair<long, long>> cur = *s.begin(); // Get the largest segment
      s.erase(s.begin()); // Remove it from the set
      long left = cur.second.first;
      long right = cur.second.second;
      long mid = (left + right) / 2; // Compute middle point for odd-length segment
      a[mid] = ++cnt; // Assign current action number to middle position
      if (left < mid) {
        // Insert left subsegment into set if it exists
        s.insert(
            std::make_pair(-(mid - left + 1), std::make_pair(left, mid - 1)));
      }
      if (mid < right) {
        // Insert right subsegment into set if it exists
        s.insert(
            std::make_pair(-(right - mid + 1), std::make_pair(mid + 1, right)));
      }
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", a[p]); // Print result array
    }
    puts(""); // Newline after each test case
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/