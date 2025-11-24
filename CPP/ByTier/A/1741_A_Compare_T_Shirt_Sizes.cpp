// Problem: CF 1741 A - Compare T-Shirt Sizes
// https://codeforces.com/contest/1741/problem/A

/*
 * Problem: Compare T-Shirt Sizes
 * Algorithms/Techniques: String parsing, comparison logic based on custom rules
 *
 * Time Complexity: O(n) where n is the length of the input strings (max 50)
 * Space Complexity: O(1) - only using a fixed amount of extra variables
 *
 * Description:
 * This program compares two T-shirt sizes according to specific rules:
 * - 'S' (small) is smaller than 'M' (medium) and 'L' (large)
 * - 'L' (large) is larger than 'M' (medium) and 'S' (small)
 * - 'X' indicates degree of size: more 'X's before 'S' makes the size smaller,
 *   more 'X's before 'L' makes it larger.
 * - 'M' is middle, so all S sizes are smaller than M, and all L sizes are larger.
 * 
 * The function f() converts a string like "XXXL" into an integer for easier comparison:
 * - 'M' returns 0
 * - 'S' returns negative number based on length (more Xs = smaller)
 * - 'L' returns positive number based on length (more Xs = larger)
 */

#include <iostream>
#include <string>

using namespace std;

int f() {
  string s;
  cin >> s;
  char c = s[s.size() - 1];  // Get last character to determine S, M, or L
  if (c == 'M')
    return 0;               // Medium is neutral value
  int t = s.size();
  return c == 'S' ? -t : +t; // Negative for small, positive for large
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for (; T--;) {
    int s = f();   // Parse first size
    int t = f();   // Parse second size
    cout << (s < t ? "<\n" : s > t ? ">\n" : "=\n");  // Compare and output result
  }
}


// https://github.com/VaHiX/codeForces/