// Problem: CF 2169 B - Drifting Away
// https://codeforces.com/contest/2169/problem/B

/*
Purpose: 
This code solves the problem of determining the maximum time Monocarp can sail along a river before ending up on the shore, 
based on the direction of currents and the presence of no-current cells ('*'). 
The algorithm simulates Monocarp's movement and checks for infinite loops (returning -1) or calculates the maximum steps before reaching the shore.

Algorithms/Techniques:
- Two-pointer technique to find the leftmost and rightmost regions of '<' and '>' characters.
- Simulation of movement with careful handling of no-current cells ('*').

Time Complexity: O(n) for each test case, where n is the length of the string.
Space Complexity: O(1) as we only use a constant amount of extra space per test case.

*/
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
int main() {
  int T;
  cin >> T;
  while (T--) {
    string s;
    cin >> s;
    int n = s.size();
    if (n == 1) {
      cout << 1 << '\n'; // If only one cell, Monocarp can stay there for 1 minute
      continue;
    }
    int i = -1, j = n; // i points to the rightmost '<', j points to the leftmost '>'
    while (i + 1 < n && s[i + 1] == '<') // Move i to the rightmost '<'
      ++i;
    while (j - 1 >= 0 && s[j - 1] == '>') // Move j to the leftmost '>'
      --j;
    // If there is a gap between i and j that is not occupied by '*' only, it's a loop
    if (i + 1 != j && i + 2 != j) {
      cout << "-1\n"; // Infinite loop case
    } else if (i + 2 != j) { // If there is a single '*' in between
      cout << max(i + 1, n - j) << '\n'; // Time is determined by max distance to shore from either side
    } else { // If there are no '*' in between
      cout << max(i + 1, n - j) + 1 << '\n'; // Add 1 for the extra move after the last current
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/