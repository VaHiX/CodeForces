// Problem: CF 1103 A - Grid game
// https://codeforces.com/contest/1103/problem/A

/*
Code Purpose:
This code simulates placing 2x1 or 1x2 tiles on a 4x4 grid based on a sequence of '0' (vertical) and '1' (horizontal) characters.
The algorithm uses a greedy strategy:
- For vertical tiles ('0'), it places them starting at row 2, column v+1, and increments v (wrapping around 4).
- For horizontal tiles ('1'), it places them starting at row 1, column 2*h+1, and toggles h between 0 and 1.

Time Complexity: O(|s|) where |s| is the length of the input string
Space Complexity: O(1) - only using a constant amount of extra space (variables h, v, p)

*/
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string s;
  std::cin >> s;
  long h(0), v(0);
  for (long p = 0; p < s.size(); p++) {
    if (s[p] == '0') {
      // Place vertical tile starting at row 2, column v+1
      std::cout << "2 " << (v + 1) << std::endl;
      ++v;
      v %= 4; // Wrap column index around 4
    } else if (s[p] == '1') {
      // Place horizontal tile starting at row 1, column 2*h+1
      std::cout << "1 " << (2 * h + 1) << std::endl;
      h = 1 - h; // Toggle h between 0 and 1
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/