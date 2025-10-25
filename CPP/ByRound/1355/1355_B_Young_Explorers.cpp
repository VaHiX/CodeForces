// Problem: CF 1355 B - Young Explorers
// https://codeforces.com/contest/1355/problem/B

/*
B. Young Explorers
Algorithm: Greedy approach after sorting
Time Complexity: O(N log N) per test case due to sorting, where N is the number of explorers
Space Complexity: O(N) for storing the inexperience values

The problem requires grouping explorers such that each group has at least as many people as the maximum inexperience in that group.
We use a greedy strategy:
1. Sort explorers by inexperience in ascending order
2. For each explorer, try to place them in an existing group if possible, otherwise form a new group
3. An explorer can join a group only if their inexperience is less than or equal to the current size of that group

The key insight is to sort first and then greedily assign explorers to minimize the number of groups needed.
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
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.begin(), a.end()); // Sort inexperience values in ascending order
    long cnt(0), cur(0);
    for (long p = 0; p < n; p++) {
      ++cur; // Increment current group size
      if (a[p] <= cur) { // If explorer's inexperience allows joining current group
        ++cnt; // Form a new group
        cur = 0; // Reset current group size counter
      }
    }
    printf("%ld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/