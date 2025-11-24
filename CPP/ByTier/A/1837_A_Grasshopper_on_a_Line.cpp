// Problem: CF 1837 A - Grasshopper on a Line
// https://codeforces.com/contest/1837/problem/A

/*
Purpose: This code solves the problem of finding the minimum number of jumps for a grasshopper to reach a target point x on a line,
         where each jump must be a distance not divisible by a given integer k.

Algorithm/Techniques:
- If x is not divisible by k, then one jump of distance x is sufficient.
- Otherwise, we split the journey into two jumps: first jump of +1, then jump of (x - 1), ensuring neither jump is divisible by k.

Time Complexity: O(1) per test case, since all operations are constant time.
Space Complexity: O(1), as only a fixed amount of variables are used.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, k;
    scanf("%ld %ld", &x, &k);
    if (x % k) {
      // If x is not divisible by k, we can make a single jump of size x
      printf("1\n%ld\n", x);
    } else {
      // If x is divisible by k, we must break it into two jumps
      // First jump is +1 (not divisible by k), second is (x - 1)
      printf("2\n1 %ld\n", x - 1);
    }
  }
}


// https://github.com/VaHiX/CodeForces/