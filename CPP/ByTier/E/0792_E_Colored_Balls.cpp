// Problem: CF 792 E - Colored Balls
// https://codeforces.com/contest/792/problem/E

/*
 * Problem: E. Colored Balls
 * 
 * Purpose: 
 *   To divide all balls into minimum number of sets such that:
 *   - Each ball belongs to exactly one set.
 *   - No set is empty.
 *   - Each set contains only balls of one color.
 *   - The difference in sizes of any two sets is at most 1.
 * 
 * Approach:
 *   - Try different possible sizes for the sets.
 *   - For each possible size, check if it's valid using the 'check' function.
 *   - The valid size is then used to compute the minimum number of sets.
 * 
 * Time Complexity: O(sqrt(max_a) * n)
 * Space Complexity: O(1)
 * 
 * Algorithms/Techniques:
 *   - Binary search or brute-force on possible set sizes.
 *   - Greedy assignment of balls to sets.
 */

#include <stdio.h>
#include <algorithm>
#include <cmath>

using namespace std;
using ll = long long;
const int N = 1e6 + 10;
int a[N];
int tmp;
bool check(int sz, int rem, int n) {
  for (int i = 1; i <= n; ++i) {
    int x = a[i] / sz, y = a[i] % sz;
    if (y > x && rem)  // If remainder is greater than quotient and we have extra capacity, return false
      return 0;
    if (!rem) {
      if (y > x) {
        --sz;  // Reduce size of set to accommodate the remainder
        ++rem;  // Increase the remainder count
        x = a[i] / sz;
        y = a[i] % sz;
      }
      if (y > x)  // Still not feasible after adjustment
        return 0;
    }
  }
  tmp = sz;
  return 1;
}
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  sort(a + 1, a + n + 1);  // Sort the array to simplify processing
  
  const int M = (int)sqrt(a[1]) + 1;  // Try divisors up to sqrt of the largest number
  for (int i = 1; i <= M; ++i) {
    int sz = a[1] / i, rem = a[1] % i;
    if (check(sz, rem, n))  // Check if this size works for all boxes
      break;
  }
  ll rs = 0;
  for (int i = 1; i <= n; ++i)
    rs += (a[i] + tmp) / (tmp + 1);  // Calculate number of sets for each type of ball
  printf("%lld\n", rs);
}


// https://github.com/VaHiX/CodeForces/