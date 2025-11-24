// Problem: CF 519 A - A and B and Chess
// https://codeforces.com/contest/519/problem/A

/*
 * Problem: A. A and B and Chess
 * Purpose: Determine which player (White or Black) has the stronger position based on the sum of piece weights.
 * 
 * Algorithms/Techniques:
 * - Single-pass board scanning
 * - Weight lookup via precomputed array
 * - Case distinction for white (uppercase) vs black (lowercase) pieces
 * 
 * Time Complexity: O(1) - Since the board size is fixed at 8x8 = 64 squares, the algorithm runs in constant time.
 * Space Complexity: O(1) - Only a fixed-size lookup table and a few variables are used.
 *
 * Approach:
 * - Precompute a lookup table with piece weights indexed by piece type.
 * - Iterate through the board character by character.
 * - For each piece, add or subtract its value based on whether it's white or black.
 * - Compare final score to determine the result.
 */

#include <cstdio>
int s; // Total score difference (positive = White wins, negative = Black wins)
char b, a[30] = "30000000000030195"; // Lookup table mapping piece characters to their weights
int main() {
  while (scanf("%c", &b) != EOF) // Read each character from input until EOF
    if (b > '.') // Skip empty squares ('.' is ASCII 46, so only process characters > 46)
      b < 'a' ? s += a[b - 'B'] - '0' : s -= a[b - 32 - 'B'] - '0'; // Add for white, subtract for black
  puts(s > 0 ? "White" : s ? "Black" : "Draw"); // Output result based on final score
}


// https://github.com/VaHiX/CodeForces/