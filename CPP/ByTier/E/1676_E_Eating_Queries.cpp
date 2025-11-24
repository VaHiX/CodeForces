// Problem: CF 1676 E - Eating Queries
// https://codeforces.com/contest/1676/problem/E

/*
E. Eating Queries

Algorithm: 
- Sort candies in descending order to greedily select the largest candies first for minimum count.
- Compute prefix sums of sorted candies to quickly determine total sugar for k candies.
- For each query, use binary search on prefix sums to find minimum number of candies needed.

Time Complexity: O(n log n + q log n) per test case
Space Complexity: O(n) for storing candies and prefix sums

Input/Output:
- First line contains t (number of test cases)
- For each test case:
  - First line contains n (number of candies), q (number of queries)
  - Second line contains n integers (sugar values of candies)
  - Next q lines contain x (target sugar quantity for each query)

Example:
Input:
3
8 7
4 3 3 1 1 4 5 9
1
10
50
14
15
22
30
4 1
1 2 3 4
3
1 2
5
4
6

Output:
1
2
-1
2
3
4
8
1
1
-1
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, q;
    scanf("%ld %ld", &n, &q);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    // Sort candies in descending order to greedily pick largest first
    sort(v.rbegin(), v.rend());
    // Compute prefix sums for quick total sugar calculation
    for (long p = 1; p < n; p++) {
      v[p] += v[p - 1];
    }
    while (q--) {
      long x;
      scanf("%ld", &x);
      long left(0), right(n - 1);
      // If target exceeds total sugar, impossible to reach
      if (x > v.back()) {
        puts("-1");
        continue;
      }
      long res(n - 1);
      // Binary search for minimum number of candies needed
      while (left <= right) {
        long mid = (left + right) / 2;
        if (x <= v[mid]) {
          res = mid + 1;     // Found a valid solution, try smaller
          right = mid - 1;
        } else {
          left = mid + 1;    // Too small, need more candies
        }
      }
      printf("%ld\n", res);
    }
  }
}


// https://github.com/VaHiX/codeForces/