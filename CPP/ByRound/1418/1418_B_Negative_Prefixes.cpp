// Problem: CF 1418 B - Negative Prefixes
// https://codeforces.com/contest/1418/problem/B

/*
Algorithm: Greedy + Sorting
- Separate locked and unlocked elements.
- Sort unlocked elements in descending order to place larger values first.
- Place elements back in order, using locked elements as-is and unlocked elements in sorted order.
- The idea is to delay negative prefix sums as much as possible by placing large positive numbers early.

Time Complexity: O(n log n) - due to sorting the unlocked elements
Space Complexity: O(n) - for storing locked and unlocked elements

Approach:
1. Read input array and lock status.
2. Categorize elements into locked and unlocked lists.
3. Sort unlocked elements in descending order.
4. Reconstruct the array by placing locked elements as they are and unlocked elements in sorted order.
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
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    std::vector<int> locked(n);
    std::vector<long> vl, vu; // vl: locked values, vu: unlocked values
    for (long p = 0; p < n; p++) {
      scanf("%d", &locked[p]);
      if (locked[p]) {
        vl.push_back(v[p]); // locked values go to vl
      } else {
        vu.push_back(v[p]); // unlocked values go to vu
      }
    }
    sort(vu.rbegin(), vu.rend()); // sort unlocked values in descending order
    long a(0), b(0); // a: index for locked values, b: index for unlocked values
    for (long p = 0; p < n; p++) {
      printf("%ld ", locked[p] ? vl[a++] : vu[b++]); // place locked or unlocked values
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/