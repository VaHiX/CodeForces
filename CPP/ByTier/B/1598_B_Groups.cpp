// Problem: CF 1598 B - Groups
// https://codeforces.com/contest/1598/problem/B

/*
B. Groups
Purpose: Determine if it's possible to split n students into two equal-sized groups,
         assign each group a different weekday for their lesson, and ensure all
         students can attend their assigned group's lesson day.

Algorithms/Techniques:
- For each pair of days (u,v), count how many students are available on both days (both),
  only on day u (first), only on day v (second), or on neither day (neither).
- Check all pairs of days to see if there exists a valid assignment where:
  - No student is excluded (i.e., neither[combo] == 0)
  - At least half of students are available for first group's day
  - At least half of students are available for second group's day

Time Complexity: O(D^2 * n) per test case, where D = 5 is the number of days
Space Complexity: O(D^2) for storing counts of combinations of day pairs
*/

#include <cstdio>
#include <map>
#include <vector>
#include <utility>

int main() {
  const int D = 5;  // Number of days in a week
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<std::pair<long, long>, long> first, second, both, neither;
    for (long row = 0; row < n; row++) {
      std::vector<int> f(D, 0);  // Stores availability of current student for each day
      for (long p = 0; p < D; p++) {
        scanf("%d", &f[p]);
      }
      for (long u = 0; u < D; u++) {
        for (long v = u + 1; v < D; v++) {  // Only check pairs where u < v to avoid duplicates
          std::pair<long, long> combo = std::make_pair(u, v);
          if (f[u] && f[v]) {  // Student available on both days
            ++both[combo];
          } else if (f[u]) {   // Student only available on day u
            ++first[combo];
          } else if (f[v]) {   // Student only available on day v
            ++second[combo];
          } else {             // Student not available on either day
            ++neither[combo];
          }
        }
      }
    }
    bool possible(false);
    for (long u = 0; !possible && u < D; u++) {
      for (long v = u + 1; !possible && v < D; v++) {
        std::pair<long, long> combo = std::make_pair(u, v);
        if (neither[combo] > 0) {  // If any student cannot attend either of days u or v, skip
          continue;
        }
        // Check if enough students are available for both groups:
        // first[combo] + both[combo] = # students available on day u
        // second[combo] + both[combo] = # students available on day v  
        if (first[combo] + both[combo] >= n / 2 &&
            second[combo] + both[combo] >= n / 2) {
          possible = true;
          break;
        }
      }
    }
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/