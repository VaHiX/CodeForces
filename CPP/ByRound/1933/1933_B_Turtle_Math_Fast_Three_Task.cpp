// Problem: CF 1933 B - Turtle Math: Fast Three Task
// https://codeforces.com/contest/1933/problem/B

/*
B. Turtle Math: Fast Three Task
Algorithm: Greedy with modular arithmetic
Time Complexity: O(n) per test case, where n is the size of the array
Space Complexity: O(1)

The problem asks to make the sum of the array divisible by 3 using minimum moves,
where each move is either removing an element or incrementing an element by 1.
Key observations:
- If the sum is already divisible by 3, no moves are needed.
- Otherwise:
  - If we can remove one element with remainder 1 when divided by 3, one move suffices.
  - If we can increment an element to change the remainder, one move may be enough.
  - Otherwise, two moves are needed (remove two elements or increment appropriately).
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    bool one(false); // Tracks if there exists an element with remainder 1 mod 3
    int s(0);        // Running sum mod 3
    for (long p = 0; p < n; p++) {
      int x;
      scanf("%d", &x);
      if (x % 3 == 1) {
        one = true;  // Mark that we found an element with remainder 1
      }
      s += x;
      s %= 3;        // Keep sum modulo 3 to reduce computation
    }
    if (!one && s % 3 == 1) {
      puts("2");     // Cannot use single removal, need two moves
    } else if (s % 3) {
      puts("1");     // Can fix with one move (remove or increment)
    } else {
      puts("0");     // Already divisible by 3
    }
  }
}


// https://github.com/VaHiX/codeForces/