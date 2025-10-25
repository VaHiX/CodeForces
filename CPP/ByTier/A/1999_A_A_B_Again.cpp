// Problem: CF 1999 A - A+B Again?
// https://codeforces.com/contest/1999/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s(0);
    while (n) {
      s += n % 10;  // Extract last digit and add to sum
      n /= 10;      // Remove last digit from number
    }
    printf("%ld\n", s);
  }
}
/*
Problem: A+B Again?
Time Complexity: O(t * log n) where t is number of test cases and n is the input number
Space Complexity: O(1) - constant space usage

Algorithm: Digit Sum Computation
- For each test case, extract digits one by one using modulo and division operations
- Time complexity for each number: O(log n) where log n represents number of digits
- Space complexity: O(1) as we only use a constant amount of extra variables
*/

// https://github.com/VaHiX/codeForces/