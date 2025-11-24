// Problem: CF 991 D - Bishwock
// https://codeforces.com/contest/991/problem/D

/*
Code Purpose:
This code solves the problem of placing the maximum number of L-shaped figures (bishwocks) on a 2×n board,
where some squares are occupied by pawns ('X'). Each bishwock occupies exactly 3 squares in an L-shape.
The approach uses dynamic programming with a greedy strategy:
For each column, we compute how many bishwocks can be placed based on the current and previous column states.
We track the "state" of a column as the count of empty squares (0s) in that column.
For every pair of columns, we determine how many bishwocks can be placed, considering both horizontal and vertical placements.

Algorithms/Techniques:
- Dynamic Programming with state tracking
- Greedy placement strategy
- Bit manipulation for character comparison (using ASCII values)

Time Complexity: O(n) where n is the length of the strings
Space Complexity: O(1) - only using a fixed amount of extra variables

*/

#include <stdio.h>
#include <string.h>
using namespace std;

char s[105], t[105];
int n, a, b, i, w;
int main() {
  // Read input strings s and t representing the two rows of the board
  for (scanf("%s%s", s, t), n = strlen(s); i < n; i++)
    // Count number of empty squares in current column
    b = (s[i] == 48) + (t[i] == 48), 
    // Add to result the number of bishwocks that can be placed based on cumulative state
    w += (a + b) / 3,
    // Update the state for next iteration: 
    // if combined empty squares from previous and current column > 2, 
    // then subtract 3 to represent one bishwock placed, else just take b
    a = (a + b > 2 ? a + b - 3 : b);
  return printf("%d", w), 0;
}


// https://github.com/VaHiX/CodeForces/