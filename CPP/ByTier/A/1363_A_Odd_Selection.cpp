// Problem: CF 1363 A - Odd Selection
// https://codeforces.com/contest/1363/problem/A

/*
Problem: Odd Selection
Algorithm: Greedy + parity analysis
Time Complexity: O(n) per test case
Space Complexity: O(1)

Shubham has an array of size n, and wants to select exactly x elements such that their sum is odd.
The key insight is that a sum is odd if and only if there is an odd number of odd elements in the selection.
We count total odd numbers in the array. Then:
1. There must be at least one odd number (odd >= 1) to form an odd sum.
2. If we select all elements (x == n), we cannot have all odd numbers being even (since even number of odds would make sum even).
3. If all numbers are odd and x is even, we can't select an odd number of odds which makes the sum odd.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    long odd(0);  // Count of odd numbers in the array
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      odd += (a % 2);  // Increment if 'a' is odd
    }
    bool ans = (odd >= 1) && (!(x == n && odd % 2 == 0)) &&
               (!(odd == n && x % 2 == 0));  // Check constraints for valid selection
    puts(ans ? "Yes" : "No");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/