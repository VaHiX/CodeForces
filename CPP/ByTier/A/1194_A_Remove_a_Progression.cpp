// Problem: CF 1194 A - Remove a Progression
// https://codeforces.com/contest/1194/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    printf("%ld\n", 2 * x);
  }
  return 0;
}

/*
Algorithm: A. Remove a Progression
Techniques: Mathematical observation

Time Complexity: O(1)
Space Complexity: O(1)

The key insight is that after removing every i-th element in the i-th step,
the remaining elements form an arithmetic progression with difference 2.
So the x-th remaining element is simply 2*x.

For example:
- n=3, x=1: sequence 1,2,3 → remove 1,2 then 3 → remaining [2,4] → answer = 2*1 = 2
- n=4, x=2: sequence 1,2,3,4 → remove 1,3 then 2,4 → remaining [2,4] → answer = 2*2 = 4

The pattern is that only even numbers remain, and they appear in order 2,4,6,8...
So the x-th element is 2*x.
*/

// https://github.com/VaHiX/codeForces/