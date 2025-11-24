// Problem: CF 655 A - Amity Assessment
// https://codeforces.com/contest/655/problem/A

/*
Algorithm/Technique: 
  - The problem involves determining if two 2x2 sliding puzzles can reach the same configuration.
  - The key insight is that all valid configurations of a 2x2 puzzle with 3 tiles and one empty space form a cycle.
  - By converting each puzzle's initial state into a string representing the order of tiles (ignoring the empty space),
    we can check if one configuration can be rotated to match another.
  - We double the first string and check if the second string appears as a substring in it — this checks if the two
    configurations are in the same cycle (i.e., one can be reached from the other by rotation).

Time Complexity: O(1) - Since we are dealing with fixed 2x2 grids, the number of operations is constant.
Space Complexity: O(1) - Only a constant amount of additional space is used.
*/
#include <iostream>
#include <string>

using namespace std;
int main() {
  string a, b, c, d, s1, s2;
  cin >> a >> b >> c >> d;
  for (int i = 0; i < 2; i++)
    if (a[i] != 'X')
      s1 += a[i];  // Collect non-X tiles from top row
  for (int i = 1; i >= 0; i--)
    if (b[i] != 'X')
      s1 += b[i];  // Collect non-X tiles from bottom row in reverse order
  for (int i = 0; i < 2; i++)
    if (c[i] != 'X')
      s2 += c[i];  // Collect non-X tiles from top row of second puzzle
  for (int i = 1; i >= 0; i--)
    if (d[i] != 'X')
      s2 += d[i];  // Collect non-X tiles from bottom row of second puzzle in reverse order
  s1 += s1;  // Double the string to simulate rotation
  if (s1.find(s2) != -1)  // Check if s2 is a rotation of s1
    cout << "YES";
  else
    cout << "NO";
  return 0;
}


// https://github.com/VaHiX/CodeForces/