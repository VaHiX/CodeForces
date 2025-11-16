// Problem: CF 845 C - Two TVs
// https://codeforces.com/contest/845/problem/C

/*
Algorithm: Event Processing with Sweep Line
Technique: Sweep line algorithm with event tracking
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing events

This code determines if Polycarp can watch all TV shows using only two TVs.
The approach is to treat each show's start and end as events. 
A start event decreases the count of available TVs, and an end event increases it.
If at any point more than 2 TVs are needed (count < -2), it's impossible to watch all shows.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<std::pair<long, int>> a(2 * n); // Create events: 2*n because each show has start and end
  for (long p = 0; p < n; p++) {
    long l, r;
    scanf("%ld %ld", &l, &r);
    a[2 * p] = std::make_pair(l, -1);   // Start event: decrease TV count
    a[2 * p + 1] = std::make_pair(r, 1); // End event: increase TV count
  }
  sort(a.begin(), a.end()); // Sort all events by time
  int count(0); // Current number of TVs in use (negative means unused)
  bool possible(true);
  for (long p = 0; p < a.size(); p++) {
    count += a[p].second; // Update TV count
    if (count < -2) {     // If more than 2 TVs are needed at any time
      possible = false;
    }
  }
  puts(possible ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/