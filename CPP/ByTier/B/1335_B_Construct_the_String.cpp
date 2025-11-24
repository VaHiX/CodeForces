// Problem: CF 1335 B - Construct the String
// https://codeforces.com/contest/1335/problem/B

/*
 * Problem: Construct a string of length n such that every substring of length a contains exactly b distinct letters.
 * 
 * Algorithm/Technique:
 * - The approach is based on cyclically repeating the last b letters of the alphabet.
 * - For a substring of length a, we want exactly b distinct letters.
 * - We can achieve this by using the last b letters of the alphabet (from 'z' down to 'z' - b + 1).
 * - Then, we cycle through these b letters to fill the entire string.
 * 
 * Time Complexity: O(n) - We iterate through the string once to construct it.
 * Space Complexity: O(1) - Only using a constant amount of extra space, not counting output.
 */

#include <iostream>

using namespace std;
int main() {
  int t, n, a, b;
  for (cin >> t; t--; cout << endl)
    for (cin >> n >> a >> b; n--;)
      // Using the last b letters from 'z' and cycling through them to satisfy the constraint
      cout << (char)(122 - n % b);
}


// https://github.com/VaHiX/CodeForces/