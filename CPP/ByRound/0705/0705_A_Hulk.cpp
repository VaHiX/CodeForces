// Problem: CF 705 A - Hulk
// https://codeforces.com/contest/705/problem/A

/*
 * Problem: Hulk
 * Algorithm/Technique: String construction with conditional logic
 * 
 * Time Complexity: O(n) - We iterate through n layers once, performing constant time operations for each.
 * Space Complexity: O(n) - The output string has length proportional to n (each layer adds 4-5 characters).
 * 
 * The solution constructs the feeling string by alternating between "I hate " and "I love " 
 * based on the layer number (even positions get "I hate", odd get "I love"). 
 * The word "that" is used between layers, and "it" ends the sentence.
 */

#include <cstdio>
int main() {
  int n;
  scanf("%d\n", &n);
  for (int p = 0; p < n; p++) {
    // Print "I hate " for even positions (0, 2, 4, ...) and "I love " for odd positions (1, 3, 5, ...)
    printf((p % 2) ? "I love " : "I hate ");
    // Print "it" for the last layer, "that" for all other layers
    printf((p == n - 1) ? "it" : "that ");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/