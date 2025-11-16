// Problem: CF 1249 D2 - Too Many Segments (hard version)
// https://codeforces.com/contest/1249/problem/D2

/*
Algorithm: Sweep Line with Priority Queue (Set)
Purpose: Remove minimum number of segments so that no point is covered by more than k segments.

Approach:
- Use a sweep line technique to process events (start and end of segments).
- At each event point, maintain a set of active segments (ordered by their end points).
- If the number of active segments exceeds k, remove the segment that ends latest (greedy choice).
- This ensures we minimize removals by keeping segments that end later as long as possible.

Time Complexity: O(n log n) - Each segment is inserted and removed from the set at most once.
Space Complexity: O(n) - For storing events and auxiliary data structures.

The code uses a difference array approach to track coverage and a set to manage active segments efficiently.
*/

#include <cstdio>
#include <set>
#include <vector>
#include <iterator>
#include <utility>

int main() {
  const long N = 2e5 + 7;
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> a(N); // Difference array to track coverage changes
  std::vector<std::vector<std::pair<long, long>>> s(N); // Start events: {end_point, segment_index}
  std::vector<std::vector<long>> t(N); // End events: segment indices
  for (long p = 0; p < n; p++) {
    long left, right;
    scanf("%ld %ld", &left, &right);
    ++a[left]; // Mark start of segment
    --a[right + 1]; // Mark end of segment
    s[left].push_back(std::make_pair(right + 1, p + 1)); // Store start event
    t[right + 1].push_back(p + 1); // Store end event
  }
  std::vector<long> rem; // Indices of removed segments
  std::set<std::pair<long, long>> cur; // Active segments, sorted by end point
  for (long p = 0; p < N; p++) {
    // Remove segments that end at current point
    for (long u = 0; u < t[p].size(); u++) {
      cur.erase(std::make_pair(p, t[p][u]));
    }
    // Add segments that start at current point
    for (long u = 0; u < s[p].size(); u++) {
      cur.insert(s[p][u]);
    }
    // If more than k segments are active, remove the one ending latest
    while (cur.size() > k) {
      std::set<std::pair<long, long>>::reverse_iterator it = cur.rbegin(); // Get the latest ending segment
      long x = it->first;
      long y = it->second;
      ++a[x]; // Update difference array
      rem.push_back(y); // Mark segment for removal
      cur.erase(*it); // Remove from active set
    }
  }
  printf("%ld\n", rem.size());
  for (long p = 0; p < rem.size(); p++) {
    printf("%ld ", rem[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/