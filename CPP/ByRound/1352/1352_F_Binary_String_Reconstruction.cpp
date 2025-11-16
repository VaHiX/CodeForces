// Problem: CF 1352 F - Binary String Reconstruction
// https://codeforces.com/contest/1352/problem/F

/*
Purpose: This code reconstructs a binary string from the counts of adjacent character pairs with 0, 1, or 2 ones.
Algorithms/Techniques: Greedy construction based on the counts of pairs with 0, 1, and 2 ones.
Time Complexity: O(n0 + n1 + n2) per test case, as we iterate through all the counts to build the string.
Space Complexity: O(1) extra space (not counting the output string).

The approach:
- First, we determine the starting character based on whether n0 is zero or not.
- Then, we append all '1's (n2 times).
- Then, we append all '0's (n0 times).
- Finally, we append alternating 0 and 1 (n1 times) to satisfy the count of pairs with exactly one '1'.
*/

#include <stdio.h>
#include <iostream>

using namespace std;
int main() {
  int t, a, b, c;
  cin >> t;
  while (t--) {
    cin >> a >> b >> c;
    // Print the first character based on n0
    cout << (!a || b || c);
    // Append all '1's n2 times
    while (c--)
      cout << 1;
    // Append all '0's n0 times
    while (a--)
      cout << 0;
    // Append alternating 0 and 1 b times
    while (++a < b)
      cout << a % 2;
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/