// Problem: CF 2051 A - Preparing for the Olympiad
// https://codeforces.com/contest/2051/problem/A

/*
A. Preparing for the Olympiad
Algorithm: Greedy
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

Monocarp wants to maximize the difference (m - s), where m is the number of problems he solves,
and s is the number of problems Stereocarp solves. 

Key insight:
- Monocarp can choose any subset of days to train.
- If Monocarp trains on day i (i < n), then Stereocarp trains on day i+1.
- On the last day, Stereocarp does not train.

Strategy:
We consider all possible ways for Monocarp to select training days and compute
the difference in total problems solved. 

The optimal strategy is to always include the last day in Monocarp's schedule,
as that maximizes his count (since he doesn't need to worry about the next day).

For each day i from 0 to n-2, if the difference between Monocarp's problems on day i
and Stereocarp’s problems on day i+1 is positive, we add it to the result. This simulates
the fact that in an optimal solution, we may want to avoid certain overlaps.

The first term is always a[n-1], because Monocarp should train on the last day.
Then, for every other day where Monocarp trains, we compare how much more he solves
than Stereocarp does on the following day.

*/

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
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    long res(a.back()); // Start with last day's Monocarp problems since that's always optimal
    for (long p = 0; p + 1 < n; p++) {
      long diff = (a[p] - b[p + 1]); // Difference on day p vs Stereocarp's day p+1
      res += (diff > 0 ? diff : 0);  // Only consider positive differences
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/