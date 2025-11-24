// Problem: CF 1747 C - Swap Game
// https://codeforces.com/contest/1747/problem/C

/*
C. Swap Game
Algorithms/Techniques: Game Theory, Greedy
Time Complexity: O(n) per test case
Space Complexity: O(1)

This problem involves a game where Alice and Bob take turns modifying an array.
The key observation is that the game ends when a[1] becomes 0.
Each move consists of decreasing a[1] by 1 and swapping a[1] with some a[i] (i ≥ 2).
If at any point a[1] = 0, the current player loses.

The strategy can be analyzed as follows:
- If a[1] = 0 initially, the first player already loses.
- Otherwise, we examine whether there's any element in the array that is smaller than a[1].
  - If such an element exists, Alice can decrease a[1] to that smaller value, ensuring a winning position.
  - If all elements are ≥ a[1], then Bob will always be able to match or exceed the value of a[1]
    and ultimately force Alice into a losing state.

Hence, if any a[i] < a[1], Alice wins; otherwise, Bob wins.
*/

#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long a;
    scanf("%ld", &a);
    bool res(false); // tracks if any element is less than a[1]
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x < a) { // if any element is less than the first element
        res = true; // Alice can win by choosing that smaller element
      }
    }
    puts(res ? "Alice" : "Bob"); // output result based on whether Alice has a winning move
  }
}


// https://github.com/VaHiX/codeForces/