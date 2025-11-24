// Problem: CF 1249 D1 - Too Many Segments (easy version)
// https://codeforces.com/contest/1249/problem/D1

/*
Algorithm: Sweep Line with Greedy Approach
Purpose: To find the minimum number of segments to remove such that no integer point is covered by more than k segments.

Time Complexity: O(N * log N), where N is the maximum coordinate value (200 in this case), due to the use of set operations.
Space Complexity: O(N), for storing the events and auxiliary vectors.

Techniques:
- Sweep line algorithm to process segment events
- Use of std::set to maintain active segments, allowing efficient insertion and deletion
- Greedy removal of the segment that ends latest (to maximize future segment usage)
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
  std::vector<long> a(N);  // Difference array for coverage count
  std::vector<std::vector<std::pair<long, long>>> s(N);  // Start events: {end_point, segment_index}
  std::vector<std::vector<long>> t(N);  // End events: list of segment indices ending at this point
  for (long p = 0; p < n; p++) {
    long left, right;
    scanf("%ld %ld", &left, &right);
    ++a[left];  // Increment coverage at start
    --a[right + 1];  // Decrement coverage after end
    s[left].push_back(std::make_pair(right + 1, p + 1));  // Record start event
    t[right + 1].push_back(p + 1);  // Record end event
  }
  std::vector<long> rem;  // Indices of segments to be removed
  std::set<std::pair<long, long>> cur;  // Current active segments: {end_point, segment_index}
  for (long p = 0; p < N; p++) {
    // Remove segments that end at current point
    for (long u = 0; u < t[p].size(); u++) {
      cur.erase(std::make_pair(p, t[p][u]));
    }
    // Add segments that start at current point
    for (long u = 0; u < s[p].size(); u++) {
      cur.insert(s[p][u]);
    }
    // If too many segments are active, remove the one ending latest
    while (cur.size() > k) {
      std::set<std::pair<long, long>>::reverse_iterator it = cur.rbegin();  // Get the segment ending latest
      long x = it->first;
      long y = it->second;
      ++a[x];  // Mark the removal in the difference array (this affects future coverage)
      rem.push_back(y);  // Add to removal list
      cur.erase(*it);  // Remove it from active set
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