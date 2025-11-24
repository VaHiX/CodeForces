// Problem: CF 1130 A - Be Positive
// https://codeforces.com/contest/1130/problem/A

/*
Algorithm: 
  - Count the number of positive and negative elements in the array.
  - If the number of positive elements is at least ceil(n/2), we can use d = 1.
  - If the number of negative elements is at least ceil(n/2), we can use d = -1.
  - Otherwise, no suitable d exists, so output 0.

Time Complexity: O(n) - We iterate through the array once.
Space Complexity: O(1) - We only use a constant amount of extra space.
*/

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long neg(0), pos(0);  // Count of negative and positive numbers
  for (long p = 0; p < n; p++) {
    long a;
    scanf("%ld", &a);
    if (a > 0) {
      ++pos;  // Increment positive counter
    } else if (a < 0) {
      ++neg;  // Increment negative counter
    }
  }
  // If positive count is sufficient, use d = 1
  if (pos >= (n + 1) / 2) {
    puts("1");
  } 
  // If negative count is sufficient, use d = -1
  else if (neg >= (n + 1) / 2) {
    puts("-1");
  } 
  // Otherwise no valid d exists
  else {
    puts("0");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/