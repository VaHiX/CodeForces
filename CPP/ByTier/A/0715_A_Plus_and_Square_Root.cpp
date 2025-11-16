// Problem: CF 715 A - Plus and Square Root
// https://codeforces.com/contest/715/problem/A

#include <cstdio>
/*
Flowerbox Description:
Purpose: This program determines the number of times the '+' button should be pressed 
         before pressing the 'sqrt' button at each level of a game, such that the 
         number on screen is a perfect square at each step and divisible by the 
         current level after pressing the 'sqrt' button.

Algorithms/Techniques: 
- Mathematical pattern recognition 
- Direct formula derivation for optimal sequence

Time Complexity: O(n) - single loop over n levels
Space Complexity: O(1) - only using a constant amount of extra space

The formula derived for the i-th level is: p * (p + 1) * (p + 1) - (p - 1)
This ensures:
1. The number becomes a perfect square at each step
2. The number is divisible by the current level after taking square root
3. All conditions of the problem are satisfied
*/
int main() {
  long long n;
  scanf("%lld\n", &n);
  for (long long p = 1; p <= n; p++) {
    if (p == 1) {
      puts("2"); // Special case for the first level
    } else {
      printf("%lld\n", p * (p + 1) * (p + 1) - (p - 1)); // Apply derived formula
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/