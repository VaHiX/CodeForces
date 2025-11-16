// Problem: CF 1191 B - Tokitsukaze and Mahjong
// https://codeforces.com/contest/1191/problem/B

/*
B. Tokitsukaze and Mahjong
Algorithm: The problem involves determining the minimum number of tiles to draw to form at least one mentsu (a koutsu or shuntsu). 
The approach is to convert input tiles into numeric codes, sort them, then analyze differences between consecutive values to determine:
- If they already form a valid mentsu (0 moves)
- If only one tile needs to be added to complete a sequence or triplet (1 move)
- Otherwise, two tiles need to be added (2 moves)

Time Complexity: O(1) - fixed number of tiles (3), sorting is constant time.
Space Complexity: O(1) - fixed size array and variables.

*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
int a[3]; // Array to store numeric representations of tiles
int main() {
  string s;
  for (int i = 0; i < 3; ++i)
    cin >> s, a[i] = (s[0] - '0') + (s[1] - 'a') * 100; // Convert tile to number: digit + suit offset
  sort(a, a + 3); // Sort the tiles for easier analysis
  int t1 = a[1] - a[0], t2 = a[2] - a[1]; // Calculate differences between adjacent tiles
  if (t1 == t2 && (t1 == 1 || t1 == 0)) // If equal diffs and diff is 0 or 1, forming sequence or duplicate
    puts("0");
  else if (t1 == 0 || t1 == 1 || t1 == 2 || t2 == 0 || t2 == 1 || t2 == 2) // If any diff <= 2, can add one tile
    puts("1");
  else
    puts("2"); // Otherwise need two tiles
  return 0;
}


// https://github.com/VaHiX/codeForces/