// Problem: CF 1468 K - The Robot
// https://codeforces.com/contest/1468/problem/K

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iosfwd>

using namespace std;
int t, f, i, j, p, q, x, y, dx[128], dy[128];
char s[5008];
int main() {
  // Flowerbox: 
  // Problem: K. The Robot
  // Purpose: Find a position to place an obstacle such that the robot returns to (0,0) after executing all commands.
  // Algorithm: Simulate robot's path and find a point where placing an obstacle results in returning to origin.
  // Time Complexity: O(n^2), where n is length of command string
  // Space Complexity: O(1) - fixed size arrays and variables

  for (dx['L'] = -(dx['R'] = 1), dy['D'] = -(dy['U'] = 1), scanf("%d", &t); t--;
       f ? 0 : printf("0 0\n"))
    for (scanf("%s", s), f = i = p = q = 0; s[i];
         x || y ? ++i : (printf("%d %d\n", p, q), f = i = strlen(s)))
      for (p += dx[s[i]], q += dy[s[j = i]],
           j = x = y = 0;
           s[j]; x += dx[s[j]], y += dy[s[j]],
           x == p && y == q ? (x -= dx[s[j]], y -= dy[s[j]]) : 0, ++j)
        ;
  exit(0);
}

// https://github.com/VaHiX/codeForces/