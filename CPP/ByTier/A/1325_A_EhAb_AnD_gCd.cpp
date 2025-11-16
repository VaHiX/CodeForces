// Problem: CF 1325 A - EhAb AnD gCd
// https://codeforces.com/contest/1325/problem/A

/*
Code Purpose:
This program finds two positive integers a and b such that GCD(a, b) + LCM(a, b) = x.
The approach uses the mathematical property that for any two numbers a and b:
GCD(a, b) * LCM(a, b) = a * b
A simple solution is to set a = 1, then b = x - 1, which works because:
- GCD(1, b) = 1
- LCM(1, b) = b
So we have 1 + b = x => b = x - 1.

Algorithms/Techniques:
- Mathematical property of GCD and LCM
- Simple substitution: setting one number to 1

Time Complexity: O(t), where t is the number of test cases
Space Complexity: O(1), constant space used

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    printf("1 %ld\n", x - 1);  // Output a=1, b=x-1
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/