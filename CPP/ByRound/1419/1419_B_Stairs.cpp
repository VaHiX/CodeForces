// Problem: CF 1419 B - Stairs
// https://codeforces.com/contest/1419/problem/B

/*
B. Stairs
Algorithm: Greedy approach to maximize the number of nice staircases.
Time Complexity: O(log x) per test case due to the while loop which doubles y each iteration.
Space Complexity: O(1), only using a constant amount of extra space.

The problem asks to find the maximum number of "nice" staircases that can be built
using at most x cells. A staircase with n stairs consists of 1+2+...+n = n*(n+1)/2 cells.
A nice staircase can be covered by exactly n disjoint squares, which is possible only if 
the staircase has a specific structure (specifically, the number of cells must be such that
it allows for n disjoint unit squares covering each column properly).

The key insight is to greedily build staircases with increasing numbers of stairs,
starting from 1. For a staircase with n stairs, it uses n*(n+1)/2 cells.
We keep building staircases while we have enough cells such that:
x >= n*(n+1)/2
and we use y = n*(n+1)/2 for the next staircase.

We can also notice that for a staircase having n stairs we need n*(n+1)/2 units of space,
and then the next staircase with k stairs would require k*(k+1)/2 and so on.
By using a greedy strategy, we want to minimize the total number of cells used
while maximizing the number of complete staircases.

The loop checks if we can still build another staircase with current y = 2*y + 1 (starting with 1),
meaning it is checking for possible staircase sizes in a specific pattern.
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll x;
    scanf("%lld", &x);
    ll y(1), res(0);  // y represents the staircase size in steps, res counts the number of staircases
    while (2 * x >= y * (y + 1)) {  // Check if we can afford the next staircase with size y
      x -= y * (y + 1) / 2;  // Deduct the required cells for current staircase
      y = 2 * y + 1;  // Update to next potential staircase size based on pattern (1,3,7,15,...)
      ++res;  // Increment count of staircases built
    }
    printf("%lld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/