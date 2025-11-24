// Problem: CF 2107 B - Apples in Boxes
// https://codeforces.com/contest/2107/problem/B

/*
B. Apples in Boxes

Purpose:
This code determines the winner of a game where Tom and Jerry take turns removing apples from boxes.
The game ends when a player makes a move that causes the difference between maximum and minimum apples in boxes to exceed k, or if no valid moves remain.

Algorithms/Techniques:
- Game theory (Nim-like logic with constraints)
- Optimization using prefix sums and tracking max/min values
- Efficient simulation of game state

Time Complexity: O(n) per test case, where n is the number of boxes.
Space Complexity: O(1), only using a constant amount of extra space.

Input:
Each test case contains n and k, followed by n integers representing apples in each box.

Output:
Print "Tom" if Tom wins, otherwise "Jerry".
*/

#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long mna(1e9 + 7), mxa(0), cntmx(0), s(0);
    for (int p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s = (s + x) % 2;   // Tracks parity of total apples (used to determine turn)
      if (x > mxa) {     // Update maximum
        mxa = x;
        cntmx = 1;       // Reset count of max elements
      } else if (x == mxa) {
        ++cntmx;         // Increment count if element equals current max
      }
      mna = (mna < x ? mna : x);   // Update minimum
    }
    // Check win condition for Jerry:
    // If difference between max and min exceeds k, or
    // the difference is exactly k+1 and there are multiple max elements
    if ((mxa > mna + k + 1) || ((mxa == mna + k + 1) && (cntmx > 1))) {
      puts("Jerry");
    } else {
      // Otherwise, result depends on parity of total apples:
      // Odd total means Tom plays last and wins; even means Jerry wins.
      puts(s ? "Tom" : "Jerry");
    }
  }
}


// https://github.com/VaHiX/codeForces/