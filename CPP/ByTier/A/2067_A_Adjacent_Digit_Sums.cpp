// Problem: CF 2067 A - Adjacent Digit Sums
// https://codeforces.com/contest/2067/problem/A

/*
Problem: Determine if there exists an integer n such that S(n) = x and S(n+1) = y,
where S(a) denotes the sum of digits of a.

Algorithms/Techniques: Digit manipulation, modular arithmetic

Time Complexity: O(1) per test case
Space Complexity: O(1)

The key insights are:
1. If y = x + 1, then n+1 is just n with a +1 increase in last digit (e.g., 199 -> 200).
2. If x > y, we can think of n+1 as n with some trailing 9s turned to 0s and a carryover of -1:
   For instance, 999 -> 1000 where digit sum reduced by 9*countOfNines + 1.
3. This leads us to test whether (x - y + 1) is divisible by 9 for such cases.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    // Check if it's possible: 
    // Case 1: y == x + 1 -> n ends in something like 9...9 and becomes 10...0
    // Case 2: x > y and (x - y + 1) is divisible by 9 -> n+1 has carries making sum decrease by multiples of 9
    puts((y == x + 1) || ((x > y) && !((x - y + 1) % 9)) ? "Yes" : "No");
  }
}


// https://github.com/VaHiX/codeForces/