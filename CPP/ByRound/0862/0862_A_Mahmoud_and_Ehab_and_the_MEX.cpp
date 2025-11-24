// Problem: CF 862 A - Mahmoud and Ehab and the MEX
// https://codeforces.com/contest/862/problem/A

/*
 * Problem: Mahmoud and Ehab and the MEX
 * Purpose: Determine the minimum number of operations to make a set 'evil',
 *          where 'evil' means the MEX (minimum excluded value) of the set is exactly x.
 * 
 * Algorithm:
 * - Use a boolean vector to track which numbers from 0 to 100 are present in the input set.
 * - To make the MEX equal to x:
 *   - All integers from 0 to x-1 must be present (so we can subtract missing ones).
 *   - The integer x itself must NOT be present (to ensure MEX is exactly x).
 * - Count how many of the numbers 0 to x-1 are missing, and whether x is present.
 * 
 * Time Complexity: O(n + x), where n is the size of the input set and x is the target MEX.
 * Space Complexity: O(1), since the vector size is fixed at 101 (constant space).
 */

#include <cstdio>
#include <vector>
int main() {
  const long N = 101;
  long n, x;
  scanf("%ld %ld", &n, &x);
  std::vector<bool> v(N, 0);  // Vector to track presence of numbers 0 to 100
  for (long p = 0; p < n; p++) {
    long u;
    scanf("%ld", &u);
    v[u] = 1;  // Mark the number as present
  }
  long count(v[x]);  // If x is already in the set, we need to remove it (1 operation)
  for (long p = 0; p < x; p++) {
    count += (1 - v[p]);  // Count how many numbers from 0 to x-1 are missing
  }
  printf("%ld\n", count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/