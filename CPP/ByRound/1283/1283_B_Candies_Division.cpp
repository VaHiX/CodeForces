// Problem: CF 1283 B - Candies Division
// https://codeforces.com/contest/1283/problem/B

/*
B. Candies Division
Algorithm: Greedy distribution with optimal grouping to satisfy constraints.
Time Complexity: O(1) per test case.
Space Complexity: O(1).

Santa wants to distribute n candies among k kids such that:
1. The difference between max and min candies given is at most 1.
2. Number of kids who get (min + 1) candies does not exceed floor(k/2).

Approach:
- First, we try to give each kid n/k candies, which is the base distribution.
- Then, some candies remain (n % k). These can be distributed one by one to different kids,
  increasing their count to (n/k + 1).
- The optimal strategy is to maximize the total number of candies used while respecting:
  - At most floor(k/2) kids can have (n/k + 1) candies.
  - We want to use as many candies as possible, so we distribute the remaining candies optimally.

The formula:
ans = k * (n / k) + min(k / 2, n % k)
Which means:
- Use k * (n / k) candies for base distribution.
- Distribute up to min(k / 2, n % k) additional candies to make some kids have one more.

This ensures we satisfy both constraints optimally.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long ans = k * (n / k) + ((k / 2) < (n % k) ? (k / 2) : (n % k)); // Compute maximum candies that can be distributed
    printf("%ld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/