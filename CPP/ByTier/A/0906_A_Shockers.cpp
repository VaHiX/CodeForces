// Problem: CF 906 A - Shockers
// https://codeforces.com/contest/906/problem/A

/*
 * Problem: Shockers
 * 
 * Purpose: 
 *   This program determines the number of excessive electric shocks Valentin received
 *   in the "Shockers" show. An excessive shock is one that could have been avoided
 *   if Valentin guessed the correct letter as early as possible (when it became uniquely determined).
 * 
 * Approach:
 *   - Maintain a bitmask `w` to represent possible letters that could be the answer.
 *   - For each action:
 *     - If the action is a word with a shock (`!`), mark all letters in the word as invalid.
 *     - If the action is a word without a shock (`.`), mark all letters in the word as valid.
 *     - If the action is a guess (`?`), check if only one letter in `w` remains possible.
 *       If so, calculate how many shocks occurred after this point and add them to result.
 * 
 * Time Complexity: O(n * L) where n is number of actions, L is total length of words.
 * Space Complexity: O(1) as we use only fixed-size arrays (128 bytes for character tracking).
 */

#include <stdio.h>
#include <string.h>

int n, f, s, v[128], w[128]; // f: flag, s: shock count, v: temporary word letters, w: possible letters
char p, q[100100];

// Function to update the possible set of letters
void c(int x) {
  int l = strlen(q), r = 0, i = 0;
  // Mark all letters in current word as present (if x == 0) or absent (if x == 1)
  for (; i < l; ++i)
    v[(int)q[i]] = 1;
  
  // Update the possible letters based on current word
  for (i = 97; i < 123; ++i)
    w[i] |= (v[i] ^ x), r += !w[i], v[i] = 0; // Toggle bits, count remaining valid letters
  
  // If there's only one possible letter left, flag it
  f |= r < 2;
}

int main() {
  for (scanf("%d%*c", &n); n; --n) {
    scanf("%c%*c%s%*c", &p, q); // Read action type and word
    
    // If this action is not a guess, and we're not at the last action, 
    // add shock penalty if flag f is set
    if (p != 46 && n > 1)
      s += f;
      
    // Determine if it's a word with shock (33 '!') or without (46 '.')
    c(p < 46 || (p > 46 && n < 2));
  }
  printf("%d", s);
}


// https://github.com/VaHiX/CodeForces/