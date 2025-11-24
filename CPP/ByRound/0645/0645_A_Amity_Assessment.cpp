// Problem: CF 645 A - Amity Assessment
// https://codeforces.com/contest/645/problem/A

/*
Purpose: Determine if two 2x2 sliding puzzle configurations can reach the same state through valid moves.
         The sliding puzzle has tiles labeled 'A', 'B', 'C' and one empty space 'X'.
         A move consists of sliding a tile adjacent to the empty space into that space.

Algorithm/Techniques:
- Convert each puzzle configuration into a string representation where 'X' is ignored.
- For each configuration, generate a string of the three tiles in order (based on their position).
- Since the puzzle is 2x2, the tile sequence can be rotated.
  For example, if one puzzle has tiles in order "ABC", valid configurations are "ABC", "BCA", "CAB".
- The key insight: two configurations are reachable from each other if one is a rotation of the other.
- This is checked by concatenating the tile string with itself and checking if the other string appears in this concatenation.
- Time Complexity: O(1) - As the input is fixed size (4 positions), all operations are constant time.
- Space Complexity: O(1) - Only a constant amount of extra space is used.

*/
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
int main() {
  const int N = 4;
  std::ios_base::sync_with_stdio(false);
  std::string t;
  getline(std::cin, t);
  std::string x;
  getline(std::cin, x);
  std::reverse(x.begin(), x.end());
  t = t + x;
  std::string a("");
  for (int p = 0; p < N; p++) {
    if (t[p] != 'X') {
      a = a + t[p];
    }
  }
  a = a + a; // Concatenate the string with itself to allow rotation checks
  getline(std::cin, t);
  getline(std::cin, x);
  std::reverse(x.begin(), x.end());
  t = t + x;
  std::string b("");
  for (int p = 0; p < N; p++) {
    if (t[p] != 'X') {
      b = b + t[p];
    }
  }
  // Check if b is a substring of a (which indicates b is a rotation of a)
  puts(a.find(b) != std::string::npos ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/