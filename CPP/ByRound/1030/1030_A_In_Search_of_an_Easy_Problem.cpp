// Problem: CF 1030 A - In Search of an Easy Problem
// https://codeforces.com/contest/1030/problem/A

#include <cstdio>
// Flowerbox: 
// Problem: A. In Search of an Easy Problem
// Purpose: Determines if a problem is "EASY" or "HARD" based on responses from n people.
//          If any person responds with 1 (hard), output "HARD", otherwise "EASY".
// Algorithms/Techniques: Linear scan through input to detect presence of '1'.
// Time Complexity: O(n) - where n is the number of people.
// Space Complexity: O(1) - only using a constant amount of extra space.

int main() {
  long n;
  scanf("%ld", &n);
  bool hard(false); // Flag to track if any person considers problem as hard
  while (n--) {
    int x;
    scanf("%d", &x); // Read individual response (0 or 1)
    if (x) {         // If current person thinks it's hard
      hard = true;   // Set flag
      break;         // Early exit since we already know it's hard
    }
  }
  puts(hard ? "HARD" : "EASY"); // Output result based on flag
  return 0;
}

// https://github.com/VaHiX/codeForces/