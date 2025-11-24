// Problem: CF 515 B - Drazil and His Happy Friends
// https://codeforces.com/contest/515/problem/B

/*
Code Purpose:
This program determines whether Drazil can make all his friends (boys and girls) happy using a specific plan.
Each day, a boy and girl are paired up, and if at least one is happy, the other becomes happy too.
The algorithm simulates the process over a sufficient number of days to ensure all possible connections are explored.

Algorithms/Techniques:
- Simulation of iterative pairing process
- Boolean vector tracking happiness status
- Modular arithmetic to cycle through indices

Time Complexity: O(n * m)
Space Complexity: O(n + m)

*/
#include <cstdio>
#include <vector>
int main() {
  int n, m;
  scanf("%d %d\n", &n, &m);
  std::vector<bool> boys(n, 0), girls(m, 0); // Initialize vectors to track happiness of boys and girls
  int f, temp;
  scanf("%d", &f);
  for (int p = 0; p < f; p++) {
    scanf("%d", &temp);
    boys[temp] = 1; // Mark happy boys
  }
  scanf("%d", &f);
  for (int p = 0; p < f; p++) {
    scanf("%d", &temp);
    girls[temp] = 1; // Mark happy girls
  }
  long day(0);
  // Simulate the process for a large enough number of days to cover all combinations
  for (long p = 0; p < m * m * n * n; p++) {
    // Update happiness status based on current pairing
    boys[p % n] = girls[p % m] = boys[p % n] | girls[p % m];
  }
  // Check if all boys are happy
  for (int p = 0; p < n; p++) {
    if (!boys[p]) {
      puts("No");
      return 0;
    }
  }
  // Check if all girls are happy
  for (int p = 0; p < m; p++) {
    if (!girls[p]) {
      puts("No");
      return 0;
    }
  }
  puts("Yes");
  return 0;
}


// https://github.com/VaHiX/CodeForces/