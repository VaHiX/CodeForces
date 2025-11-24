// Problem: CF 2091 B - Team Training
// https://codeforces.com/contest/2091/problem/B

/*
B. Team Training

Algorithm: Greedy approach with sorting.
- Sort the array in descending order to process higher skill students first.
- Use a greedy strategy: form teams by including as few low-skilled members as possible,
  ensuring the team strength (count * min_skill) meets or exceeds x.
- Time Complexity: O(n log n) per test case due to sorting.
- Space Complexity: O(n) for storing the array.

Techniques:
- Sorting
- Greedy algorithm
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.rbegin(), a.rend()); // Sort in descending order
    long num(0), cnt(0);
    for (long p = 0; p < n; p++) {
      ++num; // Increment current team size
      if (num * a[p] >= x) { // Check if team strength meets threshold
        ++cnt; // Form a new team
        num = 0; // Reset team counter
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/