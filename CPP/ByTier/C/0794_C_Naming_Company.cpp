// Problem: CF 794 C - Naming Company
// https://codeforces.com/contest/794/problem/C

/*
Purpose: This code solves the company naming game problem where two players (Oleg and Igor) take turns to fill
         positions in a string of length n. Oleg wants the final string to be lexicographically smallest,
         while Igor wants it to be lexicographically largest. Both play optimally.
         
Algorithm:
- Sort Oleg's letters in ascending order (to get smallest letters first for his turn)
- Sort Igor's letters in descending order (to get largest letters first for his turn)
- Process the positions alternately, with Oleg going first:
  - On odd turns (Oleg's turn), choose the smallest available letter from Oleg's sorted list
    or the largest from Igor's sorted list based on which is better for minimizing result.
  - On even turns (Igor's turn), choose the largest available letter from Igor's sorted list
    or the smallest from Oleg's sorted list based on which is better for maximizing result.
- Use two pointers to manage position selection from each sorted list and build the result string.

Time Complexity: O(n log n) due to sorting operations
Space Complexity: O(n) for storing strings and variables
*/

#include <algorithm>
#include <iostream>
#include <string>

int main() {
  std::string a, b;
  std::cin >> a >> b;
  std::string s(a); // Copy Oleg's original string to build result
  long n = a.size();
  sort(a.begin(), a.end()); // Sort Oleg's letters in ascending order
  sort(b.rbegin(), b.rend()); // Sort Igor's letters in descending order
  long la(0), lb(0), ls(0); // Pointers for Oleg's letters, Igor's letters, and result string
  long ra = (n + 1) / 2 - 1; // Right pointer for Oleg's sorted array (for the last half of positions)
  long rb = (n / 2) - 1; // Right pointer for Igor's sorted array (for the second half of positions)
  long rs = n - 1; // Right pointer for result string
  for (long p = 0; p < n; p++) {
    if (p & 1) { // Igor's turn (even indices starting at 0)
      // Choose between Igor's smallest or Oleg's largest (depending on what gives larger value)
      if (b[lb] > a[la]) { // If Igor's letter is better for maximizing
        s[ls++] = b[lb++]; // Add Igor's letter to left side
      } else {
        s[rs--] = b[rb--]; // Else take Igor's letter from right side for maximizing (but this may not be ideal, as it's used with a different logic)
      }
    } else { // Oleg's turn (odd indices)
      // Choose between Oleg's smallest or Igor's largest (depending on what gives smaller value)
      if (b[lb] > a[la]) { // If Igor's letter is better for minimizing
        s[ls++] = a[la++]; // Add Oleg's letter to left side
      } else {
        s[rs--] = a[ra--]; // Add Oleg's letter to right side to push smaller values to right (maximize final result in some way)
      }
    }
  }
  std::cout << s << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/