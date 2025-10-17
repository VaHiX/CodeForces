// Problem: CF 1987 C - Basil's Garden
// https://codeforces.com/contest/1987/problem/C

/*
C. Basil's Garden

Purpose:
This program calculates the number of seconds required for all flowers in a row to have zero height,
given that each second, the wind decreases the height of each flower based on a specific rule.

Algorithm/Techniques:
- Greedy approach with backward iteration
- For each flower from right to left, we compute how many seconds it will take for that flower to become 0,
  considering the effect of neighboring flowers

Time Complexity: O(n) per test case, where n is the number of flowers.
Space Complexity: O(n) for storing the heights of the flowers.

*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> h(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &h[p]);
    }
    // Initialize cnt with the height of the last flower
    long cnt(h.back());
    // Traverse from right to left to determine max time needed
    for (long p = n - 2; p >= 0; p--) {
      long tmp = cnt + 1;  // tmp represents how much time the current flower would take if it were taller than the next one
      cnt = (tmp > h[p] ? tmp : h[p]);  // Choose the maximum of tmp and actual height of current flower
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/