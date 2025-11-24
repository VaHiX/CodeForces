// Problem: CF 1118 E - Yet Another Ball Problem
// https://codeforces.com/contest/1118/problem/E

/*
Code Purpose:
This code solves the "Yet Another Ball Problem" by generating a valid sequence of costume colors for n pairs of dancers,
ensuring all constraints are satisfied. It uses a greedy approach with a specific pattern to assign colors.

Algorithms/Techniques:
- Greedy assignment with cyclic color patterns
- Modular arithmetic for color assignment
- Special handling for edge cases where solution is impossible

Time Complexity: O(n)
Space Complexity: O(1)

The solution works by:
1. Checking if a solution is possible (n <= k * (k - 1))
2. Assigning colors using a specific formula that ensures:
   - No two identical pairs
   - No pair with same color for man and woman
   - Consecutive pairs have different colors for both man and woman
*/

#include <stdio.h>
#include <iostream>

using namespace std;
int main() {
  int n, k;
  cin >> n >> k;
  // If n exceeds maximum possible pairs with given k, no solution exists
  if (n > 1ll * k * (k - 1))
    return puts("No"), 0;
  puts("Yes");
  int cur = 0; // Tracks current offset for woman's color
  // Loop through all pairs and assign colors
  for (int i = 0; i < n; i++)
    // Man's color: (i % k) + 1 (cyclic)
    // Woman's color: ((cur += (i % k == 0)) + i % k) % k + 1 (cyclic with offset)
    printf("%d %d\n", i % k + 1, ((cur += (i % k == 0)) + i % k) % k + 1);
}


// https://github.com/VaHiX/CodeForces/