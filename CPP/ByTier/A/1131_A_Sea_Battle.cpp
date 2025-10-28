// Problem: CF 1131 A - Sea Battle
// https://codeforces.com/contest/1131/problem/A

/*
Problem: Sea Battle
Algorithm/Techniques: Geometry, Mathematical Computation

Time Complexity: O(1)
Space Complexity: O(1)

This problem involves calculating the number of cells that are adjacent (including diagonally) to a ship 
consisting of two rectangles placed vertically with the second on top of the first. The rectangles share 
the same left edge, and we need to count all neighbor cells (not part of the ship) around the entire shape.
*/

#include <bits/std_abs.h>
#include <stdio.h>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 2500
#define inf 1e6
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;
int main() {
  ll i, j, k;
  ll n, m;
  ll w1, w2, h1, h2;
  sffl(w1, h1);     // Read width and height of first rectangle
  sffl(w2, h2);     // Read width and height of second rectangle
  ll ans = 0;
  ans += (w1 + 2);    // Add perimeter contribution from top and bottom edges of first rectangle
  ans += (w2 + 2);    // Add perimeter contribution from top and bottom edges of second rectangle
  ans += (h1 + h2);   // Add vertical edges along left side (heights combined)
  ans += (h1 + h2);   // Add vertical edges along right side (heights combined)
  ans += abs(w1 - w2); // Add contribution from difference in widths (diagonal neighbors)
  pfl(ans);          // Print final answer
  return 0;
}


// https://github.com/VaHiX/codeForces/