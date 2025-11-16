// Problem: CF 2091 A - Olympiad Date
// https://codeforces.com/contest/2091/problem/A

/*
Purpose: This program determines the minimum number of digits that need to be drawn 
         in order to form the date "01.03.2025" from a sequence of digits. 
         It simulates the process of collecting digits and checks if we can form 
         the required date at any step.

Algorithms/Techniques:
- Greedy approach: We process the digits one by one and keep track of how many 
  of each required digit (0, 1, 2, 3, 5) we have collected.
- We try to form the date "01.03.2025", which effectively requires:
  - Three 0s (for the day "01" and month "03")
  - One 1 (for the day "01")
  - Two 2s (for the year "2025" -- two 2s and one 5)
  - One 3 (for the month "03")
  - One 5 (for the year "2025")

Time Complexity: O(n), where n is the number of digits drawn.
Space Complexity: O(1), since we use only a fixed number of variables.
*/

#include <cstdio>
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    // Initialize count of required digits for date "01.03.2025"
    int zero(3), one(1), two(2), three(1), five(1);
    int idx(0);  // Tracks the step at which we can form the date
    for (int p = 0; p < n; p++) {
      int d;
      scanf("%d", &d);
      // Decrement required count if current digit matches
      if (d == 0 && zero) {
        --zero;
      } else if (d == 1 && one) {
        --one;
      } else if (d == 2 && two) {
        --two;
      } else if (d == 3 && three) {
        --three;
      } else if (d == 5 && five) {
        --five;
      }
      // If we have collected all required digits for the date, record the step
      if (!idx && !zero && !one && !two && !three && !five) {
        idx = p + 1;
      }
    }
    printf("%d\n", idx);
  }
}


// https://github.com/VaHiX/CodeForces/