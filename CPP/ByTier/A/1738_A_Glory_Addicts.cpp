// Problem: CF 1738 A - Glory Addicts
// https://codeforces.com/contest/1738/problem/A

/*
A. Glory Addicts
Algorithms/Techniques: Greedy, Sorting
Time Complexity: O(n * log n) per test case
Space Complexity: O(n) per test case

The hero has n skills, each of type fire (0) or frost (1), with initial damage values.
Skills can be performed in any order. When a skill is performed immediately after a skill of different type,
its damage is doubled. Otherwise, the damage remains the same.

Approach:
- Separate skills into two groups: fire (a[i] == 0) and frost (a[i] == 1)
- For each group, sort the damage values in ascending order
- The total damage is calculated as twice the sum of all initial damages
- Then, subtract the "cost" of the transition from one type to another:
  - If both types have equal count: remove the minimum from either group (whichever is smaller)
  - If fire > frost: the extra fire skills must be handled, so subtract smallest fire values
  - If frost > fire: the extra frost skills must be handled, so subtract smallest frost values
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<int> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%d", &a[p]);
    }
    std::vector<long> v, w; // v = fire skills, w = frost skills
    long long total(0);     // Total initial damage * 2
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (a[p]) {           // If frost skill
        v.push_back(x);
      } else {              // If fire skill
        w.push_back(x);
      }
      total += 2 * x;       // Add twice the damage for each skill (as per problem)
    }
    sort(v.begin(), v.end()); // Sort frost skills
    sort(w.begin(), w.end()); // Sort fire skills

    if (v.size() == w.size()) {
      // Equal number of both types: remove smallest from one group
      total -= (v[0] < w[0]) ? v[0] : w[0];
    } else if (v.size() > w.size()) {
      // More frost skills than fire: subtract the smallest frost skills
      for (long p = 0; p < v.size() - w.size(); p++) {
        total -= v[p];
      }
    } else if (w.size() > v.size()) {
      // More fire skills than frost: subtract the smallest fire skills
      for (long p = 0; p < w.size() - v.size(); p++) {
        total -= w[p];
      }
    }
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/