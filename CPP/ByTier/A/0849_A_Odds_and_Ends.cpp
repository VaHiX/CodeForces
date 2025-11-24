// Problem: CF 849 A - Odds and Ends
// https://codeforces.com/contest/849/problem/A

/*
 * Problem: A. Odds and Ends
 * 
 * Purpose: Determine if an integer sequence can be divided into an odd number of 
 *          non-empty subsegments, each of odd length, starting and ending with odd numbers.
 * 
 * Algorithm/Techniques:
 * - Check if the length of the sequence is odd (required for an odd number of subsegments)
 * - Ensure that the first and last elements are odd (required for valid subsegment boundaries)
 * 
 * Time Complexity: O(n) - single pass through the array
 * Space Complexity: O(1) - only using a few variables regardless of input size
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  // Check if length is odd - necessary condition for odd number of subsegments
  bool possible(n & 1);
  for (long p = 0; p < n; p++) {
    long a;
    scanf("%ld", &a);
    // If first element is even, impossible to start a valid subsegment
    if ((p == 0) && !(a & 1)) {
      possible = false;
      break;
    }
    // If last element is even, impossible to end a valid subsegment
    if ((p == n - 1) && !(a & 1)) {
      possible = false;
      break;
    }
  }
  puts(possible ? "Yes" : "No");
  return 0;
}


// https://github.com/VaHiX/CodeForces/