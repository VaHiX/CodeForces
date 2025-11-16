// Problem: CF 1594 A - Consecutive Sum Riddle
// https://codeforces.com/contest/1594/problem/A

/*
Purpose: Solve the consecutive sum riddle by finding two integers l and r such that the sum of all integers from l to r equals n.
Algorithm: 
    - The key insight is to use the arithmetic series formula to express the sum of consecutive integers from l to r.
    - We can rewrite the sum as: (r - l + 1) * (l + r) / 2 = n
    - Rearranging, we get: (r - l + 1) * (l + r) = 2 * n
    - A simple solution is to choose l = -(n - 1) and r = n, which ensures the sum equals n.
    - For example: if n = 6, then l = -5, r = 6. Sum = (-5) + ... + 6 = 6.
    - This works because it's a symmetric range centered around 0, and simplifies to n.

Time Complexity: O(1) - constant time per test case.
Space Complexity: O(1) - constant space usage.
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);  // Read number of test cases
  while (t--) {
    ll n;
    scanf("%lld", &n);  // Read the target sum
    printf("%lld %lld\n", -(n - 1), n);  // Output the calculated l and r
  }
}


// https://github.com/VaHiX/CodeForces/