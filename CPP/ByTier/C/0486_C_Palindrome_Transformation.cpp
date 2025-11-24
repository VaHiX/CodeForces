// Problem: CF 486 C - Palindrome Transformation
// https://codeforces.com/contest/486/problem/C

/*
C. Palindrome Transformation
Purpose: The code computes the minimum number of arrow key presses to transform a given string into a palindrome,
         considering that the cursor starts at position p and can move left/right cyclically and change characters up/down.

Algorithms/Techniques:
- Two-pointer approach to compare characters from both ends.
- Greedy selection of minimal character moves for each mismatched pair.
- Efficient cursor movement calculation by leveraging symmetry and minimizing distance.

Time Complexity: O(n), where n is the length of the string.
Space Complexity: O(1), excluding input storage.

Input:
- First line: n (length of string) and p (initial cursor position)
- Second line: a string of n lowercase letters

Output:
- Minimum number of arrow key presses to make the string a palindrome.
*/

#include <cstdio>
#include <iostream>
#include <string>
int main() {
  const int P = 26;            // Number of letters in alphabet
  long n, p;
  scanf("%ld %ld\n", &n, &p);
  std::string input;
  getline(std::cin, input);
  --n;                         // Convert to 0-based indexing
  --p;                         // Convert to 0-based indexing

  if (p > n / 2) {             // Adjust cursor position for symmetry
    p = n - p;
  }

  long l(-1), r(0), total(0);  // l: leftmost mismatched index, r: rightmost, total: steps needed

  for (long d = 0; d <= n / 2; d++) {     // Iterate through the first half of the string
    if (input[d] != input[n - d]) {      // Check if characters at symmetric positions differ
      int diff = input[d] - input[n - d]; // Compute difference in ASCII values
      if (diff < 0) {
        diff += 26;                       // Adjust for cyclic alphabet (wrap around 'z' to 'a')
      }
      if (diff > P / 2) {                 // Move towards smaller steps using symmetry
        diff = P - diff;
      }
      total += diff;                      // Accumulate minimal character changes needed

      if (l < 0) {
        l = d;                            // First mismatched index
      }
      r = d;                              // Update rightmost mismatched index
    }
  }

  // Calculate optimal cursor movement based on relative positions:
  if (p <= l) {
    total += r - p;                     // Cursor is left of all mismatches, go to rightmost
  } else if (l <= p && p <= r && (p - l <= r - p)) {
    total += (p - l) + (r - l);         // Cursor closer to left boundary, move there then right
  } else if (l <= p && p <= r && (r - p < p - l)) {
    total += (r - p) + (r - l);         // Cursor closer to right boundary, move there then left
  } else if (r <= p) {
    total += p - l;                     // Cursor is right of all mismatches, go to leftmost
  }

  if (l < 0) {                          // No mismatches found => already a palindrome
    puts("0");
  } else {
    printf("%ld\n", total);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/