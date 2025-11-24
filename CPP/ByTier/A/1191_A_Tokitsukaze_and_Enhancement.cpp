// Problem: CF 1191 A - Tokitsukaze and Enhancement
// https://codeforces.com/contest/1191/problem/A

#include <cstdio>
// Flowerbox:
// Problem: A. Tokitsukaze and Enhancement
// Purpose: Determines the optimal HP increase (0, 1, or 2) to maximize character's category.
// Algorithm: Uses modulo arithmetic to categorize current HP and decide best increment.
// Time Complexity: O(1) - constant time operations.
// Space Complexity: O(1) - only uses a fixed amount of space.

int main() {
  long x;
  scanf("%ld", &x);  // Read the current HP value
  if (x % 4 == 0) {  // If HP is divisible by 4, it's category D
    puts("1 A");     // Increase by 1 to get category A
  } else if (x % 4 == 1) {  // If remainder is 1, it's already category A
    puts("0 A");            // No need to increase
  } else if (x % 4 == 2) {  // If remainder is 2, it's category C
    puts("1 B");            // Increase by 1 to get category B
  } else if (x % 4 == 3) {  // If remainder is 3, it's category B
    puts("2 A");            // Increase by 2 to get category A
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/