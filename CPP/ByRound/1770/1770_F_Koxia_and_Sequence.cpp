// Problem: CF 1770 F - Koxia and Sequence
// https://codeforces.com/contest/1770/problem/F

/*
 * Problem: Koxia and Sequence
 * Purpose: Compute the total bitwise XOR of scores of all good arrays.
 * 
 * Algorithm:
 * - A good array satisfies:
 *   - Sum of elements equals x
 *   - Bitwise OR of all elements equals y
 * - The score of a good array is the XOR of all its elements.
 * - We are to compute the XOR of all such scores.
 * 
 * Key Insight:
 * - If n is odd, then the XOR of all elements in a valid array must equal y.
 * - Since we are only interested in the XOR of scores (which is the XOR of the whole array),
 *   and we know that for odd n, the result is always y, we can optimize:
 *   - Iterate over all subsets of bits of y (using bit manipulation: _ = (_ - 1) & y).
 *   - For each such subset, check if there exists a valid way to assign values to the array
 *     so that the constraints are satisfied.
 * 
 * Time Complexity: O(y * log(x)) where y < 2^20 and x < 2^60
 * Space Complexity: O(1)
 */

#include <stdio.h>
#include <iosfwd>

#define ll long long
using namespace std;
ll n, x;
int y, ans;
int main() {
  scanf("%lld%lld%d", &n, &x, &y);
  if (n & 1) { // Only process when n is odd
    for (int _ = y; _; _ = (_ - 1) & y) { // Iterate through all subsets of y
      for (int z = 1; z < 1048576; z <<= 1) // Try different powers of 2 as possible XOR value
        if ((_ & z) && x >= z && ((n * _ - z) & (x - z)) == x - z)
          ans ^= z; // Accumulate XOR result
    }
  }
  printf("%d\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/