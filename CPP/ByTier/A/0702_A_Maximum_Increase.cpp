// Problem: CF 702 A - Maximum Increase
// https://codeforces.com/contest/702/problem/A

#include <cstdio>
/*
 * Problem: Maximum Increase
 * 
 * Purpose: Find the maximum length of an increasing subarray in a given array.
 * 
 * Algorithm: 
 *   - Use a sliding window approach to track the current length of increasing subarray.
 *   - When the current element is greater than the previous one, increment the current length.
 *   - Otherwise, reset the current length to 1.
 *   - Keep track of the maximum length seen so far.
 * 
 * Time Complexity: O(n) - Single pass through the array.
 * Space Complexity: O(1) - Only using a constant amount of extra space.
 * 
 * Techniques: 
 *   - Linear scan with state tracking
 *   - Sliding window paradigm
 */
int main() {
  long n;
  scanf("%ld\n", &n);
  long best(0), current(0), last(0); // best: max length found, current: current increasing subarray length, last: previous element
  while (n--) {
    long x;
    scanf("%ld", &x);
    if (x > last) { // if current element is greater than last element
      ++current; // extend the current increasing subarray
    } else {
      current = 1; // reset current length to 1
    }
    last = x; // update last element
    best = (current > best) ? current : best; // update best if current is greater
  }
  printf("%ld\n", best);
  return 0;
}

// https://github.com/VaHiX/CodeForces/