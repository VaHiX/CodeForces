// Problem: CF 1883 C - Raspberries
// https://codeforces.com/contest/1883/problem/C

/*
C. Raspberries
Algorithm: Greedy + Modular Arithmetic
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem asks to find the minimum number of operations to make the product of array elements divisible by k.
Each operation allows incrementing an element by 1.

Key insights:
- If any element in the array is already divisible by k, we can immediately return 0 since the product is divisible.
- For k = 4, special cases are required because 4 = 2 * 2; we need two factors of 2 to form a multiple of 4.
- Otherwise, we compute the maximum remainder (md) when elements are divided by k and return k - md.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    int n, k;
    scanf("%d %d", &n, &k);
    int md(0), even(0); // md stores maximum remainder, even counts elements with remainder 2
    bool div(false);    // flag to check if any element is divisible by k
    for (int p = 0; p < n; p++) {
      int x;
      scanf("%d", &x);
      x %= k; // get remainder of x when divided by k
      if (x) {
        md = (md > x) ? md : x; // update max remainder
      } else {
        div = true; // found an element divisible by k
      }
      if (x == 2) {
        ++even; // count elements with remainder 2 (needed for special case of k=4)
      }
    }
    if (div) {
      puts("0"); // at least one element is divisible by k => product already divisible
    } else if (k == 4) {
      if (even >= 2) {
        puts("0"); // two elements with remainder 2 provide required 2*2 = 4
      } else if (even >= 1 || md == 3) {
        puts("1"); // one element with remainder 2 or one with remainder 3, and a factor of 2 needed
      } else {
        puts("2"); // need two increments to get even number or adjust mod
      }
    } else {
      printf("%d\n", k - md); // optimal increments needed using largest remainder
    }
  }
}


// https://github.com/VaHiX/codeForces/