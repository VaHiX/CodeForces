// Problem: CF 1792 A - GamingForces
// https://codeforces.com/contest/1792/problem/A

/*
A. GamingForces

Problem Description:
Monocarp is playing a computer game where he needs to kill n monsters, each with h_i health.
He has two spells:
1. Choose exactly two alive monsters and decrease their health by 1.
2. Choose a single monster and kill it (health becomes 0).

Goal: Find the minimum number of spell casts to kill all monsters.

Algorithm:
- For each monster, if its health > 1, we can use the first spell to reduce health.
- If the health is 1, we count how many such monsters we have.
- When we encounter two or more monsters with health 1, we can treat them as a pair using the first spell,
  effectively reducing both to 0, hence increasing the count by 1.
- After processing all monsters, any remaining 1-health monsters (ones) must be killed individually,
  so add their count to total.

Time Complexity: O(n) per test case, where n is number of monsters.
Space Complexity: O(1), only using a few variables for counting.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long ones(0), cnt(0); // ones counts consecutive 1s, cnt counts total spells
    for (long p = 0; p < n; p++) {
      long h;
      scanf("%ld", &h);
      if (h > 1) {
        ++cnt; // Use one spell to reduce health of monster with h > 1
      } else {
        ++ones; // Count consecutive 1-health monsters
        if (ones >= 2) {
          ones = 0; // Reset counter after pairing two 1s
          ++cnt;    // Pair used, add one more spell cast
        }
      }
    }
    cnt += ones; // Remaining 1s need to be killed individually
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/